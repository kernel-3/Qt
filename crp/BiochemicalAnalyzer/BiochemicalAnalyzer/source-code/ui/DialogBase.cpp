// source-code/ui/DialogBase.cpp : implementation file
//

#include"stdafx.h"
#include"DialogBase.h"
#include"afxdialogex.h"
#include"../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"
#include"../global/Theme.h"

// DialogBase dialog
IMPLEMENT_DYNAMIC(DialogBase,CDialogEx)

/**
 * name: DialogBase
 * brief: ���캯����
 * param: IDD - �Ի���ID��
 *		  pParent - ָ�򸸴��ڡ�
 * return: --
 */
DialogBase::DialogBase(
	const unsigned int IDD,CWnd *pParent/*=NULL*/)
	:CDialogEx(IDD,pParent)
	,_window_rect(){
}

/**
 * name: ~DialogBase
 * brief: ����������
 * param: --
 * return: --
 */
DialogBase::~DialogBase(){
}

/**
 * name: DoDataExchange
 * brief: DDX/DDV ֧�֡�
 * param: pDX -
 * return: --
 */
void DialogBase::DoDataExchange(CDataExchange *pDX){
	CDialogEx::DoDataExchange(pDX);
}

/**
 * name: PreTranslateMessage
 * breif: ��Ϣת��ǰ���ô����⺯����
 *        �ڴ˸��������û���ESC��Enter������
 * param: pMsg - ָ����Ϣ�ṹ��ָ�롣
 * return: --
 */
BOOL DialogBase::PreTranslateMessage(MSG *pMsg){
	// TODO: Add your specialized code here and/or call the base class
	///////////////////////////////////////////////////////////////////
	if(WM_KEYDOWN==pMsg->message){
		const int key=(int)pMsg->wParam;
		if(key==VK_RETURN){
			return(TRUE);
		}
		if(key==VK_ESCAPE){
			return(TRUE);
		}
	}
	///////////////////////////////////////////////////////////////////
	return(CDialogEx::PreTranslateMessage(pMsg));
}

/**
 * name: draw
 * brief: �Ի���������⺯����
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 *        dc - ��ʱ���Ƶ��ڴ�DC��
 * return: --
 */
void DialogBase::draw(MtBitmap &memory_bitmap,CDC &/*dc*/){
	//1.���Ƶ�ǰ�Ի��򱳾���
	draw_background(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogBase,CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//DialogBase message handlers

/**
 * name: OnSize
 * brief: �Ի���ߴ�仯ʱ�����ô���Ϣ��Ӧ������
 * param: nType - �ߴ�仯���͡�
 *        cx - ��ȡ�
 *        cy - �߶ȡ�
 * return: --
 */
void DialogBase::OnSize(UINT nType,int cx,int cy){
	//1.���û�����Ӧ��Ϣ��Ӧ������
	CDialogEx::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	_window_rect.SetRect(0,0,cx,cy);
}

/**
 * name: OnPaint
 * brief: �Ի�����Ҫ����ʱ��ϵͳ���ô���Ϣ��Ӧ�������˺�������
 *        ���ƶԻ���
 * param: --
 * return: --
 */
void DialogBase::OnPaint(){
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//1.�����ڴ�λͼ�������жϴ����Ƿ�ɹ���
	PtrToBitmap memory_bitmap(new MtBitmap(_window_rect.Width(),_window_rect.Height()));
	if((!static_cast<bool>(memory_bitmap))||(!memory_bitmap->is_valid())){
		return;
	}
	//2.����ڴ�λͼ���ݡ�
	memory_bitmap->fill(0,0,0,0);
	//3.���öԻ���������⺯����
	draw(*memory_bitmap,dc);
	//4.���ڴ�λͼ������Ի����С�
	memory_bitmap->paste_to_dc(dc.GetSafeHdc(),0,0);
	// Do not call CDialogEx::OnPaint() for painting messages
}

/**
 * name: OnEraseBkgnd
 * brief: �Ի��򱳾�������Ϣ��Ӧ������
 * param: pDC - ָ��ǰ��ͼDC��
 * return: �˺���ֱ�ӷ���TRUE��ʹ�û��ƶԻ���ʱ���ٽ��в���Ҫ�Ĳ���������
 */
BOOL DialogBase::OnEraseBkgnd(CDC * /*pDC*/){
	// TODO: Add your message handler code here and/or call default
	return(TRUE);
	//return CDialogEx::OnEraseBkgnd(pDC);
}

/**
 * name: draw_background
 * breif: ���ƶԻ��򱳾���
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogBase::draw_background(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի���ı���ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(1);
	//2.�����ǰ�Ի��򱳾�ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap(&memory_bitmap,0,0,memory_bitmap.get_width(),
		memory_bitmap.get_height(),0,0,image->get_width(),image->get_height());
}