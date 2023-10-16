//AppMain.h:PROJECT_NAME 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include"../resource.h"	//主符号

//CAppMain:
//有关此类的实现，请参阅 AlgorithmTesting.cpp
//

/**
 * name: CAppMain
 * brief: 应用程序入口类。
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