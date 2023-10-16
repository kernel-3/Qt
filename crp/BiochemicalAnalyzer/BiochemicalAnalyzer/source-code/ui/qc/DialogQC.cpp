// source-code/ui/qc/DialogQC.cpp : implementation file
//
#include"stdafx.h"
#include"DialogQC.h"
#include"afxdialogex.h"

IMPLEMENT_DYNAMIC(DialogQC,DialogBase)

/**
 * name: DialogQC
 * brief: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
DialogQC::DialogQC(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogQC::IDD, pParent){
}

/**
 * name: ~DialogQC
 * brief: 析构函数。
 * param: --
 * return: --
 */
DialogQC::~DialogQC(){
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV
 * param: pDX --
 * return: --
 */
void DialogQC::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DialogQC,DialogBase)
END_MESSAGE_MAP()

//DialogQC message handlers