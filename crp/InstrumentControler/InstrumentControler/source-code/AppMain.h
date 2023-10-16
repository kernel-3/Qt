//CAppMain.h : main header file for the InstrumentControler DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include"../resource.h"		// main symbols

// CAppMain
// See InstrumentControler.cpp for the implementation of this class
//

/**
 * name: CAppMain
 * brief: 程序入口类。
 * author: yameng_he
 * date: 2015-12-23
 */
class CAppMain
	:public CWinApp{
//construction & destruction
public:
	CAppMain();
//overrides
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};