// source-code/control/MtChart.cpp : implementation file
//

#include"stdafx.h"
#include"MtChart.h"
#include"../graphic/MtBitmap.h"

//MtChart
IMPLEMENT_DYNAMIC(MtChart,CWnd)

//define
const CString MtChart::CLASS_NAME(_T("MtChart"));

/**
 * name: MtChart
 * breif: ���캯����
 * param: --
 * return: --
 */
MtChart::MtChart()
	:_background_color_a(255)
	,_background_color_r(233)
	,_background_color_g(231)
	,_background_color_b(217)
	,_border_color_a(255)
	,_border_color_r(233)
	,_border_color_g(231)
	,_border_color_b(217){
	register_class();//��ϵͳע�ᵱǰ�ࡣ
}

/**
 * name: ~MtChart
 * breif: ����������
 * param: --
 * return: --
 */
MtChart::~MtChart(){
}

/**
 * name: set_background_color
 * breif: ���ñ�����ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 * return: --
 */
void MtChart::set_background_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b){
	_border_color_a=color_a;
	_border_color_r=color_r;
	_border_color_g=color_g;
	_border_color_b=color_b;
}

/**
 * name: set_border_color
 * breif: ���ñ߿���ɫ��
 * param: color_a - ��ɫa������
 *        color_r - ��ɫr������
 *        color_g - ��ɫg������
 *        color_b - ��ɫb������
 * return: --
 */
void MtChart::set_border_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b){
	_border_color_a=color_a;
	_border_color_r=color_r;
	_border_color_g=color_g;
	_border_color_b=color_b;
}

/**
 * name: draw
 * breif: ͼ����ƺ�����ϵͳ���ô����⺯��ʵ��ͼ��Ļ��ơ�
 * param: dest_dc - Ŀ��DC��
 *        dest_bitmap - Ŀ��λͼ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtChart::draw(const HDC /*dest_dc*/,MtBitmap & /*dest_bitmap*/){
	return(0);
}

BEGIN_MESSAGE_MAP(MtChart,CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//MtChart message handlers

/**
 * name: OnPaint
 * breif: �Ի��������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void MtChart::OnPaint(){
	CPaintDC dc(this);//device context for painting
	//TODO: Add your message handler code here
	//1.��ȡ��ǰ���ڿͻ����ߴ硣
	CRect size;
	GetClientRect(size);
	//2.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
	PtrToBitmap memory_bitmap(new MtBitmap(
		size.Width(),size.Height()));
	if((!static_cast<bool>(memory_bitmap))||(
		!memory_bitmap->is_valid())){
		return;
	}
	//3.���Ƶ�ǰ���ڱ����������жϻ����Ƿ�ɹ���
	if(memory_bitmap->fill(_background_color_a,
		_background_color_r,_background_color_g,
		_background_color_b)<0){
		return;
	}
	//4.���Ƶ�ǰ���ڱ߿򣬲����жϻ����Ƿ�ɹ���
	if(memory_bitmap->draw_rectangle(_border_color_a,
		_border_color_r,_border_color_g,_border_color_b,
		0,0,(size.Width()-1),(size.Height()-1))<0){
		return;
	}
	//5.����ͼ���������ݡ�
	if(draw(dc.GetSafeHdc(),*memory_bitmap)<0){
		return;
	}
	//6.���ڴ�λͼ�������ťDC�ϡ�
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	//Do not call CWnd::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * breif: ���ڲ�����Ϣ��Ӧ����������Ϣ��Ӧ�����ڴ��������ٻ��ƿ�����
 * param: pDC - ָ��ǰ���ڻ�ͼ�豸��
 * return: --
 */
BOOL MtChart::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CWnd::OnEraseBkgnd(pDC));
}

/**
 * name: register_class
 * breif: ��ϵͳע�ᵱǰ�ࡣ
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtChart::register_class(){
	//1.������ǰ�������������
	WNDCLASS window_class;
	HINSTANCE instance=AfxGetInstanceHandle();
	//2.�����ǰ����δ��ϵͳע�ᡣ
	if(!GetClassInfo(instance,CLASS_NAME,&window_class)){
		//2-1.�������Ϣ�ṹ�壬׼����ϵͳע�ᵱǰ�����ࡣ
		window_class.style=CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
		window_class.lpfnWndProc=::DefWindowProc;
		window_class.cbClsExtra=window_class.cbWndExtra=0;
		window_class.hInstance=instance;
		window_class.hIcon=NULL;
		window_class.hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		window_class.hbrBackground=(HBRUSH)(COLOR_3DFACE+1);
		window_class.lpszMenuName=NULL;
		window_class.lpszClassName=CLASS_NAME;
		//2-2.��ϵͳע�ᵱǰ�࣬�����ж�ע���Ƿ�ɹ���
		if(!AfxRegisterClass(&window_class)){
			AfxThrowResourceException();
			return(-1);
		}
	}
	//3.�������е��˳ɹ����ء�
	return(0);
}