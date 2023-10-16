// source-code/control/MtImageComboBox.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageComboBox.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"
#include<assert.h>

IMPLEMENT_DYNAMIC(MtImageComboBox,CComboBox)

/**
 * name: MtImageComboBox
 * brief: ���캯����
 * param: --
 * return: --
 */
MtImageComboBox::MtImageComboBox()
	:CComboBox()
	,_is_mouse_tracking(FALSE)
	,_is_mouse_hover(FALSE)
	,_is_list_box_visible(FALSE)
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_text_alignment(0)
	,_text_color_a(0)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0)
	,_list_box_background_image()
	,_list_box_background_image_slicer()
	,_is_list_box_background_image_stretched(FALSE)
	,_list_box_background_image_stretching_factors()
	,_list_box_text_alignment(0)
	,_list_box_text_color_a(0)
	,_list_box_text_color_r(0)
	,_list_box_text_color_g(0)
	,_list_box_text_color_b(0){
}

/**
 * name: MtImageComboBox
 * brief: ����������
 * param: --
 * return: --
 */
MtImageComboBox::~MtImageComboBox(){
}

/**
 * name: load_background_image
 * brief: ���ذ�ť����ͼƬ��
 * param: image_path - ͼƬ·����
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::load_background_image(const CString &image_path,
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
 * param: image - ָ�򱳾�ͼƬ������ָ�롣
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::load_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	//1.����ͼƬ����ָ�����ͼƬ���أ������жϼ����Ƿ�ɹ���
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
void MtImageComboBox::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: set_text_alignment
 * brief: �����ı�ͣ����ʽ��
 * param: alignment - �ı�ͣ����ʽ��
 * return: --
 */
void MtImageComboBox::set_text_alignment(const unsigned int alignment){
	_text_alignment=alignment;
}

/**
 * name: set_text_color
 * brief: �����ı���ɫ��
 * param: color_a - �ı���ɫ��a������
 *        color_r - �ı���ɫ��r������
 *        color_g - �ı���ɫ��g������
 *        color_b - �ı���ɫ��b������
 *        is_invalidate - �Ƿ�ˢ��������
 * return: --
 */
void MtImageComboBox::set_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_invalidate/*=FALSE*/){
	_text_color_a=color_a;
	_text_color_r=color_r;
	_text_color_g=color_g;
	_text_color_b=color_b;
	if(is_invalidate){
		Invalidate(FALSE);
	}
}

/**
 * name: load_list_box_background_image
 * brief: �������������б�򱳾�ͼƬ��
 * param: image_path - ͼƬ·����
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: ��� ������ѡ���ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::load_list_box_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	//1.����ͼƬ·������ͼƬ���أ������жϼ����Ƿ�ɹ���
	_list_box_background_image.reset(new MtImage(image_path));
	if(!static_cast<bool>(_list_box_background_image)){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-1);
	}
	if(!_list_box_background_image->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-2);
	}
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
	_list_box_background_image_slicer.reset(new MtRegionDivision(_list_box_background_image->get_width(),
		_list_box_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_list_box_background_image_slicer)){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-3);
	}
	if(!_list_box_background_image_slicer->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-4);
	}
	//3.���ء�
	return(0);
}

/**
 * name: load_list_box_background_image
 * brief: �������������б�򱳾�ͼƬ��
 * param: image - ָ��ͼƬ������ָ�롣
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: ��� ������ѡ���ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::load_list_box_background_image(
	PtrToImage image,const int image_rows,const int image_cols){
	//1.����ͼƬ����ָ�����ͼƬ���أ������жϼ����Ƿ�ɹ���
	_list_box_background_image=image;
	if(!static_cast<bool>(_list_box_background_image)){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-1);
	}
	if(!_list_box_background_image->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image.reset();
		return(-2);
	}
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
	_list_box_background_image_slicer.reset(new MtRegionDivision(_list_box_background_image->get_width(),
		_list_box_background_image->get_height(),image_rows,image_cols));
	if(!static_cast<bool>(_list_box_background_image_slicer)){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-3);
	}
	if(!_list_box_background_image_slicer->is_valid()){
		_list_box_background_image.reset();
		_list_box_background_image_slicer.reset();
		return(-4);
	}
	//3.���ء�
	return(0);
}

/**
 * name: set_list_box_background_image_stretching_factors
 * brief: �������������б�򱳾�ͼƬ����ϵ����
 * param: stretch_left - �������ϵ����
 *        stretch_top - ��������ϵ����
 *        stretch_right - �������ϵ����
 *        stretch_bottom - �ײ�����ϵ����
 * return: --
 */
void MtImageComboBox::set_list_box_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_list_box_background_image_stretching_factors.left=stretch_left;
	_list_box_background_image_stretching_factors.top=stretch_top;
	_list_box_background_image_stretching_factors.right=stretch_right;
	_list_box_background_image_stretching_factors.bottom=stretch_bottom;
	_is_list_box_background_image_stretched=TRUE;
}

/**
 * name: set_list_box_text_alignment
 * brief: �������������б���ı�ͣ����ʽ��
 * param: alignment - ͣ����ʽ��
 * return: --
 */
void MtImageComboBox::set_list_box_text_alignment(const unsigned int alignment){
	_list_box_text_alignment=alignment;
}

/**
 * name: set_list_box_text_color
 * brief: �������������б���ı���ɫ��
 * param: color_a - �ı���ɫ��a������
 *        color_r - �ı���ɫ��r������
 *        color_g - �ı���ɫ��g������
 *        color_b - �ı���ɫ��b������
 *        is_invalidate - �Ƿ�ˢ��������
 * return: --
 */
void MtImageComboBox::set_list_box_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_invalidate/*=FALSE*/){
	_list_box_text_color_a=color_a;
	_list_box_text_color_r=color_r;
	_list_box_text_color_g=color_g;
	_list_box_text_color_b=color_b;
	if(is_invalidate){
		Invalidate(FALSE);
	}
}

/**
 * name: PreSubclassWindow
 * brief: �������໯ǰ���ô����⺯�����ڴ�����ȥ��
 *        ���������б��ı߿�
 * param: --
 * return: --
 */
void MtImageComboBox::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	//1.������ǰ�����������������
	COMBOBOXINFO combo_box_info;
	combo_box_info.cbSize=sizeof(COMBOBOXINFO);
	//2.��ȡ��ǰ��������Ϣ��
	const BOOL result=GetComboBoxInfo(&combo_box_info);
	assert(TRUE==result);
	//3.��ȡ��ǰ�б����ָ�롣
	CWnd *list_box=CWnd::FromHandle(combo_box_info.hwndList);
	assert(0!=list_box);
	//4.ȥ���б��ı߿�
	list_box->ModifyStyle(WS_BORDER,0);
	//5.���û�����Ӧ���⺯����
	CComboBox::PreSubclassWindow();
}

/**
 * name: DrawItem
 * brief: ��ť�������⺯����
 * param: lpDrawItemStruct - ��ť������Ϣ��
 * return: --
 */
void MtImageComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){
	//TODO:  Add your code to draw the specified item
	//A.�����ǰ���Ƶ�Ϊ�������ı��༭�����ı�����ˢ�¿ؼ�������OnPaint�������ơ�
	if((static_cast<int>(lpDrawItemStruct->itemID)>=0)&&(
		ODS_COMBOBOXEDIT&lpDrawItemStruct->itemState)){
		Invalidate(FALSE);
	}
	//B.�����ǰ���Ƶ�Ϊ�������е��ı���
	else if(static_cast<int>(lpDrawItemStruct->itemID)>=0){
		//1.���㵱ǰ���ڳߴ硣
		CRect window_rect(lpDrawItemStruct->rcItem);
		//2.���㵱ǰ������״̬��
		unsigned int state=0;
		if(ODS_SELECTED&lpDrawItemStruct->itemState){
			state=1;
			/*
			if(GetCount()-1==static_cast<int>(lpDrawItemStruct->itemID)){
				state=3;
			}else{
				state=2;
			}
			*/
		}else{
			state=0;
			/*
			if(GetCount()-1==static_cast<int>(lpDrawItemStruct->itemID)){
				state=1;
			}else{
				state=0;
			}
			*/
		}
		//3.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
		PtrToBitmap memory_bitmap(new MtBitmap(
			window_rect.Width(),window_rect.Height()));
		if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
			return;
		}
		//4.���ݵ�ǰ�б��״̬�������б�򱳾���
		draw_list_box_background(*memory_bitmap,state);
		//5.���е�ǰ�ı��Ļ��ơ�
		CString text(_T(""));
		GetLBText(lpDrawItemStruct->itemID,text);
		draw_list_box_text(*memory_bitmap,lpDrawItemStruct->hDC,text);
		//6.���ڴ�λͼ�������ͼDC�豸�ϡ�
		memory_bitmap->paste_to_dc(
			lpDrawItemStruct->hDC,window_rect.left,window_rect.top);
	}
}

/**
 * name: MeasureItem
 * brief: �Ի�ʱ�������������ѡ��ߴ硣
 * param: lpMeasureItemStruct - ָ���б�ѡ����Ϣ�ṹ���ָ�롣
 * return: --
 */
void MtImageComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){
	// TODO:  Add your code to determine the size of specified item
	if(static_cast<int>(lpMeasureItemStruct->itemID)>=0){
		/*
		//1.��ȡ��ǰ�б���ı���
		LPCTSTR text=reinterpret_cast<LPCTSTR>(lpMeasureItemStruct->itemData);
		assert(0!=text);
		//2.��ȡ��ǰ�ı��ߴ硣
		CSize text_size(0,0);
		CDC *dc=GetDC();
		assert(0!=dc);
		text_size=dc->GetTextExtent(text);
		ReleaseDC(dc);
		//3.���õ�ǰ������߶ȡ�
		*/
		lpMeasureItemStruct->itemHeight=25/*static_cast<int>(1.5*text_size.cy)*/;
	}
}

BEGIN_MESSAGE_MAP(MtImageComboBox,CComboBox)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(CBN_DROPDOWN,&MtImageComboBox::OnCbnDropdown)
	ON_CONTROL_REFLECT(CBN_CLOSEUP,&MtImageComboBox::OnCbnCloseup)
END_MESSAGE_MAP()

/**
 * name: MtImageComboBox
 * brief: �ؼ�������Ϣ��Ӧ����������ʵ�ֿؼ����ơ�
 * param: --
 * return: --
 */
void MtImageComboBox::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.���㵱ǰ��ť״̬�������ť״̬�����仯��ˢ�¸����ڡ�
	int state=0;
	if(!IsWindowEnabled()){
		state=3;
	}else if(_is_list_box_visible){
		state=2;
	}else if(_is_mouse_hover){
		state=1;
	}
	//2.��ȡ��ǰ���ڳߴ硣
	CRect window_rect;
	GetClientRect(window_rect);
	//3.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
	PtrToBitmap memory_bitmap(new MtBitmap(
		window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//4.����������ؼ�������
	draw_background(*memory_bitmap,state);
	//5.���Ƶ�ǰ�������ı���
	draw_text(*memory_bitmap,state,dc.GetSafeHdc());
	//6.���ڴ�λͼ�������ͼDC�豸�ϡ�
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	// Do not call CComboBox::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: �ؼ�����������Ϣ��Ӧ������������Ҫ������ֹ����Ҫ
 *        ���ػ档
 * param: pDC - ��ͼDC�豸��
 * return: �˴�һֱ����TRUE��
 */
BOOL MtImageComboBox::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CComboBox::OnEraseBkgnd(pDC));
}

/**
 * name: OnMouseMove
 * brief: ����ƶ���Ϣ��Ӧ�������ڴ������������hover��leave�¼���
 * param: flags - ����־
 *        point - ���λ�á�
 * return: --
 */
void MtImageComboBox::OnMouseMove(UINT nFlags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	if(!_is_mouse_tracking){
		TRACKMOUSEEVENT track_mouse_event;
		track_mouse_event.cbSize=sizeof(TRACKMOUSEEVENT);
		track_mouse_event.hwndTrack=m_hWnd;
		track_mouse_event.dwFlags=TME_LEAVE|TME_HOVER;
		track_mouse_event.dwHoverTime=1;
		_is_mouse_tracking=_TrackMouseEvent(&track_mouse_event);	
	}
	CComboBox::OnMouseMove(nFlags, point);
}

/**
 * name: OnMouseHover
 * brief: �����������Ϣ��Ӧ�������ڴ�����������������ϱ�Ǳ�����
 * param: flags - ����־
 *        point - ���λ�á�
 * return: --
 */
void MtImageComboBox::OnMouseHover(UINT nFlags,CPoint point){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=TRUE;
	Invalidate(FALSE);
	CComboBox::OnMouseHover(nFlags, point);
}

/**
 * name: OnMouseLeave
 * brief: ������뿪��Ϣ��Ӧ�������ڴ�����ȡ�������Ӧ��Ǳ�����
 * param: --
 * return: --
 */
void MtImageComboBox::OnMouseLeave(){
	// TODO: Add your message handler code here and/or call default
	_is_mouse_hover=FALSE;
	_is_mouse_tracking=FALSE;
	Invalidate(FALSE);
	CComboBox::OnMouseLeave();
}

/**
 * name: CtlColor
 * brief: ��ɫ������Ϣ��������Ҫ�������ؼ�͸����ֻ��ʾ�Ի沿�֡�
 * param: pDC - ��ͼDC�豸��
 *        nCtlColor - �ؼ���ɫ���롣
 * return: ���Ƿ��ؿջ�ˢ��
 */
HBRUSH MtImageComboBox::CtlColor(CDC *pDC,UINT /*nCtlColor*/){
	// TODO:  Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	return((HBRUSH)GetStockObject(NULL_BRUSH));
	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	//return(NULL);
}


/**
 * name: OnCbnDropdown
 * brief: ����������ʾ�б��ʱ���ô���Ϣ��Ӧ����������
 *        �������������ؼ����б�����ʾ��
 * param: --
 * return: --
 */
void MtImageComboBox::OnCbnDropdown(){
	// TODO: Add your control notification handler code here
	_is_list_box_visible=TRUE;
	Invalidate(FALSE);
}

/**
 * name: OnCbnCloseup
 * brief: ��������ر��б��ʱ���ô���Ϣ��Ӧ����������
 *        ����ȡ��������ؼ����б�����ʾ��ǡ�
 * param: --
 * return: --
 */
void MtImageComboBox::OnCbnCloseup(){
	// TODO: Add your control notification handler code here
	_is_list_box_visible=FALSE;
	Invalidate(FALSE);
}

/**
 * name: draw_background
 * brief: ����������ı�����
 * param: memory_bitmap - �ڴ�λͼ��
 *		  state - ������ǰ״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::draw_background(MtBitmap &memory_bitmap,const unsigned int state){
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
		if(_background_image->paste_to_bitmap_ex(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height(),
			_background_image_stretching_factors.left,
			_background_image_stretching_factors.top,
			_background_image_stretching_factors.right,
			_background_image_stretching_factors.bottom)<0){
			return(-6);
		}
	}else{
		if(_background_image->paste_to_bitmap(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height())<0){
			return(-7);
		}
	}
	//5.�ɹ����ء�
	return(0);
}

/**
 * name: draw_text
 * brief: �����������ı���
 * param:  state - ��ǰ�ؼ�״̬��
 *         dc - ��ͼ�豸DC��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::draw_text(MtBitmap &memory_bitmap,const unsigned int state,const HDC dc){
	//1.�����ǰDC�豸�Ƿ����򷵻ش�����롣
	if(0==dc){
		return(-1);
	}
	//2.��ȡ��ǰ������Ӧ����ʾ���ı���
	int item=GetCurSel();
	if(CB_ERR==item){
		return(0);
	}
	CString text(_T(""));
	GetLBText(item,text);
	if(text.IsEmpty()){
		return(-2);
	}
	//3.���㵱ǰ�ı�ͣ����ʽ��
	MtBitmap::Alignment text_h_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_text_alignment&ALIGNMENT_HCENTER){
		text_h_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_text_alignment&ALIGNMENT_RIGHT){
		text_h_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	MtBitmap::Alignment text_v_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_text_alignment&ALIGNMENT_VCENTER){
		text_v_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_text_alignment&ALIGNMENT_BOTTOM){
		text_v_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	//4.���Ƶ�ǰ�ı���
	if(3==state){
		if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
			TEXT_MARGIN,TEXT_MARGIN,
			memory_bitmap.get_width()-_background_image_stretching_factors.right-TEXT_MARGIN,
			memory_bitmap.get_height()-TEXT_MARGIN,
			DISABLE_TEXT_COLOR_A,DISABLE_TEXT_COLOR_R,DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B,
			text_h_alignment,text_v_alignment)<0){
			return(-3);
		}
	}else{
		if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
			TEXT_MARGIN,TEXT_MARGIN,
			memory_bitmap.get_width()-_background_image_stretching_factors.right-TEXT_MARGIN,
			memory_bitmap.get_height()-TEXT_MARGIN,
			_text_color_a,_text_color_r,_text_color_g,_text_color_b,
			text_h_alignment,text_v_alignment)<0){
			return(-4);
		}
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}

/**
 * name: draw_list_box_background
 * breif: �������������б�򱳾���
 * param: memory_bitmap - �ڴ�λͼ��
 *		  state - ��ǰ���������б��״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::draw_list_box_background(MtBitmap &memory_bitmap,const unsigned int state){
	//1.�жϵ�ǰ����ͼƬ�Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_list_box_background_image)){
		return(-1);
	}
	if(!_list_box_background_image->is_valid()){
		return(-2);
	}
	//2.�жϵ�ǰ����ͼƬ�������Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_list_box_background_image_slicer)){
		return(-3);
	}
	if(!_list_box_background_image_slicer->is_valid()){
		return(-4);
	}
	//3.��ȡ����ͼƬ�ߴ磬�����ȡʧ��ֱ�ӷ��ش���
	const CRect image_rect=_list_box_background_image_slicer->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(-5);
	}
	//4.����ǰ����ͼƬ���Ƶ��ڴ�λͼ�ϡ�
	if(_is_list_box_background_image_stretched){
		if(_list_box_background_image->paste_to_bitmap_ex(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height(),
			_list_box_background_image_stretching_factors.left,
			_list_box_background_image_stretching_factors.top,
			_list_box_background_image_stretching_factors.right,
			_list_box_background_image_stretching_factors.bottom)<0){
			return(-6);
		}
	}else{
		if(_list_box_background_image->paste_to_bitmap(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height())<0){
			return(-7);
		}
	}
	//5.�ɹ����ء�
	return(0);
}

/**
 * name: draw_list_box_text
 * brief: �������������б����ı���
 * param: memory_bitmap - �ڴ�λͼ��
 *        dc - ��ͼʹ�õ��豸DC��
 *        text - �ı����ݡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageComboBox::draw_list_box_text(
	MtBitmap &memory_bitmap,const HDC dc,const CString &text){
	//1.�����ǰDC�豸���Ϸ�����ֱ�ӷ��ش�����롣
	if(0==dc){
		return(-1);
	}
	//2.�����ǰ�ı�Ϊ�գ���ֱ�ӷ��ء�
	if(text.IsEmpty()){
		return(0);
	}
	//3.���㵱ǰ�ı�ͣ����ʽ��
	MtBitmap::Alignment text_h_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_list_box_text_alignment&ALIGNMENT_HCENTER){
		text_h_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_list_box_text_alignment&ALIGNMENT_RIGHT){
		text_h_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	MtBitmap::Alignment text_v_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_list_box_text_alignment&ALIGNMENT_VCENTER){
		text_v_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_list_box_text_alignment&ALIGNMENT_BOTTOM){
		text_v_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	//3.���Ƶ�ǰ�ı���
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		TEXT_MARGIN,TEXT_MARGIN,memory_bitmap.get_width()-TEXT_MARGIN,
		memory_bitmap.get_height()-TEXT_MARGIN,
		_list_box_text_color_a,_list_box_text_color_r,
		_list_box_text_color_g,_list_box_text_color_b,
		text_h_alignment,text_v_alignment)<0){
		return(-2);
	}
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}