// ChemAnalyzer.cpp : Defines the class behaviors for the application.
//

#include"stdafx.h"
#include"AppMain.h"
#include"ui/DialogMain.h"
#include"../../../include/mfctoolkit/env/MtGdiplus.h"
#include"../../../include/algorithm/calibration/CalibrationFactory.h"
#include"global/Theme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"../../lib/MFCToolkit.lib")
#pragma comment(lib,"../../lib/Lis.lib")
#pragma comment(lib,"../../lib/Algorithm.lib")
#pragma comment(lib,"../../lib/InstrumentControler.lib")

//AppMain
BEGIN_MESSAGE_MAP(AppMain,CWinApp)
	ON_COMMAND(ID_HELP,&CWinApp::OnHelp)
END_MESSAGE_MAP()

//AppMain construction
/**
 * name: AppMain
 * brief: 构造函数。
 * param: --
 * return: --
 */
AppMain::AppMain(){
	//support Restart Manager
	m_dwRestartManagerSupportFlags=AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

//The one and only AppMain object
AppMain theApp;

//AppMain initialization
/**
 * name: InitInstance
 * brief: 初始化实例，负责构建进程运行环境。
 * param: --
 * return: 此函数总返回FALSE。
 */
BOOL AppMain::InitInstance(){
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize=sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC=ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager=new CShellManager;
	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	//////////////////////////////////////////////////////////////////////
	//1.初始化COM库。
	CoInitialize(NULL);
	//2.初始化GDI+运行环境。
	MtGdiplus::instance()->initialize();
	//3.为当前系统主题加载图片。
	Theme::instance()->load_images();
	//////////////////////////////////////////////////////////////////////
	DialogMain dlg;
	m_pMainWnd=&dlg;
	INT_PTR nResponse=dlg.DoModal();
	if(nResponse==IDOK){
		// TODO: Place code here to handle when the dialog is
		// dismissed with OK
	}else if(nResponse==IDCANCEL){
		// TODO: Place code here to handle when the dialog is
		// dismissed with Cancel
	}else if(nResponse==-1){
		TRACE(traceAppMsg,0,"Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg,0,"Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	// Delete the shell manager created above.
	if(pShellManager!=NULL){
		delete pShellManager;
	}
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return(FALSE);
}

/**
 * name: ExitInstance
 * brief: 进程实例退出时，调用此虚拟函数。
 * param: --
 * return:
 */
int AppMain::ExitInstance(){
	// TODO: Add your specialized code here and/or call the base class
	//1.卸载系统主题加载的图片。
	Theme::instance()->unload_images();
	//2.释放GDI+运行环境。
	MtGdiplus::instance()->release();
	//3.释放COM库。
	CoUninitialize();
	//4.调用并返回基类相应函数运行结果。
	return(CWinApp::ExitInstance());
}