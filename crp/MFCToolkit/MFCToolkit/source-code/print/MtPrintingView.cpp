// source-code/print/MtPrintingView.cpp : implementation file
//

#include"stdafx.h"
#include"MtPrintingView.h"

//MtPrintingView
IMPLEMENT_DYNCREATE(MtPrintingView,CScrollView)

/**
 * name: MtPrintingView
 * brief: ���캯����
 * param: --
 * return: --
 */
MtPrintingView::MtPrintingView(){
}

/**
 * name: ~MtPrintingView
 * brief: ����������
 * param: --
 * return: --
 */
MtPrintingView::~MtPrintingView(){
}

/**
 * name: OnInitialUpdate
 * biref: ��ͼ��ʼ�����⺯��������ʵ�ֶ���ͼ
 *        �ĳ�ʼ��������
 * param: --
 * return: --
 */
void MtPrintingView::OnInitialUpdate(){
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx=sizeTotal.cy=100;
	SetScrollSizes(MM_TEXT,sizeTotal);
}

/**
 * name: OnDraw
 * brief: ��ͼ�������⺯�����������ͼ���л��ơ�
 * param: --
 * return: --
 */
void MtPrintingView::OnDraw(CDC * /*pDC*/){
	//CDocument *pDoc=GetDocument();
	// TODO: add draw code here
}

/**
 * name: OnPreparePrinting
 * brief: ׼����ӡ���⺯�������д�ӡ��׼��������
 * param: pInfo - ָ���ӡ��Ϣ�ṹ�塣
 * return: �������ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
BOOL MtPrintingView::OnPreparePrinting(CPrintInfo *pInfo){
	// TODO:  call DoPreparePrinting to invoke the Print dialog box
	//1.���׼����ӡʧ�ܡ�
	if(!DoPreparePrinting(pInfo)){
		GetParent()->DestroyWindow();
		return(FALSE);
	}
	//2.���׼����ӡ�ɹ���
	else{
		return(TRUE);
	}
	//return(CScrollView::OnPreparePrinting(pInfo));
}

/**
 * name: OnBeginPrinting
 * brief: ��ʼ��ӡ���⺯����
 * param: pDC - ָ���ӡ�豸DC��
 *        pInfo - ָ���ӡ��Ϣ�ṹ�塣
 * return: --
 */
void MtPrintingView::OnBeginPrinting(CDC *pDC,CPrintInfo *pInfo){
	// TODO: Add your specialized code here and/or call the base class
	CScrollView::OnBeginPrinting(pDC,pInfo);
}

/**
 * name: OnPrint
 * brief: ��ӡ���⺯��������ʵ�ִ�ӡ���ơ�
 * param: pDC - ָ���ӡ�豸DC��
 *        pInfo - ָ���ӡ��Ϣ�ṹ�塣
 * return: --
 */
void MtPrintingView::OnPrint(CDC *pDC,CPrintInfo *pInfo){
	// TODO: Add your specialized code here and/or call the base class
	CScrollView::OnPrint(pDC,pInfo);
}

// MtPrintingView diagnostics
#ifdef _DEBUG
void MtPrintingView::AssertValid() const{
	CScrollView::AssertValid();
}
#ifndef _WIN32_WCE
void MtPrintingView::Dump(CDumpContext& dc) const{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

BEGIN_MESSAGE_MAP(MtPrintingView,CScrollView)
END_MESSAGE_MAP()

// MtPrintingView message handlers
