// source-code/control/MtImageEdit.cpp : implementation file
//

#include"stdafx.h"
#include"MtImageEdit.h"
#include"../graphic/MtBitmap.h"
#include"../graphic/MtImage.h"
#include"../graphic/MtRegionDivision.h"

// MtImageEdit
IMPLEMENT_DYNAMIC(MtImageEdit,CEdit)

//��ʼ����̬����
const COLORREF MtImageEdit::DISABLE_TEXT_COLOR=RGB(100,100,100);

/*
 * name: MtImageEdit
 * brief: ���캯����
 * param: --
 * return: --
 */
MtImageEdit::MtImageEdit()
	:CEdit()
	,_background_image()
	,_background_image_region_division()
	,_is_background_image_stretched(FALSE)
	,_background_image_stretching_factors()
	,_is_there_in_focus(FALSE)
	,_text_color_r(0)
	,_text_color_g(0)
	,_text_color_b(0){
}

/*
 * name: MtImageEdit
 * brief: ����������
 * param: --
 * return: --
 */
MtImageEdit::~MtImageEdit(){
}

/**
 * name: load_background_image
 * brief: ���ذ�ť����ͼƬ��
 * param: image_path - ͼƬ·����
 *		  image_rows - ͼƬ������
 *        image_cols - ͼƬ������
 * return: �������ͼƬ���سɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageEdit::load_background_image(const CString &image_path,
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
int MtImageEdit::load_background_image(PtrToImage image,
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
void MtImageEdit::set_background_image_stretching_factors(const int stretch_left,
	const int stretch_top,const int stretch_right,const int stretch_bottom){
	_background_image_stretching_factors.left=stretch_left;
	_background_image_stretching_factors.top=stretch_top;
	_background_image_stretching_factors.right=stretch_right;
	_background_image_stretching_factors.bottom=stretch_bottom;
	_is_background_image_stretched=TRUE;
}

/**
 * name: set_text_color
 * brief: �����ı���ɫ��
 * param: text_color_r - ��ɫr������
 *        text_color_g - ��ɫg������
 *        text_color_b - ��ɫb������
 *        is_invalidated - �Ƿ���´��ڡ�
 * return: --
 */
void MtImageEdit::set_text_color(const unsigned char text_color_r,
	const unsigned char text_color_g,const unsigned char text_color_b,
	const BOOL is_invalidated/*=FALSE*/){
	_text_color_r=text_color_r;
	_text_color_g=text_color_g;
	_text_color_b=text_color_b;
	if(is_invalidated){
		Invalidate(TRUE);
	}
}

/**
 * name: PreTranslateMessage
 * breif: ��Ϣת��ǰ���ô����⺯�����ڴ˸������ؼ�
 *        ����Ϣ�����¿ؼ���
 * param: pMsg - ָ����Ϣ�ṹ��ָ�롣
 * return: --
 */
BOOL MtImageEdit::PreTranslateMessage(MSG *pMsg){
	//TODO: Add your specialized code here and/or call the base class
	//1.�����ǰ��ϢΪ������Ϣ�������أ������¿ؼ���
	if(WM_KEYDOWN==pMsg->message){
		Invalidate(TRUE);
	}
	//2.���û�����Ӧ��������
	return(CEdit::PreTranslateMessage(pMsg));
}

BEGIN_MESSAGE_MAP(MtImageEdit,CEdit)
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_CHANGE,&MtImageEdit::OnEnChange)
END_MESSAGE_MAP()

//MtImageEdit message handlers

/**
 * name: OnEraseBkgnd
 * brief: ���ڱ���������Ϣ��Ӧ�������ڴ���������
 *        �ؼ��ı���ͼ����
 * param: pDC - ��ǰʹ�õĻ�ͼDC�豸��
 * return: �������ִ�гɹ�����ֵΪTRUE�����򷵻�ֵΪFALSE��
 */
BOOL MtImageEdit::OnEraseBkgnd(CDC *pDC){
	// TODO: Add your message handler code here and/or call default
	//1.��ȡ��ǰ���ڳߴ硣
	CRect window_rect(0,0,0,0);
	GetWindowRect(window_rect);
	ScreenToClient(window_rect);
	//2.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
	PtrToBitmap memory_bitmap(new MtBitmap(
		window_rect.Width(),window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||
		(!memory_bitmap->is_valid())){
		return(TRUE);
	}
	//3.���Ʊ༭�򱳾�ͼƬ��
	int state=0;
	if(!IsWindowEnabled()){
		state=2;
	}else if(_is_there_in_focus){
		state=1;
	}
	draw_background(*memory_bitmap,state);
	//4.���ڴ�λͼ���������DC�豸�ϡ�{
	CDC *dc=GetWindowDC();
	memory_bitmap->paste_to_dc(dc->GetSafeHdc(),0,0);
	ReleaseDC(dc);
	//5.����ִ�е���ֱ�ӳɹ����ء�
	//return(TRUE)	//unsolved: ֱ�ӷ���TRUEʱ�����ֿؼ�����ʱ�Ὣ���ָǵ���ԭ���в����ʣ�
	                //          �о�����pDC��dc����˳������⡣
	return(CEdit::OnEraseBkgnd(pDC));
}

/**
 * name: OnSetFocus
 * brief: �༭���ȡ������Ϣ��Ӧ����������������¼�����Ƿ��ȡ��
 * param: pOldWnd - ָ����һ�ν������ڴ��ڡ�
 * return: --
 */
void MtImageEdit::OnSetFocus(CWnd* pOldWnd){
	CEdit::OnSetFocus(pOldWnd);
	//TODO: Add your message handler code here
	_is_there_in_focus=TRUE;
	Invalidate(TRUE);
}

/**
 * name: OnKillFocus
 * brief: �༭��ʧȥ������Ϣ��Ӧ����������������¼�����Ƿ��ȡ��
 * param: pNewWnd - ָ��ǰ�������ڴ��ڡ�
 * return: --
 */
void MtImageEdit::OnKillFocus(CWnd *pNewWnd){
	CEdit::OnKillFocus(pNewWnd);
	//TODO: Add your message handler code here
	_is_there_in_focus=FALSE;
	Invalidate(TRUE);
}

/**
 * name: CtlColor
 * brief: ��ɫ���Ʒ�ӳ��Ϣ��Ӧ�����������������༭������Ϊ͸����
 * param: pDC - ��ͼ�豸DC��
 *        nCtlColor - ��ǰ���ƵĿؼ���š�
 * return: ���ػ��ƿؼ��ı�����ˢ��
 */
HBRUSH MtImageEdit::CtlColor(CDC *pDC,UINT /*nCtlColor*/){
	// TODO:  Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	if(IsWindowEnabled()){
		pDC->SetTextColor(RGB(_text_color_r,
			_text_color_g,_text_color_b));
	}else{
		pDC->SetTextColor(DISABLE_TEXT_COLOR);
	}
	return((HBRUSH)GetStockObject(NULL_BRUSH));
	//TODO:  Return a non-NULL brush if the parent's handler should not be called
	//return(NULL);
}

/**
 * name: OnEnChange
 * brief: ���༭�����ݸı�ʱ�����ô���Ϣ��Ӧ������
 *        ��ʱ����ˢ�µ�ǰ�༭�򴰿ڡ�
 * param: --
 * return: --
 */
void MtImageEdit::OnEnChange(){
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
	Invalidate(TRUE);
}

/**
 * name: draw_background
 * brief: ���ư�ť�ı�����
 * param: memory_bitmap - �ڴ�λͼ��
 *		  state - ��ť��ǰ״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImageEdit::draw_background(MtBitmap &memory_bitmap,const unsigned int state){
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