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
 * brief: ���캯����
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
 * brief: ����������
 * param: --
 * return: --
 */
MtImageListCtrl::~MtImageListCtrl(){
	delete _header;
}

/**
 * name: load_item_background_image
 * brief: �����б�����б���ı���ͼƬ��
 * param: image_path - ͼƬ·����
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageListCtrl::load_item_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	//1.����ͼƬ·������ͼƬ���أ������жϼ����Ƿ�ɹ���
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
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
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
	//3.���ء�
	return(0);
}

/**
 * name: load_item_background_image
 * brief: �����б�����б���ı���ͼƬ��
 * param: image - ָ��ͼƬ������ָ�����á�
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageListCtrl::load_item_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	//1.���ݴ���ͼƬ���ñ���ͼƬ�������ж������Ƿ�ɹ���
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
	//2.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
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
	//3.���ء�
	return(0);
}

/**
 * name: set_item_background_image_stretching_factors
 * brief: �����б����ͼƬ����ϵ����
 * param: stretch_left - �������ϵ����
 *        stretch_top - ��������ϵ����
 *        stretch_right - �Ҳ�����ϵ����
 *        stretch_bottom - �ײ�����ϵ����
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
 * brief: �����б�����ı���ɫ��
 * param: color_a - ��ɫA�ɷ֡�
 *        color_b - ��ɫB�ɷ֡�
 *        color_c - ��ɫC�ɷ֡�
 *        color_d - ��ɫD�ɷ֡�
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
 * brief: �����б����ı��ĸ�����ɫ��
 * param: color_a - ��ɫA�ɷ֡�
 *        color_b - ��ɫB�ɷ֡�
 *        color_c - ��ɫC�ɷ֡�
 *        color_d - ��ɫD�ɷ֡�
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
 * brief: �����б�����ı�ͣ����ʽ��
 * param: alignment - �ı�ͣ����ʽ��
 * return: --
 */
void MtImageListCtrl::set_item_text_alignment(const unsigned int alignment){
	_item_text_alignment=alignment;
}

/**
 * name: get_item_text_alignment
 * brief: ��ȡ�б�����ı�ͣ����ʽ��
 * param: --
 * return: �����б�����ı�ͣ����ʽ��
 */
unsigned int MtImageListCtrl::get_item_text_alignment() const{
	return(_item_text_alignment);
}

/**
 * name: set_item_row_height
 * brief: �����б�����иߡ�
 * param: height - �иߡ�
 * return: --
 */
void MtImageListCtrl::set_item_row_height(const unsigned int height){
	_item_row_height=height;
}

/**
 * name: get_item_row_height
 * brief: ��ȡ�б�����иߡ�
 * param: --
 * return: �����иߡ�
 */
unsigned int MtImageListCtrl::get_item_row_height() const{
	return(_item_row_height);
}

/**
 * name: load_header_item_background_image
 * brief: ���ر���ͷ�����ͼƬ��
 * param: image_path - ͼƬ·����
 *        image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageListCtrl::load_header_item_background_image(const CString &image_path,
	const int image_rows,const int image_cols){
	return(_header->load_item_background_image(image_path,image_rows,image_cols));
}

/**
 * name: load_header_item_background_image
 * brief: ���ر���ͷ�����ͼƬ��
 * param: image - ָ��ͼƬ������ָ�����á�
 *        image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageListCtrl::load_header_item_background_image(PtrToImage image,
	const int image_rows,const int image_cols){
	return(_header->load_item_background_image(image,image_rows,image_cols));
}

/**
 * name: set_header_item_background_image_stretching_factors
 * brief: ���ñ���ͷ�����ͼƬ����ϵ����
 * param: stretch_left - �������ϵ����
 *        stretch_top - ��������ϵ����
 *        stretch_right - �Ҳ�����ϵ����
 *        stretch_bottom - �ײ�����ϵ����
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
 * brief: ���ñ���ͷ������ı���ɫ��
 * param: color_a - ��ɫA�ɷ֡�
 *        color_b - ��ɫB�ɷ֡�
 *        color_c - ��ɫC�ɷ֡�
 *        color_d - ��ɫD�ɷ֡�
 * return: --
 */
void MtImageListCtrl::set_header_item_text_color(const unsigned char &color_a,
	const unsigned char &color_r,const unsigned char &color_g,const unsigned char &color_b){
	_header->set_item_text_color(color_a,color_r,color_g,color_b);
}

/**
 * name: set_header_item_text_alignment
 * brief: ���ñ���ͷ������ı�ͣ����ʽ��
 * param: alignment - �ı�ͣ����ʽ��
 * return: --
 */
void MtImageListCtrl::set_header_item_text_alignment(const unsigned int alignment){
	_header->set_item_text_alignment(alignment);
}

/**
 * name: get_header_item_text_alignment
 * brief: ��ȡ����ͷ������ı�ͣ����ʽ��
 * param: --
 * return: ���ر���ͷ������ı�ͣ����ʽ��
 */
unsigned int MtImageListCtrl::get_header_item_text_alignment() const{
	return(_header->get_item_text_alignment());
}

/**
 * name: PreSubclassWindow
 * brief: �������໯���⺯����
 * param: --
 * return: --
 */
void MtImageListCtrl::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	//////////////////////////////////////////////////////////////////
	//1.�޸ĵ�ǰ���ڷ��ʹ���Ϊ�Ի���
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	//2.�޸ĵ�ǰ���������ڴ�����̡�
	HWND header=GetHeaderCtrl()->GetSafeHwnd();
	_header->SubclassWindow(header);
	//////////////////////////////////////////////////////////////////
	CListCtrl::PreSubclassWindow();
}

/**
 * name: DrawItem
 * breif: �ؼ��Ի����⺯����
 * param: lpDrawItemStruct - ִ���Ի�ؼ�״̬�ṹ�塣
 * return: --
 */
void MtImageListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){
	// TODO:  Add your code to draw the specified item
	//1.�Զ������͡�
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	//2.��������������ڴ�λͼ�������жϴ����Ƿ�ɹ���
	//2-1.��ȡ��ǰ��ͼ����ߴ硣
	const CRect draw_rect(lpDrawItemStruct->rcItem);
	//2-2.�����ڴ�λͼ���������ʧ����ֱ�ӷ��ء�
	PtrToBitmap memory_bitmap(new MtBitmap(draw_rect.Width(),draw_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//3.���㵱ǰ�б����״̬��1 ��ͨ״̬��3 ����״̬����
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
	//4.��ȡ��ǰ�б������������ߴ硣
	const int cols=_header->GetItemCount();
	//5.������ǰ�б����ÿһ��,���Ҷ�ÿһ����л��ơ�
	for(int item=0;item!=cols;++item){
		//5-1.�����Ƿ�Ϊ������������ǰ�ؼ�״̬��
		unsigned int state_t=state;
		if((1==state)&&(0==item)){
			state_t=0;
		}else if((3==state)&&(0==item)){
			state_t=2;
		}
		//5-2.���㵱ǰ��ĳߴ硣
		CRect item_rect;
		if(0!=item){
			if(!GetSubItemRect(lpDrawItemStruct->itemID,
				item,LVIR_BOUNDS,item_rect)){
				continue;
			}
		}else if(1==cols){//�����ǰ�б��ֻ��1�С�
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
		//5-3.�ñ�������Ӧ����ĳߴ�Ч���б���ĳߴ磨�����������ˮƽ����������ʱ�����������б��ͬ������
		CRect hearder_item_rect;
		if(!_header->GetItemRect(item,hearder_item_rect)){
			continue;
		}
		item_rect.left=hearder_item_rect.left;
		item_rect.right=hearder_item_rect.right;
		//5-4.���Ƶ�ǰ�б���е��
		draw_item_background(*memory_bitmap,item_rect,state_t);
		//5-5.�����б��
		draw_item(*memory_bitmap,lpDrawItemStruct->itemID,item,item_rect,state_t);
		//5-6.���Ƶ�ǰ�б�������֡�
		const CString text=GetItemText(lpDrawItemStruct->itemID,item);
		draw_item_text(*memory_bitmap,text,item_rect,state_t,lpDrawItemStruct->hDC);
	}
	//6.������ͼƬ�������ͼ�豸�ϡ�
	memory_bitmap->paste_to_dc(lpDrawItemStruct->hDC,draw_rect.left,draw_rect.top);
}

/**
 * name: MeasureItem
 * brief: �б���߶ȵ������⺯����
 * param: lpMeasureItemStruct - ָ���б���ߴ�ṹ�塣
 * return: --
 */
void MtImageListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct){
	lpMeasureItemStruct->itemHeight=_item_row_height;
}

/**
 * name: draw_item
 * brief: ���⺯���������б��
 * param: memory_bitmap - �ڴ�λͼ���á�
 *        item - �б��
 *        sub_item - �б����
 *        item_rect - �б���λ�óߴ硣
 *        state - �б���״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 * remark: �˺�������������б���Ľӿڡ�
 */
int MtImageListCtrl::draw_item(MtBitmap &/*memory_bitmap*/,const int /*item*/,
	const int /*sub_item*/,const CRect &/*item_rect*/,const unsigned int /*state*/){
	return(0);
}

BEGIN_MESSAGE_MAP(MtImageListCtrl,CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
	//ON_WM_ERASEBKGND() //��������η��ֹ���������ʱListˢ�²���ʱ��
END_MESSAGE_MAP()

/**
 * name: OnEraseBkgnd
 * brief: ���ڲ�����Ϣ��Ӧ������������������������Ҫ���Ի档
 * param: --
 * return �˺���һֱ����TRUE��
 */
BOOL MtImageListCtrl::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CListCtrl::OnEraseBkgnd(pDC));
}

/**
 * name: draw_item_background
 * brief: �����б���ı�����
 * param: memory_bitmap - �ڴ�λͼ��
 *        item_rect - �б���ĳߴ硣
 *		  state - �ؼ���ǰ״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageListCtrl::draw_item_background(MtBitmap &memory_bitmap,
	const CRect &item_rect,const unsigned int state){
	//1.�жϵ�ǰ����ͼƬ�Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_item_background_image)){
		return(-1);
	}
	if(!_item_background_image->is_valid()){
		return(-2);
	}
	//2.�жϵ�ǰ����ͼƬ�������Ƿ�Ϸ���������Ϸ���ֱ�ӷ��ش���
	if(!static_cast<bool>(_item_background_image_region_division)){
		return(-3);
	}
	if(!_item_background_image_region_division->is_valid()){
		return(-4);
	}
	//3.��ȡ����ͼƬ�ߴ磬�����ȡʧ��ֱ�ӷ��ش���
	const CRect image_rect=_item_background_image_region_division->
		get_child_region_rect(state);
	if(image_rect.IsRectEmpty()){
		return(-5);
	}
	//4.����ǰ����ͼƬ���Ƶ��ڴ�λͼ�ϡ�
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
	//5.�ɹ����ء�
	return(0);
}

/**
 * name: draw_item_text
 * brief: �����б����ı���
 * param: memory_bitmap - �ڴ�λͼ��
 *        text - �ı���
 *        rect - �����ı���Χ��
 *        state - �ؼ���ǰ״̬��
 *        dc - �����ı��Ļ�ͼ�豸��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageListCtrl::draw_item_text(MtBitmap &memory_bitmap,
	const CString &text,const CRect &rect,const unsigned int state,HDC dc){
	//1.�����ǰ���ݲ������Ϸ�����ֱ�ӷ��ء�
	if((text.IsEmpty())||(rect.IsRectEmpty())||(0==dc)){
		return(-1);
	}
	//2.���¼��㵱ǰ�ı���������
	CRect text_rect(rect);
	text_rect.InflateRect(-1,-1,-1,-1);
	//3.���㵱ǰ�ı�ͣ����ʽ��
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
	//4.���㵱ǰ�ı�������ɫ��
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
	//5.��ȡ��ǰ�ı����Ƶ����塣
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		text_rect.left,text_rect.top,text_rect.Width(),text_rect.Height(),color_a,
		color_r,color_g,color_b,text_h_alignment,text_v_alignment)<0){
		return(-2);
	}
	//5.�ɹ����ء�
	return(0);
}