// AppMain.cpp: Defines the initialization routines for the DLL.
//

#include"stdafx.h"
#include"AppMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"../../lib/MFCToolkit.lib")

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//
// AppMain

BEGIN_MESSAGE_MAP(AppMain,CWinApp)
END_MESSAGE_MAP()

// AppMain construction
/**
 * name: AppMain
 * brief: 构造函数。
 * param: --
 * return: --
 */
AppMain::AppMain(){
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only AppMain object
AppMain theApp;

// AppMain initialization
/**
 * name: InitInstance
 * brief: DLL初始化虚拟函数，负责对DLL进行初始化操作。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL AppMain::InitInstance(){
	CWinApp::InitInstance();
	return(TRUE);
}