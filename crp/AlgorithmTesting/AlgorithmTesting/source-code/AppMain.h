//AppMain.h:PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include"../resource.h"	//������

//CAppMain:
//�йش����ʵ�֣������ AlgorithmTesting.cpp
//

/**
 * name: CAppMain
 * brief: Ӧ�ó�������ࡣ
 * author: yameng_he
 * date: 2015-10-27
 */
class CAppMain
	:public CWinApp{
//construction & destruction
public:
	CAppMain();
//overrides
protected:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CAppMain theApp;