#include"stdafx.h"
#include"MtImageButton.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"
#include"../env/MtGdiplus.h"
#include<Gdiplus.h>

IMPLEMENT_DYNAMIC(MtImageButton,CButton)

/**
 * name: MtImageButton
 * brief: ���캯����
 * param: type - ��ť���͡�
 * return: --
 */
MtImageButton::MtImageButton(const Type type)
	:CButton()
	,_type(type)
	,_is_mouse_tracking(FALSE)
	,_is_mouse_hover(FALSE)
	,_is_checked(FALSE)
	//,_last_state(0)
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_foreground_image()
	,_foreground_image_region_division()
	,_foreground_image_alignment(0)
	,_is_foreground_image_stretched(FALSE)
	,_foreground_image_stretching_factors()
	,_text_color_a(255)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0)
	,_light_text_color_a(0)
	,_light_text_color_r(0)
	,_light_text_color_g(0)
	,_light_text_color_b(0){
}

/**
 * name: ~MtImageButton
 * brief: ����������
 * param: --
 * return: --
 */
MtImageButton::~MtImageButton(){
}

/**
 * name: set_checked
 * brief: ���ð�ťChecked״̬��
 * param: is_checked - �Ƿ���Checked״̬��
 *        is_invalidated - �Ƿ�ˢ�µ�ǰ��ť��
 * return: --
 */
void MtImageButton::set_checked(const BOOL is_checked,const BOOL is_invalidated/*=TRUE*/){
	_is_checked=is_checked;
	if(is_invalidated){
		//update_parent_window();
		Invalidate(FALSE);
	}
}

/**
 * name: get_checked
 * brief: ��ȡ��ťChecked״̬��
 * param: --
 * return: ���ذ�ťChecked״̬��
 */
BOOL MtImageButton::get_checked() const{
	return(_is_checked);
}

/**
 * name: load_background_image
 * brief: ���ذ�ť����ͼƬ��
 * param: image_path - ͼƬ·����
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageButton::load_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	//1.����ͼƬ·������ͼƬ���أ������жϼ����Ƿ�ɹ���
	_background_image.reset(new MtImage(image_path));
	if(!static_cast<bool>(_background_image)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-1);
	}
	if(!_background_image->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-2);
	}
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
	_background_image_region_division.reset(new MtRegionDivision(_background_image->get_width(),
		_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_background_image_region_division)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-3);
	}
	if(!_background_image_region_division->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-4);
	}
	//3.���ء�
	return(0);
}

/**
 * name: load_background_image
 * brief: ���ذ�ť����ͼƬ��
 * param: image - ָ��ͼƬ������ָ�����á�
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageButton::load_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	//1.���ݴ���ͼƬ���ñ���ͼƬ�������ж������Ƿ�ɹ���
	_background_image=image;
	if(!static_cast<bool>(_background_image)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-1);
	}
	if(!_background_image->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-2);
	}
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
	_background_image_region_division.reset(new MtRegionDivision(_background_image->get_width(),
		_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_background_image_region_division)){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-3);
	}
	if(!_background_image_region_division->is_valid()){
		_background_image.reset();
		_background_image_region_division.reset();
		return(-4);
	}
	//3.���ء�
	return(0);
}

/**
 * name: set_background_image_stretching_factors
 * brief: ���ñ���ͼƬ����ϵ����
 * param: stretch_left - �������ϵ����
 *        stretch_top - ��������ϵ����
 *        stretch_right - �������ϵ����
 *        stretch_bottom - �ײ�����ϵ����
 * return: --
 */
void MtImageButton::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: load_foreground_image
 * brief: ���ذ�ťǰ��ͼƬ��
 * param: image_path - ͼƬ·����
 *        image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageButton::load_foreground_image(
	const CString &image_path,const int image_rows,const int image_cols){
	//1.����ͼƬ·������ͼƬ���أ������жϼ����Ƿ�ɹ���
	_foreground_image.reset(new MtImage(image_path));
	if(!static_cast<bool>(_foreground_image)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-1);
	}
	if(!_foreground_image->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-2);
	}
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
	_foreground_image_region_division.reset(new MtRegionDivision(_foreground_image->get_width(),
		_foreground_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_foreground_image_region_division)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-3);
	}
	if(!_foreground_image_region_division->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-4);
	}
	//3.���ء�
	return(0);
}

/**
 * name: load_foreground_image
 * brief: ���ذ�ťǰ��ͼƬ��
 * param: foreground_image - ָ��ͼƬ������ָ�����á�
 *        image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageButton::load_foreground_image(
	PtrToImage foreground_image,const int image_rows,const int image_cols){
	//1.���ݴ��ݵ�ͼƬ���õ�ǰ��ť��ǰ��ͼƬ�������ж������Ƿ�ɹ���
	_foreground_image=foreground_image;
	if(!static_cast<bool>(_foreground_image)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-1);
	}
	if(!_foreground_image->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-2);
	}
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
	_foreground_image_region_division.reset(new MtRegionDivision(_foreground_image->get_width(),
		_foreground_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_foreground_image_region_division)){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-3);
	}
	if(!_foreground_image_region_division->is_valid()){
		_foreground_image.reset();
		_foreground_image_region_division.reset();
		return(-4);
	}
	//3.���ء�
	return(0);
}

/**
 * name: set_foreground_image_alignment
 * brief: ���ð�ťǰ��ͼƬͣ����ʽ��
 * param: alignment - ͣ����ʽ��
 * return: --
 */
void MtImageButton::set_foreground_image_alignment(const unsigned int alignment){
	_foreground_image_alignment=alignment;
}

/**
 * name: set_foreground_image_stretching_factors
 * brief: ����ǰ��ͼƬ����ϵ����
 * param: stretch_left - �������ϵ����
 *        stretch_top - ��������ϵ����
 *        stretch_right - �������ϵ����
 *        stretch_bottom - �ײ�����ϵ����
 * return: --
 */
void MtImageButton::set_foreground_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_foreground_image_stretching_factors.left=stretch_left;
	_foreground_image_stretching_factors.top=stretch_top;
	_foreground_image_stretching_factors.right=stretch_right;
	_foreground_image_stretching_factors.bottom=stretch_bottom;
	_is_foreground_image_stretched=TRUE;
}

/**
 * name: set_text_color
 * brief: �����ı���ɫ��
 * param: color_a - �ı���ɫa������
 *		  color_r - �ı���ɫr������
 *        color_g - �ı���ɫg������
 *        color_b - �ı���ɫb������
 * return: --
 */
void MtImageButton::set_text_color(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_text_color_a=color_a;
	_text_color_r=color_r;
	_text_color_g=color_g;
	_text_color_b=color_b;
}

/**
 * name: set_light_text_color
 * brief: ���ð�ť�ĸ����ı���ɫ��
 * param: color_a - �ı���ɫa������
 *		  color_r - �ı���ɫr������
 *        color_g - �ı���ɫg������
 *        color_b - �ı���ɫb������
 * return: --
 * remark: ����������ı������ı���ɫ��
 *         ��ť�ı�ֻ��ʾһ���ı���ɫ��
 */
void MtImageButton::set_light_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,const unsigned char color_b){
	_light_text_color_a=color_a;
	_light_text_color_r=color_r;
	_light_text_color_g=color_g;
	_light_text_color_b=color_b;
}

/**
 * name: PreSubclassWindow
 * brief: ���໯��ťǰ���ô����⺯�����ڴ���������ť
 *        �޸�Ϊ�Ի���
 * param: --
 * return: --
 */
void MtImageButton::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

/**
 * name: DrawItem
 * brief: ��ť�������⺯����
 * param: draw_items_info - ��ť������Ϣ��
 * return: --
 */
void MtImageButton::DrawItem(LPDRAWITEMSTRUCT draw_items_info){
	// TODO:  Add your code to draw the specified item
	//1.���㵱ǰ��ť״̬�������ť״̬�����仯��ˢ�¸����ڡ�
	//1-1.������ǰ�������������
	int state=0;
	//1-2.�����ǰ��ťΪ��ť���͡�
	if(TYPE_BUTTON==_type){
		if(ODS_DISABLED&draw_items_info->itemState){
			state=3;
		}else if((_is_checked)||(ODS_SELECTED&draw_items_info->itemState)){
			state=2;
		}else if(_is_mouse_hover){
			state=1;
		}
	}
	//1-3.�����ǰ��ťΪ�������͡�
	else{
		if(ODS_DISABLED&draw_items_info->itemState){
			if(_is_checked){
				state=5;
			}else{
				state=4;
			}
		}else if(_is_checked&&_is_mouse_hover){
			state=3;
		}else if(_is_checked){
			state=2;
		}else if(_is_mouse_hover){
			state=1;
		}
	}
	//2.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
	PtrToBitmap memory_bitmap(new MtBitmap(
		draw_items_info->rcItem.right-draw_items_info->rcItem.left,
		draw_items_info->rcItem.bottom-draw_items_info->rcItem.top));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//3.���ư�ť������
	draw_background(*memory_bitmap,state);
	//4.���ư�ťǰ����
	const CRect foreground_image_rect=draw_foreground(*memory_bitmap,draw_items_info->hDC,state);
	//5.���ư�ť�ı���
	draw_text(*memory_bitmap,foreground_image_rect,draw_items_info->hDC,state);
	//6.�ṩ����Ϊ��ť��ӻ������ݵĽӿڡ�
	draw_item(*memory_bitmap,draw_items_info->hDC,state);
	//7.���ڴ�λͼ�������ťDC�ϡ�
	memory_bitmap->paste_to_dc(draw_items_info->hDC,0,0);
}

/**
 * name: draw_item
 * breif: ���Ƶ�ǰ��ť���˺����ڴ�ʲôҲ��ʵ�֣�ֻ��
 *        Ϊ���ṩ�ӿڸ����࣬������ӻ������ݡ�
 * param: memory_bitmap - ��ǰ׼�����Ƶ�����λͼ��
 *        dc - ��ǰ׼�����Ƶ��ڴ�DC��
 *        state - ��ǰ��ť״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ�������򷵻�ֵС���㡣
 */
int MtImageButton::draw_item(MtBitmap &/*memory_bitmap*/,HDC /*dc*/,const unsigned int /*state*/){
	return(0);
}

BEGIN_MESSAGE_MAP(MtImageButton,CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/**
 * name: OnMouseMove
 * brief: ����ƶ���Ϣ��Ӧ�������ڴ������������hover��leave�¼���
 * param: flags - ����־
 *        point - ���λ�á�
 * return: --
 */
void MtImageButton::OnMouseMove(UINT flags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	if(!_is_mouse_tracking){
		TRACKMOUSEEVENT track_mouse_event;
		track_mouse_event.cbSize=sizeof(TRACKMOUSEEVENT);
		track_mouse_event.hwndTrack=m_hWnd;
		track_mouse_event.dwFlags=TME_LEAVE|TME_HOVER;
		track_mouse_event.dwHoverTime=1;
		_is_mouse_tracking=_TrackMouseEvent(&track_mouse_event);	
	}
	CButton::OnMouseMove(flags,point);
}

/**
 * name: OnMouseHover
 * brief: �����������Ϣ��Ӧ�������ڴ�����������������ϱ�Ǳ�����
 * param: flags - ����־
 *        point - ���λ�á�
 * return: --
 */
void MtImageButton::OnMouseHover(UINT flags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=TRUE;
	//update_parent_window();
	Invalidate(FALSE);
	CButton::OnMouseHover(flags,point);
}

/**
 * name: OnMouseLeave
 * brief: ������뿪��Ϣ��Ӧ�������ڴ�����ȡ�������Ӧ��Ǳ�����
 * param: --
 * return: --
 */
void MtImageButton::OnMouseLeave(){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=FALSE;
	_is_mouse_tracking=FALSE;
	//update_parent_window();
	Invalidate(FALSE);
	CButton::OnMouseLeave();
}

/**
 * name: OnEraseBkgnd
 * brief: ����������Ϣ��Ӧ����,��������������ť����Ҫ���ػ档
 * param: dc - ��ǰ�豸DC��
 * return: �������ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
BOOL MtImageButton::OnEraseBkgnd(CDC * /*dc*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CButton::OnEraseBkgnd(dc));
}

/**
 * name: update_parent_window
 * brief: ���°�ť���״��ڵ���Ӧ����
 * param: --
 * return: �����ǰ����ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageButton::update_parent_window(){
	CRect rect_parent_window(0,0,0,0);
	GetWindowRect(rect_parent_window);
	CWnd *parent=GetParent();
	if(0==parent){
		return(-1);
	}
	parent->ScreenToClient(rect_parent_window);
	parent->InvalidateRect(rect_parent_window);
	return(0);
}

/**
 * name: draw_background
 * brief: ���ư�ť�ı�����
 * param: memory_bitmap - �ڴ�λͼ��
 *		  state - ��ť��ǰ״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageButton::draw_background(MtBitmap &memory_bitmap,const unsigned int state){
	//1.�жϵ�ǰ����ͼƬ�Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_background_image)){
		return(-1);
	}
	if(!_background_image->is_valid()){
		return(-2);
	}
	//2.�жϵ�ǰ����ͼƬ�������Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_background_image_region_division)){
		return(-3);
	}
	if(!_background_image_region_division->is_valid()){
		return(-4);
	}
	//3.��ȡ����ͼƬ�ߴ磬�����ȡʧ��ֱ�ӷ��ش���
	const CRect image_rect=_background_image_region_division->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(-5);
	}
	//4.����ǰ����ͼƬ���Ƶ��ڴ�λͼ�ϡ�
	if(_is_background_image_stretched){
		if(_background_image->paste_to_bitmap_ex(&memory_bitmap,0,0,
			memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height(),
			_background_image_stretching_factors.left,
			_background_image_stretching_factors.top,
			_background_image_stretching_factors.right,
			_background_image_stretching_factors.bottom)<0){
			return(-6);
		}
	}else{
		if(_background_image->paste_to_bitmap(&memory_bitmap,0,0,
			memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height())<0){
			return(-7);
		}
	}
	//5.�ɹ����ء�
	return(0);
}

/**
 * name: draw_foreground
 * brief: ���ư�ťǰ����
 * param: memory_bitmap - �ڴ�λͼ��
 *        dc - ��ͼDC.
 *		  state - ��ť״̬��
 * return: �������ִ�гɹ�����ǰ��ͼƬλ�ã����򷵻�һ���յ�λ����Ϣ��
 *         ����CRect::IsRectEmpty����ȷ�ϣ���
 */
CRect MtImageButton::draw_foreground(MtBitmap &memory_bitmap,HDC dc,const unsigned int state){
	//1.�жϵ�ǰǰ��ͼƬ�Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_foreground_image)){
		return(CRect(0,0,0,0));
	}
	if(!_foreground_image->is_valid()){
		return(CRect(0,0,0,0));
	}
	//2.�жϵ�ǰǰ��ͼƬ�������Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_foreground_image_region_division)){
		return(CRect(0,0,0,0));
	}
	if(!_foreground_image_region_division->is_valid()){
		return(CRect(0,0,0,0));
	}
	//3.��ȡǰ��ͼƬ�ߴ磬�����ȡʧ��ֱ�ӷ��ش���
	const CRect image_rect=_foreground_image_region_division->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(CRect(0,0,0,0));
	}
	//4.����ǰ��ͼƬͣ����ʽ������ǰ��ͼƬ���λ�á�
	int dest_x=0;
	if(ALIGNMENT_HCENTER&_foreground_image_alignment){
		dest_x=(memory_bitmap.get_width()-image_rect.Width())/2;
	}else if(ALIGNMENT_RIGHT&_foreground_image_alignment){
		dest_x=memory_bitmap.get_width()-image_rect.Width()-IMAGE_MARGIN;
	}else{
		dest_x=IMAGE_MARGIN;
	}
	int dest_y=0;
	if(ALIGNMENT_VCENTER&_foreground_image_alignment){
		dest_y=(memory_bitmap.get_height()-image_rect.Height())/2;
	}else if(ALIGNMENT_BOTTOM&_foreground_image_alignment){
		dest_y=memory_bitmap.get_height()-image_rect.Height()-IMAGE_MARGIN;
	}else{
		/*dest_y=IMAGE_MARGIN;*/
		CSize text_size(0,0);
		CString text(_T(""));
		GetWindowText(text);
		MtGdiplus::calculate_text_size(text,dc,static_cast<HFONT>(
			GetFont()->GetSafeHandle()),text_size);
		dest_y=(memory_bitmap.get_height()-image_rect.Height()-text_size.cy)/2;
	}
	if((TYPE_BUTTON==_type)&&(2==state)){
		++dest_x;
		++dest_y;
	}
	//5.����ǰǰ��ͼƬ���Ƶ��ڴ�λͼ�ϡ�
	if(_is_foreground_image_stretched){
		if(_foreground_image->paste_to_bitmap_ex(&memory_bitmap,
			dest_x,dest_y,image_rect.Width(),image_rect.Height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height(),
			_foreground_image_stretching_factors.left,
			_foreground_image_stretching_factors.top,
			_foreground_image_stretching_factors.right,
			_foreground_image_stretching_factors.bottom)<0){
			return(CRect(0,0,0,0));
		}
	}else{
		if(_foreground_image->paste_to_bitmap(&memory_bitmap,
			dest_x,dest_y,image_rect.Width(),image_rect.Height(),
			image_rect.left,image_rect.top,image_rect.Width(),
			image_rect.Height())<0){
			return(CRect(0,0,0,0));
		}
	}
	//6.�ɹ����ء�
	return(CRect(dest_x,dest_y,dest_x+image_rect.Width(),dest_y+image_rect.Height()));
}

/**
 * name: draw_text
 * brief: ���ư�ť���⡣
 * param: memory_bitmap - �ڴ�λͼ��
 *		  foreground_image_rect - ǰ��ͼƬλ������
 *        dc - ��ͼ�豸DC��
 *        state - ��ť״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageButton::draw_text(MtBitmap &memory_bitmap,
	const CRect &foreground_image_rect,HDC dc,const unsigned int state){
	//1.��ȡ��ǰ��ť���⡣
	CString text(_T(""));
	GetWindowText(text);
	if(text.IsEmpty()){
		return(0);
	}
	//2.�����ǰ��ťǰ��ͼƬλ��Ϊ�ա�
	if(foreground_image_rect.IsRectEmpty()){
		//2-1.�����ı�λ�á�
		int dest_x=0;
		int dest_y=0;
		int dest_width=memory_bitmap.get_width();
		int dest_height=memory_bitmap.get_height();
		if((TYPE_BUTTON==_type)&&(2==state)){
			++dest_x;
			++dest_y;
		}
		//2-2.�����ı����ơ�
		//2-2-1.�����ǰ��ť����ʧЧ״̬��
		if(3==state){
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,DISABLE_TEXT_COLOR_A,DISABLE_TEXT_COLOR_R,
				DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B)<0){
				return(-1);
			}
		}
		//2-2-2.�����ǰ��ť����ʹ��״̬��
		else{
			unsigned char text_color_a=_text_color_a;
			unsigned char text_color_r=_text_color_r;
			unsigned char text_color_g=_text_color_g;
			unsigned char text_color_b=_text_color_b;
			if(0!=_light_text_color_a){
				if((TYPE_BUTTON==_type)&&((1==state)||(2==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}else if(((TYPE_CHECK_BOX==_type)||(TYPE_RADIO_BOX==_type))&&
					((1==state)||(3==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}
			}
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,text_color_a,text_color_r,text_color_g,
				text_color_b)<0){
				return(-2);
			}
		}
	}
	//3.�����ǰ��ťǰ��ͼƬλ�ò�Ϊ�ա�
	else{
		//3-1.�����ı�λ�á�
		int dest_x=0;
		int dest_y=0;
		int dest_width=memory_bitmap.get_width();
		int dest_height=memory_bitmap.get_height();
		if(ALIGNMENT_HCENTER&_foreground_image_alignment){
			if(ALIGNMENT_BOTTOM&_foreground_image_alignment){
				dest_y+=IMAGE_MARGIN;
				dest_height=foreground_image_rect.top-IMAGE_MARGIN-dest_y;
			}else{
				dest_y=foreground_image_rect.bottom+IMAGE_MARGIN;
				dest_height=dest_height-IMAGE_MARGIN-dest_y;
			}
		}else if(ALIGNMENT_RIGHT&_foreground_image_alignment){
			dest_x+=IMAGE_MARGIN;
			dest_width=foreground_image_rect.left-IMAGE_MARGIN-dest_x;
		}else{
			dest_x=foreground_image_rect.right+IMAGE_MARGIN;
			dest_width=dest_width-IMAGE_MARGIN-dest_x;
		}
		if((TYPE_BUTTON==_type)&&(2==state)){
			++dest_x;
			++dest_y;
		}
		//3-2.�����ı����ơ�
		//3-2-1.�����ǰ��ť����ʧЧ״̬��
		if(((TYPE_BUTTON==_type)&&(3==state))||(4==state)||(5==state)){
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,DISABLE_TEXT_COLOR_A,DISABLE_TEXT_COLOR_R,
				DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B)<0){
				return(-3);
			}
		}
		//3-2-2.�����ǰ��ť����ʹ��״̬��
		else{
			unsigned char text_color_a=_text_color_a;
			unsigned char text_color_r=_text_color_r;
			unsigned char text_color_g=_text_color_g;
			unsigned char text_color_b=_text_color_b;
			if(0!=_light_text_color_a){
				if((TYPE_BUTTON==_type)&&((1==state)||(2==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}else if(((TYPE_CHECK_BOX==_type)||(TYPE_RADIO_BOX==_type))&&
					((1==state)||(3==state))){
					text_color_a=_light_text_color_a;
					text_color_r=_light_text_color_r;
					text_color_g=_light_text_color_g;
					text_color_b=_light_text_color_b;
				}
			}
			if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(
				GetFont()->GetSafeHandle()),dest_x,dest_y,dest_width,
				dest_height,text_color_a,text_color_r,text_color_g,
				text_color_b)<0){
				return(-4);
			}
		}
	}
	//4.�ɹ����ء�
	return(0);
}