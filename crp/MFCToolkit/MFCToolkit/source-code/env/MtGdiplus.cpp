#include"stdafx.h"
#include"MtGdiplus.h"
#include"../tool/MtLock.h"
#include"../tool/MtSingleton.h"
#include"../tool/MtCharacterSet.h"
#include<Gdiplus.h>

/**
 * name: MtGdiplus
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtGdiplus::~MtGdiplus(void){
	release();
}

/**
 * name: instance
 * brief: 获取当前类的唯一实例对象。
 * param: --
 * return: 返回当前类的唯一实例对象。
 */
MtGdiplus *MtGdiplus::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: calculate_text_size
 * breif: 计算指定文本尺寸。
 * param: text - 指定文本。
 *        dc - 文本准备绘制的DC设备。
 *        font - 指定字体。
 *        size - 返回文本尺寸。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtGdiplus::calculate_text_size(const CString &text,
	const HDC dc,const HFONT font,CSize &size){
	//1.如果当前参数传递不合法，则直接返回错误。
	if((0==dc)||(INVALID_HANDLE_VALUE==dc)||
		(0==font)||(INVALID_HANDLE_VALUE==font)){
		return(-1);
	}
	//2.如果当前文本传递为空，则直接设置文本尺寸为零。
	if(_T("")==text){
		size.cx=0;
		size.cy=0;
		return(0);
	}
	//3.利用GDI+计算当前文本尺寸。
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
	//4.返回当前文字尺寸。
	size.cx=rect.Width;
	size.cy=rect.Height;
	//5.程序运行到此直接返回。
	return(0);
}

/**
 * name: initialize
 * brief: 初始化GDI+库。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 释放GDI+库。
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
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtGdiplus::MtGdiplus(void)
	:_token(0){
}