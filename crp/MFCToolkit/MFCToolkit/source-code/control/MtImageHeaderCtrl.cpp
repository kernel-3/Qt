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
 * brief: ���캯����
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
 * brief: ����������
 * param: --
 * return: --
 */
MtImageHeaderCtrl::~MtImageHeaderCtrl(){
}

/**
 * name: set_height
 * brief: ���ø߶ȡ�
 * param: height - �߶ȡ�
 * return: --
 */
void MtImageHeaderCtrl::set_height(const unsigned int height){
	_height=height;
}

/**
 * name: get_height
 * breif: ��ȡ�߶ȡ�
 * param: --
 * return: ���ظ߶ȡ�
 */
unsigned int MtImageHeaderCtrl::get_height() const{
	return(_height);
}

/**
 * name: load_item_background_image
 * brief: �����б�����б���ı���ͼƬ��
 * param: image_path - ͼƬ·����
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageHeaderCtrl::load_item_background_image(const CString &image_path,
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
int MtImageHeaderCtrl::load_item_background_image(PtrToImage image,
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
 * brief: ���ñ�������ı���ɫ��
 * param: color_a - ��ɫA�ɷ֡�
 *        color_b - ��ɫB�ɷ֡�
 *        color_c - ��ɫC�ɷ֡�
 *        color_d - ��ɫD�ɷ֡�
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
 * brief: ���ñ�������ı�ͣ����ʽ��
 * param: alignment - �ı�ͣ����ʽ��
 * return: --
 */
void MtImageHeaderCtrl::set_item_text_alignment(const unsigned int alignment){
	_item_text_alignment=alignment;
}

/**
 * name: get_item_text_alignment
 * brief: ��ȡ�б�����ı�ͣ����ʽ��
 * param: --
 * return: �����б�����ı�ͣ����ʽ��
 */
unsigned int MtImageHeaderCtrl::get_item_text_alignment() const{
	return(_item_text_alignment);
}

BEGIN_MESSAGE_MAP(MtImageHeaderCtrl,CHeaderCtrl)
	ON_WM_PAINT()
	//ON_WM_ERASEBKGND() //��������η��ֹ���������ʱ������ˢ�²���ʱ��
	ON_MESSAGE(HDM_LAYOUT,&MtImageHeaderCtrl::OnLayout)
END_MESSAGE_MAP()

// MtImageHeaderCtrl message handlers

/**
 * name: OnPaint
 * breif: ���ڻ�����Ϣ��Ӧ������
 * param: --
 * return: --
 */
void MtImageHeaderCtrl::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.���塣
	typedef std::shared_ptr<MtBitmap> PtrToBitmap;
	//2.��ȡ��ǰ�����������
	const int items=GetItemCount();
	if(items<=0){
		return;
	}
	//3.��ȡ��ǰ���ڳߴ硣
	CRect window_rect;
	GetClientRect(window_rect);
	if(window_rect.IsRectEmpty()){
		return;
	}
	//4.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
	PtrToBitmap memory_bitmap(new MtBitmap(window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//5.ѭ�����Ʊ���ÿһ�
	for(int item=0;item!=items;++item){
		//5-1.���㵱ǰ�ؼ�״̬��
		unsigned int state=1;
		if(0==item){
			state=0;
		}
		//5-2.��ȡ��ǰ������ߴ硣
		CRect item_rect;
		if(!GetItemRect(item,item_rect)){
			continue;
		}
		if(item_rect.IsRectEmpty()){
			continue;
		}
		//5-3.���Ƶ�ǰ���������
		draw_item_background(*memory_bitmap,item_rect,state);
		//5-3.��ȡ��ǰ�������ı���
		TCHAR text[_MAX_PATH];
		memset(text,0,_MAX_PATH*sizeof(TCHAR));
		HD_ITEM hd_item;
		hd_item.mask=HDI_TEXT|HDI_FORMAT|HDI_ORDER;
		hd_item.pszText=text;
		hd_item.cchTextMax=_MAX_PATH;
		GetItem(item,&hd_item);
		//5-4.���Ƶ�ǰ�������ı���
		draw_item_text(*memory_bitmap,text,item_rect,dc.GetSafeHdc());
	}
	//6.�ڴ�λͼ��ͼ��
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),window_rect.left,window_rect.top);
	// Do not call CHeaderCtrl::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: ���ڲ�����Ϣ��Ӧ������������������������Ҫ���Ի档
 * param: --
 * return �˺���һֱ����TRUE��
 */
BOOL MtImageHeaderCtrl::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return(CHeaderCtrl::OnEraseBkgnd(pDC));
}

/**
 * name: OnLayout
 * brief: HDM_LAYOUT��Ϣ��Ӧ��������ϵͳ��������CHeaderCtrl�ĳߴ�ʱ��
 *        ���ʹ���Ϣ��
 * param: wParam - ������0��
 *        lParam - ָ��HDLAYOUT�ṹ���ָ�롣
 * return: �������ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
LRESULT MtImageHeaderCtrl::OnLayout(WPARAM wParam,LPARAM lParam){
	//1.����Ĭ�ϵĴ��ڴ�������
	const LRESULT result=MtImageHeaderCtrl::DefWindowProc(HDM_LAYOUT,wParam,lParam);
	//2.��ȡ�ߴ���ؽṹ��ָ�롣
	HD_LAYOUT *hd_layout=(HD_LAYOUT*)lParam;
	RECT *prc=hd_layout->prc;
	WINDOWPOS *pwpos=hd_layout->pwpos;
	//3.���ñ�ͷ�߶�
	pwpos->cy=_height;  
	prc->top=_height;
	//4.���ش��ڲ��������
	return(result);
}

/**
 * name: draw_item_background
 * brief: �����б���ı�����
 * param: memory_bitmap - �ڴ�λͼ��
 *        item_rect - �б���ĳߴ硣
 *		  state - �ؼ���ǰ״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageHeaderCtrl::draw_item_background(MtBitmap &memory_bitmap,
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
 *        dc - �����ı��Ļ�ͼ�豸��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageHeaderCtrl::draw_item_text(MtBitmap &memory_bitmap,
	const CString &text,const CRect &rect,HDC dc){
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
	//4.��ȡ��ǰ�ı����Ƶ����塣
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		text_rect.left,text_rect.top,text_rect.Width(),text_rect.Height(),_item_text_color_a,
		_item_text_color_r,_item_text_color_g,_item_text_color_b,text_h_alignment,text_v_alignment)<0){
		return(-2);
	}
	//5.�ɹ����ء�
	return(0);
}