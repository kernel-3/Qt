// source-code/ui/qc/DialogQC.cpp : implementation file
//
#include"stdafx.h"
#include"DialogQC.h"
#include"afxdialogex.h"

IMPLEMENT_DYNAMIC(DialogQC,DialogBase)

/**
 * name: DialogQC
 * brief: ���캯����
 * param: pParent - ָ�򸸴���ָ�롣
 * return: --
 */
DialogQC::DialogQC(CWnd *pParent/*=NULL*/)
	:DialogBase(DialogQC::IDD, pParent){
}

/**
 * name: ~DialogQC
 * brief: ����������
 * param: --
 * return: --
 */
DialogQC::~DialogQC(){
}

/**
 * name: DoDataExchange
 * breif: ֧��DDX/DDV
 * param: pDX --
 * return: --
 */
void DialogQC::DoDataExchange(CDataExchange *pDX){
	DialogBase::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DialogQC,DialogBase)
END_MESSAGE_MAP()

//DialogQC message handlers