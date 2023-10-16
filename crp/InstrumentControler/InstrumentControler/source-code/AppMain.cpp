//AppMain.cpp : Defines the initialization routines for the DLL.
//

#include"stdafx.h"
#include"AppMain.h"
#include"common/CommonData.h"
#include"common/Logs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"../../lib/MFCToolkit.lib")

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any Functionss exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the Functions.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunctions()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal Functions body here
//		}
//
//		It is very important that this macro appear in each
//		Functions, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		Functions, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

//CAppMain

BEGIN_MESSAGE_MAP(CAppMain,CWinApp)
END_MESSAGE_MAP()

//CAppMain construction

/**
 * name: CAppMain
 * breif: 构造函数。
 * param: --
 * return: --
 */
CAppMain::CAppMain(){
	//TODO: add construction code here,
	//Place all significant initialization in InitInstance
}

//The one and only CAppMain object
CAppMain theApp;

//CAppMain initialization

/**
 * name: InitInstance
 * breif: 动态链接库初始化虚拟函数，负责动态库加载时初始化
 *        动态链接库环境。
 * param: --
 * return: 如果动态链接库初始化实例成功返回TRUE，否则返回FALSE。
 */
BOOL CAppMain::InitInstance(){
	CWinApp::InitInstance();
	CommonData::instance();
	Logs::instance();
	return(TRUE);
}