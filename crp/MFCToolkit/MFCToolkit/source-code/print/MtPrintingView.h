#pragma once

/**
 * name: MtPrintingView
 * brief: ����ӡ����ͼ�࣬Ϊʵ�ִ�ӡ���������
 *        MFC��ӡʱ�������ͼ�ࡣ
 * author: yameng_he
 * date: 2014-07-17 
 */
class MtPrintingView
	:public CScrollView{
	DECLARE_DYNCREATE(MtPrintingView)
//constructor & destructor
public:
	MtPrintingView(); //protected constructor used by dynamic creation
	virtual ~MtPrintingView();
//overrides
protected:
	virtual void OnInitialUpdate();//first time after construct
	virtual void OnDraw(CDC *pDC);//overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
	virtual void OnBeginPrinting(CDC *pDC,CPrintInfo *pInfo);
	virtual void OnPrint(CDC *pDC,CPrintInfo *pInfo);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	DECLARE_MESSAGE_MAP()
};