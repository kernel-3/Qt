#pragma once

#include"../../../Resource.h"
#include"../DialogModalBase.h"
#include"afxwin.h"

//DialogMessageBox dialog

class MtImageStatic;
class MtImageButton;
class MtHorizonLayout;
class MtVerticalLayout;

/**
 * name: DialogMessageBox
 * breif: 消息对话框，对MessageBox进行定制。
 * author: yameng_he
 * date: 2015-06-16
 */
class DialogMessageBox
	:public DialogModalBase{
	DECLARE_DYNAMIC(DialogMessageBox)
//define
public:
	enum{IDD=IDD_DIALOG_MESSAGE_BOX,
		IDOPERATION1=101,IDOPERATION2=102,IDOPERATION3=103,};
//construction & destruction
public:
	DialogMessageBox(const CString &title,const int width,
		const int height,const int image_no,const CString &message,
		const CString &operation_1_name,const CString &operation_2_name,
		const CString &operation_3_name,CWnd *pParent=NULL);//standard constructor
	virtual ~DialogMessageBox();
//overrides
protected:
	virtual void DoDataExchange(CDataExchange *pDX);//DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnBnClickedButtonOperation1();
	afx_msg void OnBnClickedButtonOperation2();
	afx_msg void OnBnClickedButtonOperation3();
//implement
private:
	void init_window();
	void init_controls();
//variables
private:
	CString _title;
	int _width;
	int _height;
	int _image_no;
	CString _message;
	CString _operation_1_name;
	CString _operation_2_name;
	CString _operation_3_name;
	MtImageStatic *_image_static;
	MtImageStatic *_message_static;
	MtImageButton *_operation_1_button;
	MtImageButton *_operation_2_button;
	MtImageButton *_operation_3_button;
	MtVerticalLayout *_child_layout_1;
	MtHorizonLayout *_child_layout_2;
	MtHorizonLayout *_child_layout_3;
	MtVerticalLayout *_main_layout;
};

extern unsigned int WarningMessageBox(const CString &message,
	CWnd *parent=NULL,const int width=300,const int height=200);
extern unsigned int ErrorMessageBox(const CString &message,
	CWnd *parent=NULL,const int width=300,const int height=200);
extern unsigned int QuestionMessageBox(const CString &message,
	CWnd *parent=NULL,const int width=300,const int height=200);
extern unsigned int QuestionMessageBoxEx(const CString &message,
	CWnd *parent=NULL,const int width=400,const int height=200);