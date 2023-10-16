//DlgMain.h : 头文件
//
#pragma once

#include"afxwin.h"
#include"afxcmn.h"
#include"../data/FittingData.h"
#include<vector>

class MtCurveChart;

//CDlgMain 对话框
/**
 * name: CDlgMain
 * breif: 主对话框类。
 * author: yameng_he
 * date: 2015-10-27
 */
class CDlgMain
	:public CDialogEx {
	//define
public:
	enum { IDD = IDD_DIALOG_MAIN };
	typedef std::vector<FittingData> VECFITDATA;
	typedef enum {
		CUP_TYPE_STANDARD = 0,//标准杯。
		CUP_TYPE_TUBE = 1,//采血管。
		CUP_TYPE_MICROSCALE = 2,//微量杯。
	}CupType;
	//construction & destruction
public:
	CDlgMain(CWnd* pParent = NULL);//标准构造函数
	~CDlgMain(void);
	//overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);//DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonFit();
	afx_msg void OnCbnSelchangeComboExperimentMethod();
	afx_msg void OnCbnSelchangeComboCoordinatesType();
	afx_msg void OnBnClickedButtonCalculate();
	//implement
private:
	void init_controls();
	//variables
private:
	void copy_clipboard_data();
	void copy_multiple_fitting_data();//将多样本的发光值复制到左下方表格_ghm
	void copy_list_data();
	void draw_calibration_curve();//绘制定标曲线_ghm
	std::vector<double> _paras;
	std::vector<double> _paras_two;
	HICON m_hIcon;
	MtCurveChart* _curve_chart;
	CComboBox _calibration_type_combo_box;
	CComboBox _fitting_method_combo_box;
	CComboBox _experiment_method_combo_box;
	CComboBox _coordinates_type_combo_box;
	CListCtrl _fitting_data_list;
	CEdit _fitting_result_edit;
	CEdit _luminous_edit;
	CEdit _concentration_edit;
	CButton _is_s0_participation_check_box;
	CButton _calculate_button;
	VECFITDATA _fitting_data;
	VECFITDATA m_two_fitting_data;//存储两点定标时的浓度、发光值
	CListCtrl m_multiple_fitting_list;//变量——存储发光值及浓度
	CListCtrl m_two_point_calibration_list;//两点定标变量
	double m_concentration_ratio[2];//两点定标时的浓度比
	int m_nRow;//2点定标测试点的行
	int m_nCol;//2点定标测试点的列
	double _xbase{};
	double _ybase{};
	double _xration{ 1. };

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCopyButton();//复制发光值到左下方list表格中
	afx_msg void OnBnClickedClearButton();//清空左下方list表格中数据
	afx_msg void OnBnClickedCalculateButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedButtonCopy();
	afx_msg void OnBnClickedInputLuminousbutton();
	afx_msg void OnBnClickedCalculateConcentrationButton();
	afx_msg void OnBnClickedConcentrationRatioButton();
	afx_msg void OnBnClickedFittingButton();
	afx_msg void OnNMDblclkTwoPointCalibrationList(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CComboBox m_TestPointCombo;//变量——2点定标测试点下拉框
public:
	afx_msg void OnCbnKillfocusTestPointCombo();//下拉框失去焦点响应函数
	afx_msg void OnCbnSelchangeTestPointCombo();//下拉框选择值后响应函数
	afx_msg void OnBnClickedClear();
private:
	CButton m_is_calculateConcentration_by_two_box;
public:
	afx_msg void OnBnClickedInversePasteButton();
	afx_msg void OnBnClickedLumsButton();
	afx_msg void OnBnClickedInverseCopyButton();
};
