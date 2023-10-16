// source-code/ui/control/MarkButton.cpp : implementation file
//
#include"stdafx.h"
#include"MarkButton.h"
#include"../../../../../include/mfctoolkit/graphic/MtBitmap.h"

IMPLEMENT_DYNAMIC(MarkButton,MtImageButton)

/**
 * name: MarkButton
 * brief: ���캯����
 * param: --
 * return: --
 */
MarkButton::MarkButton()
	:MtImageButton(TYPE_BUTTON)
	,_mark_text(_T(""))
	,_mark_text_font()
	,_mark_text_alignment(0)
	,_mark_text_color_a(255)
	,_mark_text_color_r(0)
	,_mark_text_color_g(0)
	,_mark_text_color_b(0){
}

/**
 * name: ~MarkButton
 * brief: 
 * param:
 * return:
 */
MarkButton::~MarkButton(){
	if(0!=_mark_text_font.GetSafeHandle()){
		_mark_text_font.DeleteObject();
	}
}

/**
 * name: set_mark_text
 * brief: ���õ�ǰ��ť����ı���
 * param: mark_text - ����ı���
 * return: --
 */
void MarkButton::set_mark_text(const CString &mark_text){
	_mark_text=mark_text;
}

/**
 * name: set_mark_text_alignment
 * brief: ���ñ���ı�ͣ����ʽ��
 * param: mark_text_alignment - ����ı�ͣ����ʽ��
 * return: --
 */
void MarkButton::set_mark_text_alignment(const unsigned int mark_text_alignment){
	_mark_text_alignment=mark_text_alignment;
}

/**
 * name: set_mark_text_color
 * brief: ���õ�ǰ����ı���ɫ��
 * param: color_a - �ı���ɫa������
 *        color_r - �ı���ɫr������
 *        color_g - �ı���ɫg������
 *        color_b - �ı���ɫb������
 * return: --
 */
void MarkButton::set_mark_text_color(const unsigned char color_a,const unsigned char color_r,
	const unsigned char color_g,const unsigned char color_b){
	_mark_text_color_a=color_a;
	_mark_text_color_r=color_r;
	_mark_text_color_g=color_g;
	_mark_text_color_b=color_b;
}

/**
 * name: PreSubclassWindow
 * brief: ���໯��ťǰ���ô����⺯�����ڴ���������
 *        ��ť����ı��������塣
 * param: --
 * return: --
 */
void MarkButton::PreSubclassWindow(){
	// TODO: Add your specialized code here and/or call the base class
	//////////////////////////////////////////////////////////////////
	//1.��ȡ��ǰ��ť�������ݡ�
	LOGFONT log_font;
	GetFont()->GetLogFont(&log_font);
	//2.��С��ǰ��ť���塣
	if(abs(log_font.lfHeight)>3){
		if(log_font.lfHeight<0){
			log_font.lfHeight+=3;
		}else{
			log_font.lfHeight-=3;
		}
	}
	log_font.lfWeight=FW_DONTCARE;
	//3.������ǰ��ť����ı����塣
	_mark_text_font.CreateFontIndirect(&log_font);
	//////////////////////////////////////////////////////////////////
	MtImageButton::PreSubclassWindow();
}

/**
 * name: draw_item
 * breif: ��ť�������⺯��������ʵ�ְ�ť���ơ�
 * param: memory_bitmap - ��ǰ��ť�ڴ�λͼ��
 *        dc - ��ǰ��ť����DC��
 *        state - ��ǰ��ť״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MarkButton::draw_item(MtBitmap &memory_bitmap,HDC dc,const unsigned int state){
	//1.���û�����Ӧ���⺯����
	MtImageButton::draw_item(memory_bitmap,dc,state);
	//2.���Ƶ�ǰ��ť����ı���
	draw_mark_text(memory_bitmap,dc,state);
	//3.�������е��˳ɹ����ء�
	return(0);
}

BEGIN_MESSAGE_MAP(MarkButton,MtImageButton)
END_MESSAGE_MAP()

//MarkButton message handlers

/**
 * name: draw_mark_text
 * brief: ���Ƶ�ǰ��ť����ı���
 * param: memory_bitmap - ��ǰ��ť�ڴ�λͼ��
 *        dc - ��ǰ��ť����DC��
 *        state - ��ǰ��ť״̬��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MarkButton::draw_mark_text(MtBitmap &memory_bitmap,HDC dc,const unsigned int state){
	//1.�����ǰ��ť����ı������ڣ���ֱ�ӷ��ء�
	if(_T("")==_mark_text){
		return(0);
	}
	//2.���㵱ǰ����ı����Ʒ�Χ��
	CRect text_range(0,0,memory_bitmap.get_width(),
		memory_bitmap.get_height());
	text_range.InflateRect(-MARK_TEXT_MARGIN,-MARK_TEXT_MARGIN,
		-MARK_TEXT_MARGIN,-MARK_TEXT_MARGIN);
	if(2==state){
		text_range.InflateRect(-1,-1,1,1);
	}
	//3.���㵱ǰ����ı���ͣ����ʽ��
	MtBitmap::Alignment horizontal_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_mark_text_alignment&ALIGNMENT_HCENTER){
		horizontal_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_mark_text_alignment&ALIGNMENT_RIGHT){
		horizontal_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	MtBitmap::Alignment vertical_alignment=MtBitmap::ALIGNMENT_NEAR;
	if(_mark_text_alignment&ALIGNMENT_VCENTER){
		vertical_alignment=MtBitmap::ALIGNMENT_CENTER;
	}else if(_mark_text_alignment&ALIGNMENT_BOTTOM){
		vertical_alignment=MtBitmap::ALIGNMENT_FAR;
	}
	//4.���ݵ�ǰ��ť״̬�����ı���
	//4-1.�����ǰ��ť����ʧЧ״̬��
	if(3==state){
		if(memory_bitmap.draw_text(_mark_text,dc,static_cast<HFONT>(
			_mark_text_font.GetSafeHandle()),text_range.left,text_range.top,
			text_range.Width(),text_range.Height(),DISABLE_TEXT_COLOR_A,
			DISABLE_TEXT_COLOR_R,DISABLE_TEXT_COLOR_G,DISABLE_TEXT_COLOR_B,
			horizontal_alignment,vertical_alignment)<0){
			return(-1);
		}
	}
	//4-2.�����ǰ��ť��������״̬��
	else{
		if(memory_bitmap.draw_text(_mark_text,dc,static_cast<HFONT>(
			_mark_text_font.GetSafeHandle()),text_range.left,text_range.top,
			text_range.Width(),text_range.Height(),_mark_text_color_a,
			_mark_text_color_r,_mark_text_color_g,_mark_text_color_b,
			horizontal_alignment,vertical_alignment)<0){
			return(-2);
		}
	}
	//5.�������е��˳ɹ����ء�
	return(0);
}