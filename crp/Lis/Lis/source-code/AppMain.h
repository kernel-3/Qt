// AppMain.h: main header file for the Lis DLL
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include"../resource.h"		// main symbols

// AppMain
// See AppMain.cpp for the implementation of this class
//

/**
 * name: AppMain
 * brief: ��������࣬����DLL��ʼ�����ͷŵȲ�����
 * author: yameng_he
 * date: 2014-12-19
 */
class AppMain
	:public CWinApp{
//construction & destruction
public:
	AppMain();
//overrides
protected:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};