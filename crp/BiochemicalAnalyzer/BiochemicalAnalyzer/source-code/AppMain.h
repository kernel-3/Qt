
// ChemAnalyzer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include"../resource.h"		// main symbols

// AppMain:
// See AppMain.cpp for the implementation of this class
//

/**
 * name: AppMain
 * brief: 程序入口类,负责整个进程运行环境的初始化与释放。
 * author: yameng_he
 * date: 2014-12-04
 */
class AppMain
	:public CWinApp{
//constructor & destructor
public:
	AppMain();
//overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};

extern AppMain theApp;