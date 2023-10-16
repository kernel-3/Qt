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
 * breif: 构造函数。
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
	register_class();//向系统注册当前类。
}

/**
 * name: ~MtChart
 * breif: 析构函数。
 * param: --
 * return: --
 */
MtChart::~MtChart(){
}

/**
 * name: set_background_color
 * breif: 设置背景颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
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
 * breif: 设置边框颜色。
 * param: color_a - 颜色a分量。
 *        color_r - 颜色r分量。
 *        color_g - 颜色g分量。
 *        color_b - 颜色b分量。
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
 * breif: 图标绘制函数，系统调用此虚拟函数实现图表的绘制。
 * param: dest_dc - 目标DC。
 *        dest_bitmap - 目标位图。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * breif: 对话框绘制消息相应函数。
 * param: --
 * return: --
 */
void MtChart::OnPaint(){
	CPaintDC dc(this);//device context for painting
	//TODO: Add your message handler code here
	//1.获取当前窗口客户区尺寸。
	CRect size;
	GetClientRect(size);
	//2.创建内存位图，并且判断创建是否成功。
	PtrToBitmap memory_bitmap(new MtBitmap(
		size.Width(),size.Height()));
	if((!static_cast<bool>(memory_bitmap))||(
		!memory_bitmap->is_valid())){
		return;
	}
	//3.绘制当前窗口背景，并且判断绘制是否成功。
	if(memory_bitmap->fill(_background_color_a,
		_background_color_r,_background_color_g,
		_background_color_b)<0){
		return;
	}
	//4.绘制当前窗口边框，并且判断绘制是否成功。
	if(memory_bitmap->draw_rectangle(_border_color_a,
		_border_color_r,_border_color_g,_border_color_b,
		0,0,(size.Width()-1),(size.Height()-1))<0){
		return;
	}
	//5.绘制图表其它内容。
	if(draw(dc.GetSafeHdc(),*memory_bitmap)<0){
		return;
	}
	//6.将内存位图黏贴到按钮DC上。
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	//Do not call CWnd::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * breif: 窗口擦除消息响应函数，此消息响应函数在此用来减少绘制开销。
 * param: pDC - 指向当前窗口绘图设备。
 * return: --
 */
BOOL MtChart::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CWnd::OnEraseBkgnd(pDC));
}

/**
 * name: register_class
 * breif: 向系统注册当前类。
 * param: --
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtChart::register_class(){
	//1.声明当前操作所需变量。
	WNDCLASS window_class;
	HINSTANCE instance=AfxGetInstanceHandle();
	//2.如果当前类尚未向系统注册。
	if(!GetClassInfo(instance,CLASS_NAME,&window_class)){
		//2-1.填充类信息结构体，准备向系统注册当前窗口类。
		window_class.style=CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
		window_class.lpfnWndProc=::DefWindowProc;
		window_class.cbClsExtra=window_class.cbWndExtra=0;
		window_class.hInstance=instance;
		window_class.hIcon=NULL;
		window_class.hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		window_class.hbrBackground=(HBRUSH)(COLOR_3DFACE+1);
		window_class.lpszMenuName=NULL;
		window_class.lpszClassName=CLASS_NAME;
		//2-2.向系统注册当前类，并且判断注册是否成功。
		if(!AfxRegisterClass(&window_class)){
			AfxThrowResourceException();
			return(-1);
		}
	}
	//3.程序运行到此成功返回。
	return(0);
}