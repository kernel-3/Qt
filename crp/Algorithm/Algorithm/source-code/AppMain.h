//AppMain.h : main header file for the Algorithm DLL
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include"../resource.h" //main symbols

// AppMain
// See Algorithm.cpp for the implementation of this class
//

/**
 * name: AppMain
 * brief: 程序入口类，负责DLL初始化、释放等操作。
 * author: yameng_he
 * date: 2015-04-30
 */
class AppMain
	:public CWinApp{
//construction & destruction
public:
	AppMain();
//overrides
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};