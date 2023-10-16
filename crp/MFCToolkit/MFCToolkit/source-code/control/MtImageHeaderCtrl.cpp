// source-code/control/MtImageHeaderCtrl.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageHeaderCtrl.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"

//MtImageHeaderCtrl
IMPLEMENT_DYNAMIC(MtImageHeaderCtrl,CHeaderCtrl)

/**
 * name: MtImageHeaderCtrl
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtImageHeaderCtrl::MtImageHeaderCtrl()
	:CHeaderCtrl()
	,_height(35)
	,_item_background_image()
	,_item_background_image_region_division()
	,_is_item_background_image_stretched(FALSE)
	,_item_background_image_stretching_factors()
	,_item_text_color_a(255)
	,_item_text_color_r(0)
	,_item_text_color_g(0)
	,_item_text_color_b(0)
	,_item_text_alignment(ALIGNMENT_LEFT|ALIGNMENT_VCENTER){
}

/**
 * name: ~MtImageHeaderCtrl
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtImageHeaderCtrl::~MtImageHeaderCtrl(){
}

/**
 * name: set_height
 * brief: 设置高度。
 * param: height - 高度。
 * return: --
 */
void MtImageHeaderCtrl::set_height(const unsigned int height){
	_height=height;
}

/**
 * name: get_height
 * breif: 获取高度。
 * param: --
 * return: 返回高度。
 */
unsigned int MtImageHeaderCtrl::get_height() const{
	return(_height);
}

/**
 * name: load_item_background_image
 * brief: 加载列表框中列表项的背景图片。
 * param: image_path - 图片路径。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageHeaderCtrl::load_item_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	//1.根据图片路径进行图片加载，并且判断加载是否成功。
	_item_background_image.reset(new MtImage(image_path));
	if(!static_cast<bool>(_item_background_image)){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-1);
	}
	if(!_item_background_image->is_valid()){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_item_background_image_region_division.reset(new MtRegionDivision(
		_item_background_image->get_width(),_item_background_image->get_height(),
		image_rows,image_cols));
	if(!static_cast<bool>(_item_background_image_region_division)){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-3);
	}
	if(!_item_background_image_region_division->is_valid()){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: load_item_background_image
 * brief: 加载列表框中列表项的背景图片。
 * param: image - 指向图片的智能指针引用。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageHeaderCtrl::load_item_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	//1.根据传递图片设置背景图片，并且判断设置是否成功。
	_item_background_image=image;
	if(!static_cast<bool>(_item_background_image)){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-1);
	}
	if(!_item_background_image->is_valid()){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-2);
	}
	//2.根据图片的行数、列数生成图片剪裁器，并且判断是否成功。
	_item_background_image_region_division.reset(new MtRegionDivision(
		_item_background_image->get_width(),_item_background_image->get_height(),
		image_rows,image_cols));
	if(!static_cast<bool>(_item_background_image_region_division)){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-3);
	}
	if(!_item_background_image_region_division->is_valid()){
		_item_background_image.reset();
		_item_background_image_region_division.reset();
		return(-4);
	}
	//3.返回。
	return(0);
}

/**
 * name: set_item_background_image_stretching_factors
 * brief: 设置列表项背景图片拉伸系数。
 * param: stretch_left - 左侧拉伸系数。
 *        stretch_top - 顶部拉伸系数。
 *        stretch_right - 右侧拉伸系数。
 *        stretch_bottom - 底部拉伸系数。
 * return: --
 */
void MtImageHeaderCtrl::set_item_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_item_background_image_stretching_factors.left=stretch_left;
	_item_background_image_stretching_factors.top=stretch_top;
	_item_background_image_stretching_factors.right=stretch_right;
	_item_background_image_stretching_factors.bottom=stretch_bottom;
	_is_item_background_image_stretched=TRUE;
}

/**
 * name: set_item_text_color
 * brief: 设置标题项的文本颜色。
 * param: color_a - 颜色A成分。
 *        color_b - 颜色B成分。
 *        color_c - 颜色C成分。
 *        color_d - 颜色D成分。
 * return: --
 */
void MtImageHeaderCtrl::set_item_text_color(const unsigned char &color_a,
	const unsigned char &color_r,const unsigned char &color_g,
	const unsigned char &color_b){
	_item_text_color_a=color_a;
	_item_text_color_r=color_r;
	_item_text_color_g=color_g;
	_item_text_color_b=color_b;
}

/**
 * name: set_item_text_alignment
 * brief: 设置标题项的文本停靠方式。
 * param: alignment - 文本停靠方式。
 * return: --
 */
void MtImageHeaderCtrl::set_item_text_alignment(const unsigned int alignment){
	_item_text_alignment=alignment;
}

/**
 * name: get_item_text_alignment
 * brief: 获取列表项的文本停靠方式。
 * param: --
 * return: 返回列表项的文本停靠方式。
 */
unsigned int MtImageHeaderCtrl::get_item_text_alignment() const{
	return(_item_text_alignment);
}

BEGIN_MESSAGE_MAP(MtImageHeaderCtrl,CHeaderCtrl)
	ON_WM_PAINT()
	//ON_WM_ERASEBKGND() //如果不屏蔽发现滚动条滚动时标题栏刷新不及时。
	ON_MESSAGE(HDM_LAYOUT,&MtImageHeaderCtrl::OnLayout)
END_MESSAGE_MAP()

// MtImageHeaderCtrl message handlers

/**
 * name: OnPaint
 * breif: 窗口绘制消息响应函数。
 * param: --
 * return: --
 */
void MtImageHeaderCtrl::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.定义。
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	//2.获取当前标题项个数。
	const int items=GetItemCount();
	if(items<=0){
		return;
	}
	//3.获取当前窗口尺寸。
	CRect window_rect;
	GetClientRect(window_rect);
	if(window_rect.IsRectEmpty()){
		return;
	}
	//4.创建内存位图，并且判断创建是否成功。
	PtrToBitmap memory_bitmap(new MtBitmap(window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//5.循环绘制标题每一项。
	for(int item=0;item!=items;++item){
		//5-1.计算当前控件状态。
		unsigned int state=1;
		if(0==item){
			state=0;
		}
		//5-2.获取当前标题项尺寸。
		CRect item_rect;
		if(!GetItemRect(item,item_rect)){
			continue;
		}
		if(item_rect.IsRectEmpty()){
			continue;
		}
		//5-3.绘制当前标题项背景。
		draw_item_background(*memory_bitmap,item_rect,state);
		//5-3.获取当前标题项文本。
		TCHAR text[_MAX_PATH];
		memset(text,0,_MAX_PATH*sizeof(TCHAR));
		HD_ITEM hd_item;
		hd_item.mask=HDI_TEXT|HDI_FORMAT|HDI_ORDER;
		hd_item.pszText=text;
		hd_item.cchTextMax=_MAX_PATH;
		GetItem(item,&hd_item);
		//5-4.绘制当前标题项文本。
		draw_item_text(*memory_bitmap,text,item_rect,dc.GetSafeHdc());
	}
	//6.内存位图贴图。
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),window_rect.left,window_rect.top);
	// Do not call CHeaderCtrl::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: 窗口擦除消息响应函数，在这里用于消除不必要的自绘。
 * param: --
 * return 此函数一直返回TRUE。
 */
BOOL MtImageHeaderCtrl::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CHeaderCtrl::OnEraseBkgnd(pDC));
}

/**
 * name: OnLayout
 * brief: HDM_LAYOUT消息响应函数，当系统期望调整CHeaderCtrl的尺寸时，
 *        发送此消息。
 * param: wParam - 必须是0。
 *        lParam - 指向HDLAYOUT结构体的指针。
 * return: 如果函数执行成功返回TRUE，否则返回FALSE。
 */
LRESULT MtImageHeaderCtrl::OnLayout(WPARAM wParam,LPARAM lParam){
	//1.调用默认的窗口处理函数。
	const LRESULT result=MtImageHeaderCtrl::DefWindowProc(HDM_LAYOUT,wParam,lParam);
	//2.获取尺寸相关结构体指针。
	HD_LAYOUT *hd_layout=(HD_LAYOUT*)lParam;
	RECT *prc=hd_layout->prc;
	WINDOWPOS *pwpos=hd_layout->pwpos;
	//3.设置表头高度
	pwpos->cy=_height;  
	prc->top=_height;
	//4.返回窗口操作结果。
	return(result);
}

/**
 * name: draw_item_background
 * brief: 绘制列表项的背景。
 * param: memory_bitmap - 内存位图。
 *        item_rect - 列表项的尺寸。
 *		  state - 控件当前状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageHeaderCtrl::draw_item_background(MtBitmap &memory_bitmap,
	const CRect &item_rect,const unsigned int state){
	//1.判断当前背景图片是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_item_background_image)){
		return(-1);
	}
	if(!_item_background_image->is_valid()){
		return(-2);
	}
	//2.判断当前背景图片剪裁器是否合法，如果不合法则直接返回错误。
	if(!static_cast<bool>(_item_background_image_region_division)){
		return(-3);
	}
	if(!_item_background_image_region_division->is_valid()){
		return(-4);
	}
	//3.获取背景图片尺寸，如果获取失败直接返回错误。
	const CRect image_rect=_item_background_image_region_division->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(-5);
	}
	//4.将当前背景图片绘制的内存位图上。
	if(_is_item_background_image_stretched){
		if(_item_background_image->paste_to_bitmap_ex(&memory_bitmap,
			item_rect.left,item_rect.top,item_rect.Width(),item_rect.Height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height(),
			_item_background_image_stretching_factors.left,
			_item_background_image_stretching_factors.top,
			_item_background_image_stretching_factors.right,
			_item_background_image_stretching_factors.bottom)<0){
			return(-6);
		}
	}else{
		if(_item_background_image->paste_to_bitmap(&memory_bitmap,0,0,
			memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height())<0){
			return(-7);
		}
	}
	//5.成功返回。
	return(0);
}

/**
 * name: draw_item_text
 * brief: 绘制列表项文本。
 * param: memory_bitmap - 内存位图。
 *        text - 文本。
 *        rect - 绘制文本范围。
 *        dc - 绘制文本的绘图设备。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageHeaderCtrl::draw_item_text(MtBitmap &memory_bitmap,
	const CString &text,const CRect &rect,HDC dc){
	//1.如果当前传递参数不合法，则直接返回。
	if((text.IsEmpty())||(rect.IsRectEmpty())||(0==dc)){
		return(-1);
	}
	//2.重新计算当前文本绘制区域。
	CRect text_rect(rect);
	text_rect.InflateRect(-1,-1,-1,-1);
	//3.计算当前文本停靠方式。
	MtBitmap::Alignment text_h_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_item_text_alignment&ALIGNMENT_HCENTER){
		text_h_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_item_text_alignment&ALIGNMENT_RIGHT){
		text_h_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	MtBitmap::Alignment text_v_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_item_text_alignment&ALIGNMENT_VCENTER){
		text_v_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_item_text_alignment&ALIGNMENT_BOTTOM){
		text_v_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	//4.获取当前文本绘制的字体。
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		text_rect.left,text_rect.top,text_rect.Width(),text_rect.Height(),_item_text_color_a,
		_item_text_color_r,_item_text_color_g,_item_text_color_b,text_h_alignment,text_v_alignment)<0){
		return(-2);
	}
	//5.成功返回。
	return(0);
}