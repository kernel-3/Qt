// source-code/control/MtImageStatic.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageStatic.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"

IMPLEMENT_DYNAMIC(MtImageStatic,CStatic)

/**
 * name: MtImageStatic
 * brief: ���캯����
 * param: --
 * return: --
 */
MtImageStatic::MtImageStatic()
	:CStatic()
	,_text(_T(""))
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_background_image_index(0)
	,_text_alignment(0)
	,_text_color_a(255)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0){
}

/**
 * name: ~MtImageStatic
 * brief: ����������
 * param: --
 * return: --
 */
MtImageStatic::~MtImageStatic(){
}

/**
 * name: load_background_image
 * brief: ���ر���ͼƬ��
 * param: image_path - ͼƬ·����
 *        image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageStatic::load_background_image(
	const CString &image_path,const int image_rows/*=1*/,const int image_cols/*=1*/){
	//1.����ͼƬ·�������µı���ͼƬ��
	_background_image.reset(new MtImage(image_path));
	//2.�жϱ���ͼƬ�����Ƿ�ɹ���
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
	//3.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
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
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: load_background_image
 * brief: ���ر���ͼƬ��
 * param: image - ָ�򱳾�ͼƬ������ָ�롣
 *        image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageStatic::load_background_image(
	PtrToImage image,const int image_rows/*=1*/,const int image_cols/*=1*/){
	//1.����ͼƬ��ֻ��ָ�봴���ı���ͼƬ��
	_background_image=image;
	//2.�жϱ���ͼƬ�����Ƿ�ɹ���
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
	//3.����ͼƬ����������������ͼƬ�������������ж��Ƿ�ɹ���
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
	//4.�������е���ֱ�ӳɹ����ء�
	return(0);
}

/**
 * name: set_background_image_stretching_factors
 * brief: ���ñ���ͼƬ����ϵ����
 * param: stretch_left - ����ͼƬ�������ϵ����
 *        stretch_top - ����ͼƬ��������ϵ����
 *        stretch_right - ����ͼƬ�Ҳ�����ϵ����
 *        stretch_bottom - ����ͼƬ�ײ�����ϵ����
 * return: --
 */
void MtImageStatic::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: clear_background_image_stretching_factors
 * brief: �������ͼƬ������ϵ����
 * param: --
 * return: --
 */
void MtImageStatic::clear_background_image_stretching_factors(){
	_background_image_stretching_factors.left=0;
	_background_image_stretching_factors.top=0;
	_background_image_stretching_factors.right=0;
	_background_image_stretching_factors.bottom=0;
	_is_background_image_stretched=FALSE;
}

/**
 * name: set_background_image_index
 * brief: ���õ�ǰ��̬�ı�����ʾ�ı���ͼƬ������š�
 * param: index - ��ǰ��ʾ�ı���ͼƬ��š�
 *        is_invalidate - �Ƿ�ˢ�µ�ǰ���ڡ�
 * return: --
 */ 
void MtImageStatic::set_background_image_index(
	const int index,const BOOL is_invalidate/*=TRUE*/){
	_background_image_index=index;
	if(is_invalidate){
		Invalidate(TRUE);
	}
}

/**
 * name: set_text
 * brief: ���þ�̬�ı����ı���
 * param: text - ��̬�ı����ı���
 *        is_invalidate - �Ƿ�ˢ�¾�̬�ı���
 * return: --
 */
void MtImageStatic::set_text(
	const CString &text,const BOOL is_invalidate/*=FALSE*/){
	SetWindowText(text);
	_text=text;
	if(is_invalidate){
		invalidate_parent_window();
		Invalidate(FALSE);
	}
}

/**
 * name: get_text
 * brief: ��ȡ��̬�ı����ı���
 * param: --
 * return: ���ؾ�̬�ı����ı���
 */
CString MtImageStatic::get_text(){
	CString text(_T(""));
	GetWindowText(text);
	if(!text.IsEmpty()){
		_text=text;
		SetWindowText(_T(""));
	}
	return(_text);
}

/**
 * name: set_text_alignment
 * brief: �����ı�ͣ����ʽ��
 * param: alignment - �ı�ͣ����ʽ��
 * return: --
 */
void MtImageStatic::set_text_alignment(const unsigned int alignment){
	_text_alignment=alignment;
}

/**
 * name: get_text_alignment
 * brief: ��ȡ�ı�ͣ����ʽ��
 * param: --
 * return: ���ص�ǰ�ı�ͣ����ʽ��
 */
unsigned int MtImageStatic::get_text_alignment() const{
	return(_text_alignment);
}

/**
 * name: set_text_color
 * brief: ���þ�̬�ı�����ı���ɫ��
 * param: color_a - �ı���ɫ��a������
 *        color_r - �ı���ɫ��r������
 *        color_g - �ı���ɫ��g������
 *        color_b - �ı���ɫ��b������
 *        is_invalidate - �Ƿ�ˢ�¾�̬�ı���
 * return: --
 */
void MtImageStatic::set_text_color(const unsigned char color_a,
	const unsigned char color_r,const unsigned char color_g,
	const unsigned char color_b,const BOOL is_invalidate/*=FALSE*/){
	_text_color_a=color_a;
	_text_color_r=color_r;
	_text_color_g=color_g;
	_text_color_b=color_b;
	if(is_invalidate){
		invalidate_parent_window();
		//Invalidate(FALSE);
	}
}

BEGIN_MESSAGE_MAP(MtImageStatic,CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/**
 * name: OnPaint
 * brief: �ؼ�������Ϣ��Ӧ�������ڴ�����ʵ��
 *        �ؼ��Ļ��ơ�
 * param: --
 * return: --
 */
void MtImageStatic::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.��ȡ��ǰ���ڳߴ���Ϣ��
	CRect window_rect(0,0,0,0);
	GetClientRect(window_rect);
	//2.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
	PtrToBitmap memory_bitmap(new MtBitmap(
		window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||
		(!memory_bitmap->is_valid())){
		return;
	}
	//3.���ƿؼ�������
	draw_background(*memory_bitmap);
	//4.���ƿؼ��ı���
	draw_text(*memory_bitmap,dc.GetSafeHdc());
	//5.����ǰ�ڴ�λͼ�����DC�豸�ϡ�
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	// Do not call CStatic::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: ���ڲ�����Ϣ��Ӧ����������������ֹ���������������ػ渺����
 * param: --
 * return: �������Ƿ���TRUE��
 */
BOOL MtImageStatic::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return CStatic::OnEraseBkgnd(pDC);
}

/**
 * name: OnSize
 * brief: ���ڳߴ������Ϣ��Ӧ������
 * param: nType - �ߴ�������͡�
 *        cx - ��ȡ�
 *        cy - �߶ȡ�
 */
void MtImageStatic::OnSize(UINT nType,int cx,int cy){
	CStatic::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	//1.�����ǰ�ߴ緢���仯�����¸�������Ӧ����
	invalidate_parent_window();
	//2.�ػ浱ǰ���ڡ�
	OnPaint();
}

/**
 * name: invalidate_parent_window
 * brief: ˢ�¸����ڡ�
 * param: --
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageStatic::invalidate_parent_window(){
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
 * brief: ���ƿؼ�������
 * param: memory_bitmap - �ڴ�λͼ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageStatic::draw_background(MtBitmap &memory_bitmap){
	//1.�����ǰ����ͼƬ���Ϸ�����ֱ�ӷ��ش���
	if((!static_cast<bool>(_background_image))||
		(!_background_image->is_valid())){
		return(-1);
	}
	//2.�����ǰ����ͼƬ�ü������Ϸ���
	if((!static_cast<bool>(_background_image_region_division))||
		(!_background_image_region_division->is_valid())){
		return(-2);
	}
	//2.���㵱ǰ����ͼƬ��������
	const CRect image_rect=_background_image_region_division->
		get_child_region_rect(_background_image_index);
	if(image_rect.IsRectEmpty()){
		return(-3);
	}
	//2.���ڴ�λͼ�������ͼƬ��
	//2-1.�����ǰ����ͼƬ����ϵ�����á�
	if(_is_background_image_stretched){
		if(_background_image->paste_to_bitmap_ex(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height(),
			_background_image_stretching_factors.left,
			_background_image_stretching_factors.top,
			_background_image_stretching_factors.right,
			_background_image_stretching_factors.bottom)<0){
			return(-4);
		}
	}
	//2-2.�����ǰ����ͼƬ����ϵ��û�����á�
	else{
		if(_background_image->paste_to_bitmap(&memory_bitmap,
			0,0,memory_bitmap.get_width(),memory_bitmap.get_height(),
			image_rect.left,image_rect.top,image_rect.Width(),image_rect.Height())<0){
			return(-5);
		}
	}
	//3.�������е��ˣ��ɹ����ء�
	return(0);
}

/**
 * name: draw_text
 * brief: ���ƾ�̬�ı����ı���
 * param: memory_bitmap - �ڴ�λͼ�� 
 *		  dc - ׼�������ı���DC�豸��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageStatic::draw_text(MtBitmap &memory_bitmap,const HDC dc){
	//1.��ȡ��ǰ��̬�ı����ı���
	CString text=get_text();
	if(text.IsEmpty()){
		return(0);
	}
	//2.���㵱ǰ�ı�ͣ����ʽ��
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
	//3.��ȡ��ǰ�ı����Ƶ����塣
	if(memory_bitmap.draw_text(text,dc,static_cast<HFONT>(GetFont()->GetSafeHandle()),
		WINDOW_MARGIN,WINDOW_MARGIN,memory_bitmap.get_width()-WINDOW_MARGIN,
		memory_bitmap.get_height()-WINDOW_MARGIN,
		_text_color_a,_text_color_r,_text_color_g,_text_color_b,
		text_h_alignment,text_v_alignment)<0){
		return(-1);
	}
	//4.�ɹ����ء�
	return(0);
}