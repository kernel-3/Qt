#include"stdafx.h"
#include"MtGdiplus.h"
#include"../tool/MtLock.h"
#include"../tool/MtSingleton.h"
#include"../tool/MtCharacterSet.h"
#include<Gdiplus.h>

/**
 * name: MtGdiplus
 * brief: ����������
 * param: --
 * return: --
 */
MtGdiplus::~MtGdiplus(void){
	release();
}

/**
 * name: instance
 * brief: ��ȡ��ǰ���Ψһʵ������
 * param: --
 * return: ���ص�ǰ���Ψһʵ������
 */
MtGdiplus *MtGdiplus::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: calculate_text_size
 * breif: ����ָ���ı��ߴ硣
 * param: text - ָ���ı���
 *        dc - �ı�׼�����Ƶ�DC�豸��
 *        font - ָ�����塣
 *        size - �����ı��ߴ硣
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtGdiplus::calculate_text_size(const CString &text,
	const HDC dc,const HFONT font,CSize &size){
	//1.�����ǰ�������ݲ��Ϸ�����ֱ�ӷ��ش���
	if((0==dc)||(INVALID_HANDLE_VALUE==dc)||
		(0==font)||(INVALID_HANDLE_VALUE==font)){
		return(-1);
	}
	//2.�����ǰ�ı�����Ϊ�գ���ֱ�������ı��ߴ�Ϊ�㡣
	if(_T("")==text){
		size.cx=0;
		size.cy=0;
		return(0);
	}
	//3.����GDI+���㵱ǰ�ı��ߴ硣
	Gdiplus::Font font_t(dc,font);
	if(Gdiplus::Ok!=font_t.GetLastStatus()){
		return(-2);
	}
	Gdiplus::GraphicsPath path;
	Gdiplus::FontFamily family;
	if(Gdiplus::Ok!=font_t.GetFamily(&family)){
		return(-3);
	}
	if(Gdiplus::Ok!=path.AddString(static_cast<const WCHAR*>(
		MtCharacterSet::to_unicode(text)),-1,&family,font_t.GetStyle(),
		font_t.GetSize(),Gdiplus::Point(0,0),0)){
		return(-4);
	}
	Gdiplus::Rect rect;
	if(Gdiplus::Ok!=path.GetBounds(&rect)){
		return(-5);
	}
	//4.���ص�ǰ���ֳߴ硣
	size.cx=rect.Width;
	size.cy=rect.Height;
	//5.�������е���ֱ�ӷ��ء�
	return(0);
}

/**
 * name: initialize
 * brief: ��ʼ��GDI+�⡣
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtGdiplus::initialize(){
	if(0!=_token){
		return(0);
	}
	Gdiplus::GdiplusStartupInput input;
	if(Gdiplus::Ok!=Gdiplus::GdiplusStartup(&_token,&input,0)){
		_token=0;
		return(-1);
	}
	return(0);
}

/**
 * name: release
 * brief: �ͷ�GDI+�⡣
 * param: --
 * return: --
 */
void MtGdiplus::release(){
	if(0!=_token){
		Gdiplus::GdiplusShutdown(_token);
		_token=0;
	}
}

/**
 * name: MtGdiplus
 * brief: ���캯����
 * param: --
 * return: --
 */
MtGdiplus::MtGdiplus(void)
	:_token(0){
}