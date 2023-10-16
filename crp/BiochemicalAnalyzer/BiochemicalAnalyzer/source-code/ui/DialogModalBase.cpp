//source-code/ui/DialogModalBase.cpp : implementation file
//

#include"stdafx.h"
#include"DialogModalBase.h"
#include"afxdialogex.h"
#include"../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../global/Theme.h"

//DialogModalBase dialog

IMPLEMENT_DYNAMIC(DialogModalBase,DialogBase)

/**
 * name: DialogModalBase
 * breif: ���캯����
 * param: IDD - ��ǰ�Ի���ID��
 *        pParent - ָ�򸸶Ի���
 * return: --
 */
DialogModalBase::DialogModalBase(const unsigned int IDD,CWnd *pParent/*=NULL*/)
	:DialogBase(IDD,pParent){
}

/**
 * name: ~DialogModalBase
 * breif: ����������
 * param: --
 * return: --
 */
DialogModalBase::~DialogModalBase(){
}

/**
 * name: DoDataExchange
 * breif: ֧��DDX/DDV��
 * param: pDX -
 * return: --
 */
void DialogModalBase::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
}

/**
 * name: draw
 * brief: �Ի���������⺯����
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 *        dc - �Ի����ͼDC��
 * return: --
 */
void DialogModalBase::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.���û�����Ӧ�������ƶԻ��򱳾���
	DialogBase::draw(memory_bitmap,dc);
	//2.���ƶԻ�����⡢�߿�
	draw_title_and_border(memory_bitmap);
	//3.���ƶԻ�������ı���
	draw_title_text(memory_bitmap,dc);
}

BEGIN_MESSAGE_MAP(DialogModalBase,DialogBase)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

//DialogModalBase message handlers

/**
 * name: OnNcHitTest
 * brief: �Ի���߿�����Ϣ��Ӧ�������ٴ�����ʵ��
 *        �Ի���������������ק���ܡ�
 * param: point - ���λ����Ϣ��
 * return: ...
 */
LRESULT DialogModalBase::OnNcHitTest(CPoint point){
	// TODO: Add your message handler code here and/or call default
	/////////////////////////////////////////////////////////////////
	//1.���㵱ǰ�Ի����������Χ��
	CRect title_range;
	GetClientRect(title_range);
	title_range.bottom=TITLE_SIZE;
	ClientToScreen(title_range);
	//2.�����ǰ���������������Χ�ڡ�
	if(title_range.PtInRect(point)){
		return(HTCAPTION);
	}
	////////////////////////////////////////////////////////////////
	return(DialogBase::OnNcHitTest(point));
}

/**
 * name: draw_title_and_border
 * breif: ���ƶԻ���ı����Լ��߿�
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogModalBase::draw_title_and_border(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի���ı��⡢�߿�ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(37);
	//2.�����ǰ�Ի�����⡢�߿�ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap_ex(&memory_bitmap,0,0,memory_bitmap.get_width(),
		memory_bitmap.get_height(),0,0,image->get_width(),image->get_height(),
		BORDER_SIZE,TITLE_SIZE,BORDER_SIZE,BORDER_SIZE);
}

/**
 * name: draw_title_text
 * brief: ���Ƶ�ǰ�Ի���ı����ı���
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 *        dc - �Ի����ͼDC��
 * return: --
 */
void DialogModalBase::draw_title_text(MtBitmap &memory_bitmap,CDC &dc){
	//1.��ȡ��ǰ�Ի�����⡣
	CString title(_T(""));
	GetWindowText(title);
	//2.�����ǰ�Ի������Ϊ�ա�
	if(_T("")==title){
		return;
	}
	//3.���Ƶ�ǰ�Ի�����⡣
	memory_bitmap.draw_text(title,dc.GetSafeHdc(),
		static_cast<HFONT>(GetFont()->GetSafeHandle()),BORDER_SIZE,
		0,(memory_bitmap.get_width()-(2*BORDER_SIZE)),TITLE_SIZE,
		255,255,255,255,MtBitmap::ALIGNMENT_NEAR,MtBitmap::ALIGNMENT_CENTER);
}