// source-code/control/MtImageListCtrl.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageListCtrl.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"
#include"MtImageHeaderCtrl.h"

//MtImageListCtrl
IMPLEMENT_DYNAMIC(MtImageListCtrl,CListCtrl)

/**
 * name: MtImageListCtrl
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtImageListCtrl::MtImageListCtrl()
	:CListCtrl()
	,_item_background_image()
	,_item_background_image_region_division()
	,_is_item_background_image_stretched(FALSE)
	,_item_background_image_stretching_factors()
	,_item_text_color_a(255)
	,_item_text_color_r(0)
	,_item_text_color_g(0)
	,_item_text_color_b(0)
	,_item_light_text_color_a(0)
	,_item_light_text_color_r(0)
	,_item_light_text_color_g(0)
	,_item_light_text_color_b(0)
	,_item_text_alignment(ALIGNMENT_LEFT|ALIGNMENT_VCENTER)
	,_item_row_height(35)
	,_header(new MtImageHeaderCtrl){
}

/**
 * name: ~MtImageListCtrl
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtImageListCtrl::~MtImageListCtrl(){
	delete _header;
}

/**
 * name: load_item_background_image
 * brief: 加载列表框中列表项的背景图片。
 * param: image_path - 图片路径。
 *		  image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageListCtrl::load_item_background_image(const CString &image_path,
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
int MtImageListCtrl::load_item_background_image(PtrToImage image,
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
void MtImageListCtrl::set_item_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_item_background_image_stretching_factors.left=stretch_left;
	_item_background_image_stretching_factors.top=stretch_top;
	_item_background_image_stretching_factors.right=stretch_right;
	_item_background_image_stretching_factors.bottom=stretch_bottom;
	_is_item_background_image_stretched=TRUE;
}

/**
 * name: set_item_text_color
 * brief: 设置列表项的文本颜色。
 * param: color_a - 颜色A成分。
 *        color_b - 颜色B成分。
 *        color_c - 颜色C成分。
 *        color_d - 颜色D成分。
 * return: --
 */
void MtImageListCtrl::set_item_text_color(const unsigned char &color_a,
	const unsigned char &color_r,const unsigned char &color_g,
	const unsigned char &color_b){
	_item_text_color_a=color_a;
	_item_text_color_r=color_r;
	_item_text_color_g=color_g;
	_item_text_color_b=color_b;
}

/**
 * name: set_item_light_text_color
 * brief: 设置列表项文本的高亮颜色。
 * param: color_a - 颜色A成分。
 *        color_b - 颜色B成分。
 *        color_c - 颜色C成分。
 *        color_d - 颜色D成分。
 * return: --
 */
void MtImageListCtrl::set_item_light_text_color(const unsigned char &color_a,
	const unsigned char &color_r,const unsigned char &color_g,
	const unsigned char &color_b){
	_item_light_text_color_a=color_a;
	_item_light_text_color_r=color_r;
	_item_light_text_color_g=color_g;
	_item_light_text_color_b=color_b;
}

/**
 * name: set_item_text_alignment
 * brief: 设置列表项的文本停靠方式。
 * param: alignment - 文本停靠方式。
 * return: --
 */
void MtImageListCtrl::set_item_text_alignment(const unsigned int alignment){
	_item_text_alignment=alignment;
}

/**
 * name: get_item_text_alignment
 * brief: 获取列表项的文本停靠方式。
 * param: --
 * return: 返回列表项的文本停靠方式。
 */
unsigned int MtImageListCtrl::get_item_text_alignment() const{
	return(_item_text_alignment);
}

/**
 * name: set_item_row_height
 * brief: 设置列表项的行高。
 * param: height - 行高。
 * return: --
 */
void MtImageListCtrl::set_item_row_height(const unsigned int height){
	_item_row_height=height;
}

/**
 * name: get_item_row_height
 * brief: 获取列表项的行高。
 * param: --
 * return: 返回行高。
 */
unsigned int MtImageListCtrl::get_item_row_height() const{
	return(_item_row_height);
}

/**
 * name: load_header_item_background_image
 * brief: 加载标题头子项背景图片。
 * param: image_path - 图片路径。
 *        image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageListCtrl::load_header_item_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	return(_header->load_item_background_image(image_path,image_rows,image_cols));
}

/**
 * name: load_header_item_background_image
 * brief: 加载标题头子项背景图片。
 * param: image - 指向图片的智能指针引用。
 *        image_rows - 图片行数。
 *        image_cols - 图片列数。
 * return: 如果背景图片加载成功返回值大于等于零，否则返回值小于零。
 */
int MtImageListCtrl::load_header_item_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	return(_header->load_item_background_image(image,image_rows,image_cols));
}

/**
 * name: set_header_item_background_image_stretching_factors
 * brief: 设置标题头子项背景图片拉伸系数。
 * param: stretch_left - 左侧拉伸系数。
 *        stretch_top - 顶部拉伸系数。
 *        stretch_right - 右侧拉伸系数。
 *        stretch_bottom - 底部拉伸系数。
 * return: --
 */
void MtImageListCtrl::set_header_item_background_image_stretching_factors(
	const int stretch_left,const int stretch_top,const int stretch_right,
	const int stretch_bottom){
	return(_header->set_item_background_image_stretching_factors(stretch_left,
		stretch_top,stretch_right,stretch_bottom));
}

/**
 * name: set_header_item_text_color
 * brief: 设置标题头子项的文本颜色。
 * param: color_a - 颜色A成分。
 *        color_b - 颜色B成分。
 *        color_c - 颜色C成分。
 *        color_d - 颜色D成分。
 * return: --
 */
void MtImageListCtrl::set_header_item_text_color(const unsigned char &color_a,
	const unsigned char &color_r,const unsigned char &color_g,const unsigned char &color_b){
	_header->set_item_text_color(color_a,color_r,color_g,color_b);
}

/**
 * name: set_header_item_text_alignment
 * brief: 设置标题头子项的文本停靠方式。
 * param: alignment - 文本停靠方式。
 * return: --
 */
void MtImageListCtrl::set_header_item_text_alignment(const unsigned int alignment){
	_header->set_item_text_alignment(alignment);
}

/**
 * name: get_header_item_text_alignment
 * brief: 获取标题头子项的文本停靠方式。
 * param: --
 * return: 返回标题头子项的文本停靠方式。
 */
unsigned int MtImageListCtrl::get_header_item_text_alignment() const{
	return(_header->get_item_text_alignment());
}

/**
 * name: PreSubclassWindow
 * brief: 窗口子类化虚拟函数。
 * param: --
 * return: --
 */
void MtImageListCtrl::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	//////////////////////////////////////////////////////////////////
	//1.修改当前窗口风格，使其变为自绘风格。
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	//2.修改当前标题栏窗口处理过程。
	HWND header=GetHeaderCtrl()->GetSafeHwnd();
	_header->SubclassWindow(header);
	//////////////////////////////////////////////////////////////////
	CListCtrl::PreSubclassWindow();
}

/**
 * name: DrawItem
 * breif: 控件自绘虚拟函数。
 * param: lpDrawItemStruct - 执行自绘控件状态结构体。
 * return: --
 */
void MtImageListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){
	// TODO:  Add your code to draw the specified item
	//1.自定义类型。
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	//2.创建绘制区域的内存位图，并且判断创建是否成功。
	//2-1.获取当前绘图区域尺寸。
	const CRect draw_rect(lpDrawItemStruct->rcItem);
	//2-2.创建内存位图，如果创建失败则直接返回。
	PtrToBitmap memory_bitmap(new MtBitmap(draw_rect.Width(),draw_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//3.计算当前列表项的状态（1 普通状态、3 高亮状态）。
	unsigned int state=1;
	LVITEM lvi;
	memset(&lvi,0,sizeof(LVITEM));
	lvi.mask=LVIF_STATE;
	lvi.stateMask=LVIS_FOCUSED|LVIS_SELECTED;
	lvi.iItem=lpDrawItemStruct->itemID;
	GetItem(&lvi);
	if(lvi.state&LVIS_SELECTED){
		state=3;
	}
	//4.获取当前列表框列数，标题尺寸。
	const int cols=_header->GetItemCount();
	//5.遍历当前列表框中每一项,并且对每一项进行绘制。
	for(int item=0;item!=cols;++item){
		//5-1.根据是否为最左侧项，调整当前控件状态。
		unsigned int state_t=state;
		if((1==state)&&(0==item)){
			state_t=0;
		}else if((3==state)&&(0==item)){
			state_t=2;
		}
		//5-2.计算当前项的尺寸。
		CRect item_rect;
		if(0!=item){
			if(!GetSubItemRect(lpDrawItemStruct->itemID,
				item,LVIR_BOUNDS,item_rect)){
				continue;
			}
		}else if(1==cols){//如果当前列表框只有1列。
			if(!GetItemRect(lpDrawItemStruct->itemID,
				item_rect,LVIR_BOUNDS)){
				continue;
			}
		}else{
			CRect temp_rect;
			if(!GetSubItemRect(lpDrawItemStruct->itemID,1,
				LVIR_BOUNDS,temp_rect)){
				continue;
			}
			if(!GetItemRect(lpDrawItemStruct->itemID,
				item_rect,LVIR_BOUNDS)){
				continue;
			}
			item_rect.right=temp_rect.left;
		}
		item_rect.bottom=item_rect.Height();
		item_rect.top=0;
		//5-3.用标题拦相应子项的尺寸效正列表项的尺寸（如果不这样在水平滚动条滚动时，标题拦、列表项不同步）。
		CRect hearder_item_rect;
		if(!_header->GetItemRect(item,hearder_item_rect)){
			continue;
		}
		item_rect.left=hearder_item_rect.left;
		item_rect.right=hearder_item_rect.right;
		//5-4.绘制当前列表框中的项。
		draw_item_background(*memory_bitmap,item_rect,state_t);
		//5-5.绘制列表项。
		draw_item(*memory_bitmap,lpDrawItemStruct->itemID,item,item_rect,state_t);
		//5-6.绘制当前列表项的文字。
		const CString text=GetItemText(lpDrawItemStruct->itemID,item);
		draw_item_text(*memory_bitmap,text,item_rect,state_t,lpDrawItemStruct->hDC);
	}
	//6.将背景图片黏贴到绘图设备上。
	memory_bitmap->paste_to_dc(lpDrawItemStruct->hDC,draw_rect.left,draw_rect.top);
}

/**
 * name: MeasureItem
 * brief: 列表项高度调整虚拟函数。
 * param: lpMeasureItemStruct - 指向列表项尺寸结构体。
 * return: --
 */
void MtImageListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){
	lpMeasureItemStruct->itemHeight=_item_row_height;
}

/**
 * name: draw_item
 * brief: 虚拟函数，绘制列表项。
 * param: memory_bitmap - 内存位图引用。
 *        item - 列表项。
 *        sub_item - 列表子项。
 *        item_rect - 列表项位置尺寸。
 *        state - 列表项状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 * remark: 此函数是子类绘制列表项的接口。
 */
int MtImageListCtrl::draw_item(MtBitmap &/*memory_bitmap*/,const int /*item*/,
	const int /*sub_item*/,const CRect &/*item_rect*/,const unsigned int /*state*/){
	return(0);
}

BEGIN_MESSAGE_MAP(MtImageListCtrl,CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
	//ON_WM_ERASEBKGND() //如果不屏蔽发现滚动条滚动时List刷新不及时。
END_MESSAGE_MAP()

/**
 * name: OnEraseBkgnd
 * brief: 窗口擦除消息响应函数，在这里用于消除不必要的自绘。
 * param: --
 * return 此函数一直返回TRUE。
 */
BOOL MtImageListCtrl::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CListCtrl::OnEraseBkgnd(pDC));
}

/**
 * name: draw_item_background
 * brief: 绘制列表项的背景。
 * param: memory_bitmap - 内存位图。
 *        item_rect - 列表项的尺寸。
 *		  state - 控件当前状态。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageListCtrl::draw_item_background(MtBitmap &memory_bitmap,
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
 *        state - 控件当前状态。
 *        dc - 绘制文本的绘图设备。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int MtImageListCtrl::draw_item_text(MtBitmap &memory_bitmap,
	const CString &text,const CRect &rect,const unsigned int state,HDC dc){
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
	//4.计算当前文本绘制颜色。
	unsigned char color_a=_item_text_color_a;
	unsigned char color_r=_item_text_color_r;
	unsigned char color_g=_item_text_color_g;
	unsigned char color_b=_item_text_color_b;
	if((0!=_item_light_text_color_a)&&((2==state)||(3==state))){
		color_a=_item_light_text_color_a;
		color_r=_item_light_text_color_r;
		color_g=_item_light_text_color_g;
		color_b=_item_light_text_color_b;
	}
	//5.获取当前文本绘制的字体。
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		text_rect.left,text_rect.top,text_rect.Width(),text_rect.Height(),color_a,
		color_r,color_g,color_b,text_h_alignment,text_v_alignment)<0){
		return(-2);
	}
	//5.成功返回。
	return(0);
}