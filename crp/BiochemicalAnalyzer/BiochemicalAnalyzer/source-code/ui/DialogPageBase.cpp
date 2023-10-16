//source-code/ui/DialogPageBase.cpp : implementation file
//

#include"stdafx.h"
#include"DialogPageBase.h"
#include"afxdialogex.h"
#include"../global/Theme.h"
#include"../../../../include/mfctoolkit/graphic/MtBitmap.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"

//DialogPageBase dialog
IMPLEMENT_DYNAMIC(DialogPageBase,DialogBase)

/**
 * name: DialogPageBase
 * breif: ���캯����
 * param: IDD - �Ի���ID��
 *        pParent - ָ�򸸶Ի���
 * return: --
 */
DialogPageBase::DialogPageBase(
	const unsigned int IDD,CWnd *pParent/*=NULL*/)
	:DialogBase(IDD,pParent){
}

/**
 * name: ~DialogPageBase
 * breif: ����������
 * param: --
 * return: --
 */
DialogPageBase::~DialogPageBase(){
}

/**
 * name: DoDataExchange
 * breif: ֧��DDX/DDV
 * param: pDX -
 * return: --
 */
void DialogPageBase::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
}

/**
 * name: draw
 * brief: �Ի���������⺯����
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 *        dc - �Ի����ͼDC��
 * return: --
 */
void DialogPageBase::draw(MtBitmap &memory_bitmap,CDC &dc){
	//1.���û�����Ӧ�������ƶԻ��򱳾���
	DialogBase::draw(memory_bitmap,dc);
	//2.���ƶԻ���߿�
	draw_boder(memory_bitmap);
}

BEGIN_MESSAGE_MAP(DialogPageBase,DialogBase)
END_MESSAGE_MAP()

//DialogPageBase message handlers

/**
 * name: draw_boder
 * brief: ���ƶԻ���߿�
 * param: memory_bitmap - �Ի����ڴ�λͼ��
 * return: --
 */
void DialogPageBase::draw_boder(MtBitmap &memory_bitmap){
	//1.��ȡ��ǰ�Ի���ı߿�ͼƬ��
	Theme::PtrToImage image=Theme::instance()->get_image(24);
	//2.�����ǰ�Ի���߿�ͼƬ��ȡʧ�ܣ���ֱ�ӷ��ء�
	if(!static_cast<bool>(image)){
		return;
	}
	//3.���㵱ǰ�Ի���߿�λ����Ϣ��
	const CRect rect(0,0,memory_bitmap.get_width(),BODER_SIZE);
	//4.����ǰͼƬ�����ָ�����ڴ�λͼ�ϡ�
	image->paste_to_bitmap(&memory_bitmap,rect.left,rect.top,
		rect.Width(),rect.Height(),0,0,image->get_width(),
		image->get_height());
}