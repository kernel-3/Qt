//DlgMain.cpp:实现文件
//

#include"stdafx.h"
#include"../AppMain.h"
#include"DlgMain.h"
#include <algorithm>
#include <algorithm>
#include <cassert>
#include"afxdialogex.h"
#include"../../../../include/mfctoolkit/control/MtCurveChart.h"
#include"../../../../include/algorithm/calibration/CalibrationFactory.h"
#include"DlgInput.h"
#include"../../DlgMultipleInput.h"
#include <vector>
#include <cstring>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg
	:public CDialogEx {
	//define
public:
	enum { IDD = IDD_ABOUTBOX };
	//construction
public:
	CAboutDlg();
	//overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);//DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg()
	:CDialogEx(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//CDlgMain对话框

/**
 * name: CDlgMain
 * breif: 构造函数。
 * param: pParent - 指向父窗口指针。
 * return: --
 */
CDlgMain::CDlgMain(CWnd* pParent/*=NULL*/)
	:CDialogEx(CDlgMain::IDD, pParent)
	, _curve_chart(new MtCurveChart)
	, _fitting_data() {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

/**
 * name: ~CDlgMain
 * breif: 析构函数。
 * param: --
 * return: --
 */
CDlgMain::~CDlgMain() {
	delete _curve_chart;
}

/**
 * name: DoDataExchange
 * breif: 支持DDX/DDV。
 * parma: pDX -
 * return: --
 */
void CDlgMain::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_CURVE, *_curve_chart);
	DDX_Control(pDX, IDC_COMBO_CALIBRATION_TYPE, _calibration_type_combo_box);
	DDX_Control(pDX, IDC_COMBO_FITTING_METHOD, _fitting_method_combo_box);
	DDX_Control(pDX, IDC_COMBO_EXPERIMENT_METHOD, _experiment_method_combo_box);
	DDX_Control(pDX, IDC_COMBO_COORDINATES_TYPE, _coordinates_type_combo_box);
	DDX_Control(pDX, IDC_LIST_FITTING_DATA, _fitting_data_list);
	DDX_Control(pDX, IDC_EDIT_FITTING_RESULT, _fitting_result_edit);
	DDX_Control(pDX, IDC_EDIT_LUMINOUS, _luminous_edit);
	DDX_Control(pDX, IDC_EDIT_CONCENTRATION, _concentration_edit);
	DDX_Control(pDX, IDC_CHECK_IS_S0_PARTICIPATION, _is_s0_participation_check_box);
	DDX_Control(pDX, IDC_BUTTON_CALCULATE, _calculate_button);
	DDX_Control(pDX, IDC_MULTIPLE_FITTING_LIST, m_multiple_fitting_list);
	DDX_Control(pDX, IDC_TWO_POINT_CALIBRATION_LIST, m_two_point_calibration_list);
	DDX_Control(pDX, IDC_TEST_POINT_COMBO, m_TestPointCombo);
	DDX_Control(pDX, IDC_TWO_CALCULATE_CONCENTRATION_CHECK, m_is_calculateConcentration_by_two_box);
}

/**
 * name: OnInitDialog
 * breif: 对话框初始化虚拟函数。
 * param: --
 * return: 此函数一直返回TRUE。
 */
BOOL CDlgMain::OnInitDialog() {
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	////////////////////////////////////////////////
	//1.初始化对话框中控件。
	init_controls();
	////////////////////////////////////////////////
	return(TRUE);//除非将焦点设置到控件，否则返回 TRUE
}

/**
 * name: OnSysCommand
 * breif: 系统命令消息响应函数。
 * param: nID - 命令ID。
 *        lParam - 命令参数。
 * return: --
 */
void CDlgMain::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgMain::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CDlgMain::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgMain::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgMain::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_FIT, &CDlgMain::OnBnClickedButtonFit)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPERIMENT_METHOD, &CDlgMain::OnCbnSelchangeComboExperimentMethod)
	ON_CBN_SELCHANGE(IDC_COMBO_COORDINATES_TYPE, &CDlgMain::OnCbnSelchangeComboCoordinatesType)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CDlgMain::OnBnClickedButtonCalculate)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_COPY_BUTTON, &CDlgMain::OnBnClickedCopyButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CDlgMain::OnBnClickedClearButton)
	ON_BN_CLICKED(IDC_CALCULATE_BUTTON, &CDlgMain::OnBnClickedCalculateButton)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CDlgMain::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CDlgMain::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CDlgMain::OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_INPUT_LUMINOUSBUTTON, &CDlgMain::OnBnClickedInputLuminousbutton)
	ON_BN_CLICKED(IDC_CALCULATE_CONCENTRATION_BUTTON, &CDlgMain::OnBnClickedCalculateConcentrationButton)
	ON_BN_CLICKED(IDC_CONCENTRATION_RATIO_BUTTON, &CDlgMain::OnBnClickedConcentrationRatioButton)
	ON_BN_CLICKED(IDC_FITTING_BUTTON, &CDlgMain::OnBnClickedFittingButton)
	ON_NOTIFY(NM_DBLCLK, IDC_TWO_POINT_CALIBRATION_LIST, &CDlgMain::OnNMDblclkTwoPointCalibrationList)
	ON_CBN_KILLFOCUS(IDC_TEST_POINT_COMBO, &CDlgMain::OnCbnKillfocusTestPointCombo)
	ON_CBN_SELCHANGE(IDC_TEST_POINT_COMBO, &CDlgMain::OnCbnSelchangeTestPointCombo)
	ON_BN_CLICKED(IDC_CLEAR, &CDlgMain::OnBnClickedClear)
	ON_BN_CLICKED(IDC_INVERSE_PASTE_BUTTON, &CDlgMain::OnBnClickedInversePasteButton)
	ON_BN_CLICKED(IDC_LUMS_BUTTON, &CDlgMain::OnBnClickedLumsButton)
	ON_BN_CLICKED(IDC_INVERSE_COPY_BUTTON, &CDlgMain::OnBnClickedInverseCopyButton)
END_MESSAGE_MAP()

//CDlgMain 消息处理程序

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
/**
 * name: OnPaint
 * breif: 对话框绘制消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnPaint() {
	if (IsIconic()) {
		CPaintDC dc(this);//用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		//使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		//绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}

/**2017.02.23
 * name: draw_calibration_curve
 * breif: 六点拟合绘制定标曲线
 * param: --
 * return: --
 */
void CDlgMain::draw_calibration_curve()
{
	const unsigned int fitting_data_size = _fitting_data.size();
	//TODO: Add your control notification handler code here
	//1.检测输入的拟合数据数量是否合法。
	if (fitting_data_size < 4) {
		MessageBox(_T("很抱歉，请输入至少4组数据，谢谢！"),
			_T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	//2.获取当前用户选择的定标信息，并且判断获取是否成功。
	//2-1.获取当前用户选择的定标类型，并且判断获取是否成功。
	int item = _calibration_type_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择定标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_calibration_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationType calibration_type =
		static_cast<CalibrationFactory::CalibrationType>(
			_calibration_type_combo_box.GetItemData(item));
	//2-2.获取当前用户选择的定标方法，并且判断获取是否成功。
	item = _fitting_method_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择定标方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_fitting_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationMethod calibration_method =
		static_cast<CalibrationFactory::CalibrationMethod>(
			_fitting_method_combo_box.GetItemData(item));
	//2-3.获取当前用户选择的实验方法，并且判断获取是否成功。
	item = _experiment_method_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择实验方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_experiment_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::ExperimentMethod experiment_method =
		static_cast<CalibrationFactory::ExperimentMethod>(
			_experiment_method_combo_box.GetItemData(item));
	//2-4.获取当前用户选择的坐标类型，并且判断获取是否成功。
	item = _coordinates_type_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择坐标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_coordinates_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CoordinatesType coordinates_type =
		static_cast<CalibrationFactory::CoordinatesType>(
			_coordinates_type_combo_box.GetItemData(item));
	//2-5.获取当前s0是否参与拟合。
	const BOOL is_s0_participation = _is_s0_participation_check_box.GetCheck();
	//3.对输入数据进行拟合，并且判断拟合是否成功。
	//3-1.声明当前操作所需变量。
	double concs[100] = {};// {0, 0.51, 5.07, 20, 80, 160};// {0.0, 0.51, 1.01, 1.52, 5.07, 10.13};
	double lums[100] = {};// {0.0001, 0.0027, 0.0176, 0.0309, 0.0667, 0.0899};// {0.0001, 0.0027, 0.0039, 0.0052, 0.0176, 0.0242};
	for (unsigned int i = 0; i != fitting_data_size; ++i) {
		concs[i] = _fitting_data[i].get_x();
		lums[i] = _fitting_data[i].get_y();
		//_fitting_data.push_back({ concs[i], lums[i] });
	}
	double a[5], R = 0.0, xbase = 0.0, ybase{}, xration{};
	//3-2.对当前输入数据进行拟合，并且判断拟合是否成功。
	if (CalibrationFactory::calibrate(calibration_type, calibration_method,
		experiment_method, coordinates_type, is_s0_participation, concs, lums,
		fitting_data_size, a, 5, R, xbase, ybase, xration) < 0) {
		MessageBox(_T("数据拟合失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	//3-4.显示拟合结果。
	CString text(_T(""));
	if (CalibrationFactory::CALIBRATION_METHOD_LINEAR == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nR2=%.6lf\r\nD=%.6lf"), a[0], a[1], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}
	else if (CalibrationFactory::CALIBRATION_METHOD_CUBIC_POLYNOMIAL == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nc=%.6lf\r\nd=%.6lf\r\nR2=%.6lf\r\nD=%.6lf"),
			a[0], a[1], a[2], a[3], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}
	else if (CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG4P == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nc=%.6lf\r\nd=%.6lf\r\nR2=%.6lf\r\nD=%.6lf"),
			a[0], a[1], a[2], a[3], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}
	else if (CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG5P == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nc=%.6lf\r\nd=%.6lf\r\ne=%.6lf\r\nR2=%.6lf\r\nD=%.6lf"),
			a[1], a[3], a[2], a[0], a[4], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}

	//3-5.保存当前拟合参数。
	int para_size{};
	switch (calibration_method)
	{
	case CalibrationFactory::CALIBRATION_METHOD_LINEAR:
		para_size = 2;
		break;
	case CalibrationFactory::CALIBRATION_METHOD_CUBIC_POLYNOMIAL:
	case CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG4P:
		para_size = 4;
		break;
	case CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG5P:
		para_size = 5;
		break;
	default:
	{assert(false); }
	}

	_paras.clear();
	for (int i = 0; i < para_size; ++i)
		_paras.push_back(a[i]);
	_xbase = xbase;
	_ybase = ybase;
	_xration = xration;

	std::vector<double> conc1{ concs, concs + fitting_data_size };
	std::vector<double> lum1{ lums, lums + fitting_data_size };
	//CalibrationFactory::calculate_luminous(calibration_type, calibration_method, experiment_method, coordinates_type
	//	, is_s0_participation, &_paras[0], _paras.size(), 0, _ybase);

	//double x = _fitting_data[0].get_x();
	//if (fabs(x) < 0.000001)
	//{
	//	if (_fitting_data[0].get_y() > _ybase)
	//		_ybase = _fitting_data[0].get_y();
	//}

	//CalibrationFactory::calculate_concentration(calibration_type, calibration_method, experiment_method, coordinates_type
	//	, is_s0_participation, &_paras[0], _paras.size(), _ybase, _xbase);


	//4.对曲线进行绘制。
	//4-1.清除当前曲线、点集内容。
	_curve_chart->clear_points_of_curve_two();
	_curve_chart->clear_points_of_point_two_set();
	_curve_chart->clear_points_of_curve();
	_curve_chart->clear_points_of_point_set();
	//4-2.计算横坐标浓度的显示范围。
	/*double min_conc = _fitting_data[0].get_x();
	double max_conc = _fitting_data[fitting_data_size - 1].get_x();
	if ((CalibrationFactory::convert_x_y_coordinates(coordinates_type, min_conc) < 0) ||
		(CalibrationFactory::convert_x_y_coordinates(coordinates_type, max_conc) < 0)) {
		MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	max_conc *= 1.05;*/

	//4-3.根据计算定标点上的浓度，并且判断计算是否成功。
	for (unsigned int i = 0; i != fitting_data_size; ++i) {
		//4-3-1.获取当前待拟合数据。
		double cal_conc = 0.0;
		for (unsigned int j = 0; j != fitting_data_size; ++j) {
			concs[j] = _fitting_data[j].get_x();
			lums[j] = _fitting_data[j].get_y();
		}
		//4-3-2.反算浓度，并且判断反算是否成功。
		int ret = CalibrationFactory::calculate_concentration(calibration_type, calibration_method,
			experiment_method, coordinates_type, is_s0_participation, a, para_size,
			_xration, _xbase, _ybase,
			lums[i], cal_conc);
		if (ret < 0)
		{
			MessageBox(_T("反算浓度失败，请重试！"), _T("警告"),
				MB_ICONWARNING | MB_OK);
			return;
		}
		//4-3-3.书写计算的浓度。
		text.Format(_T("%.2lf"), cal_conc);
		_fitting_data_list.SetItemText(i, 2, text);
		//4-3-4.书写相对计算的相对偏差。
		if (0 != i) {
			text.Format(_T("%.2lf"), fabs(
				_fitting_data[i].get_x() - cal_conc) /
				fabs(_fitting_data[i].get_x()));
		}
		else {
			text.Format(_T("--"));
		}
		_fitting_data_list.SetItemText(i, 3, text);
		//4-3-5.对计算出的浓度进行坐标变换，并且判断变换是否成功。
		if (CalibrationFactory::convert_x_y_coordinates(coordinates_type, cal_conc) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
	}
	//4-4.计算y轴的范围。
	//double min_lum = _fitting_data[0].get_y();
	//double max_lum = _fitting_data[fitting_data_size - 1].get_y();
	//if ((CalibrationFactory::convert_x_y_coordinates(coordinates_type,
	//	_fitting_data[0].get_y(), min_lum) < 0) || (CalibrationFactory::
	//		convert_x_y_coordinates(coordinates_type, _fitting_data[0].
	//			get_y(), max_lum) < 0)) {
	//	MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
	//	return;
	//}
	//if (min_lum > max_lum) {
	//	const double temp = min_lum;
	//	min_lum = max_lum;
	//	max_lum = temp;
	//}
	//while (conc <= conc1.back()) {
	//	double cal_lum = 0.0;
	//	double conc_t = conc;
	//	if (CalibrationFactory::convert_to_x_y_coordinates(coordinates_type, conc_t) < 0) {
	//		MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
	//		return;
	//	}
	//	if (CalibrationFactory::calculate_luminous(calibration_type, calibration_method,
	//		experiment_method, coordinates_type, is_s0_participation, a, para_size, _xration, _xbase, conc_t, cal_lum) < 0) {
	//		MessageBox(_T("反算浓度失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
	//		return;
	//	}
	//	if (CalibrationFactory::convert_x_y_coordinates(
	//		coordinates_type, _fitting_data[0].get_y(), cal_lum) < 0) {
	//		MessageBox(_T("反算浓度失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
	//		return;
	//	}
	//}
	//max_lum *= 1.05;
	////4-6.设置横纵坐标范围。
	_curve_chart->set_horizontal_coordinate_range(conc1[0], conc1.back());
	_curve_chart->set_vertical_coordinate_range(lum1[0], lum1.back());
	_curve_chart->set_curve_color(255, 255, 0, 0);
	_curve_chart->RedrawWindow();
	////4-7.计算当前曲线上的点，用以形成曲线。
	////4-7-1.声明当前操作所需变量。
	//conc = min_conc;
	//conc_span = abs(max_conc - min_conc) / 1000.0;

	double conc = conc1[0];
	double conc_span = abs(conc1.back() - conc1[0]) / 1000.0;
	//4-7-2.循环计算所有坐标点的浓度。
	while (conc <= conc1.back()) {
		//a.获取当前待拟合数据。
		double cal_lum = 0.0;
		//b.将当前浓度值转换为x-y类型坐标。
		double conc_t = conc;
		if (CalibrationFactory::convert_to_x_y_coordinates(coordinates_type, conc_t) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//c.计算发光值，并且判断计算是否成功。
		if (CalibrationFactory::calculate_luminous(calibration_type, calibration_method,
			experiment_method, coordinates_type, is_s0_participation, a, para_size, 1., 0., conc_t, cal_lum) < 0) {
			MessageBox(_T("反算浓度失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//d.将计算出的发光值转换坐标系。
		if (CalibrationFactory::convert_x_y_coordinates(
			coordinates_type, _fitting_data[0].get_y(), cal_lum) < 0) {
			MessageBox(_T("反算浓度失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//e.保存当前拟合的点，并且判断保存是否成功。
		const int result = _curve_chart->add_point_to_curve(conc, cal_lum);
		if (result < 0) {
			if (-1 == result) {
				conc += conc_span;
				continue;
			}
			else {
				MessageBox(_T("向曲线中添加点失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
				return;
			}
		}
		conc += conc_span;
	}
	//4-7-3.计算点集上的点，用于点集绘制。
	for (unsigned int i = 0; i < fitting_data_size; ++i) {
		//a.计算当前坐标。
		double conc = conc1[i];
		/*if (CalibrationFactory::convert_x_y_coordinates(coordinates_type, conc) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}*/
		double lum = lum1[i];
		/*if (CalibrationFactory::convert_x_y_coordinates(
			coordinates_type, _fitting_data[0].get_y(), lum) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}*/
		_curve_chart->add_point_to_point_set(conc, lum);
	}
	//4-6-4.更新当前曲线图表。
	_curve_chart->RedrawWindow();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
/**
 * name: OnQueryDragIcon
 * breif: 当用户拖动最小化窗口时系统调用此函数取得光标显示。
 * param: --
 * return: 返回当前显示的光标内容。
 */
HCURSOR CDlgMain::OnQueryDragIcon() {
	return(static_cast<HCURSOR>(m_hIcon));
}

/**
 * name: OnBnClickedButtonAdd
 * breif: 用户点击“添加”按钮消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnBnClickedButtonAdd() {
	//TODO: Add your control notification handler code here
	//1.声明当前操作所需变量。
	CDlgInput dlg(this);
	//2.显示输入数据对话框。
	if (IDOK == dlg.DoModal()) {
		//2-1.向当前拟合数据中插入添加的数据。
		_fitting_data.push_back(FittingData(
			dlg.get_conc(), dlg.get_rlu()));
		//2-2.向列表框中，插入当前的数据。
		int item = _fitting_data_list.InsertItem(
			_fitting_data_list.GetItemCount(), _T(""));
		CString text(_T(""));
		text.Format(_T("%.2lf"), dlg.get_conc());
		_fitting_data_list.SetItemText(item, 0, text);
		text.Format(_T("%.2lf"), dlg.get_rlu());
		_fitting_data_list.SetItemText(item, 1, text);
		_fitting_data_list.SetItemText(item, 2, _T(""));
		_fitting_data_list.SetItemText(item, 3, _T(""));
	}
}

/**
 * name: OnBnClickedButtonEdit
 * breif: 用户点击“编辑”按钮消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnBnClickedButtonEdit() {
	// TODO: Add your control notification handler code here
	//1.获取当前用户选择编辑的内容。
	POSITION pos = _fitting_data_list.GetFirstSelectedItemPosition();
	if (0 == pos) {
		MessageBox(_T("请选中期望编辑的内容！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	const int item = _fitting_data_list.GetNextSelectedItem(pos);
	if ((item < 0) || (item >= static_cast<int>(_fitting_data.size()))) {
		MessageBox(_T("您选中的内容非法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	//2.显示“输入”对话框，准备编辑输入值。
	CDlgInput dlg(_fitting_data[item].get_x(), _fitting_data[item].get_y(), this);
	//3.如果用户成功输入修改值。
	if (IDOK == dlg.DoModal()) {
		//3-1.修改内存存储的数据值。
		_fitting_data[item].set_x(dlg.get_conc());
		_fitting_data[item].set_y(dlg.get_rlu());
		//3-2.修改列表框中，相应显示的内容。
		CString text(_T(""));
		text.Format(_T("%.2lf"), dlg.get_conc());
		_fitting_data_list.SetItemText(item, 0, text);
		text.Format(_T("%.2lf"), dlg.get_rlu());
		_fitting_data_list.SetItemText(item, 1, text);
		_fitting_data_list.SetItemText(item, 2, _T(""));
		_fitting_data_list.SetItemText(item, 3, _T(""));
	}
}

/**
 * name: OnBnClickedButtonDelete
 * breif: 用户点击“删除”按钮消息响应函数。
 * parma: --
 * return: --
 */
void CDlgMain::OnBnClickedButtonDelete() {
	//TODO: Add your control notification handler code here
	//1.获取当前用户选择删除的内容。
	POSITION pos = _fitting_data_list.GetFirstSelectedItemPosition();
	if (0 == pos) {
		MessageBox(_T("请选中期望删除的内容！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	const int item = _fitting_data_list.GetNextSelectedItem(pos);
	if ((item < 0) || (item >= static_cast<int>(_fitting_data.size()))) {
		MessageBox(_T("您选中的内容非法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	//2.从内存中删除相应数据。
	_fitting_data.erase(_fitting_data.begin() + item);
	//3.从列表控件中删除相应的数据。
	_fitting_data_list.DeleteItem(item);
}

/**
 * name: OnBnClickedButtonClear
 * breif: 用户点击“清空”按钮消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnBnClickedButtonClear() {
	//TODO: Add your control notification handler code here
	//1.清空内存内容。
	_fitting_data.clear();
	VECFITDATA temp;
	_fitting_data.swap(temp);
	//2.清空列表框内容。
	_fitting_data_list.DeleteAllItems();
}

/**
 * name: OnBnClickedButtonFit
 * breif: 用户点击“拟合”按钮消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnBnClickedButtonFit() {
	//TODO: Add your control notification handler code here
	draw_calibration_curve();
}

/**
 * name: OnCbnSelchangeComboExperimentMethod
 * brief: 实验方法下拉框选项改变消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnCbnSelchangeComboExperimentMethod() {
	// TODO: Add your control notification handler code here
	//1.如果用户选择的实验方法，如果获取失败，则直接返回。
	const int item = _experiment_method_combo_box.GetCurSel();
	if (item < 0) {
		return;
	}
	const CalibrationFactory::ExperimentMethod method =
		static_cast<CalibrationFactory::ExperimentMethod>(
			_experiment_method_combo_box.GetItemData(item));
	//2.如果当前用户选择了“竞争法”，作为实验方法。
	if (CalibrationFactory::EXPERIMENT_METHOD_COMPETITION == method) {
		//2-1.声明当前操作所需变量。
		BOOL is_existed = FALSE;
		//2-2.检测当前坐标类型是否存在"log(x)-logit(y)"类型。
		for (int i = 0; i < _coordinates_type_combo_box.GetCount(); ++i) {
			if (CalibrationFactory::COORDINATES_TYPE_LOGX_LOGITY ==
				static_cast<CalibrationFactory::CoordinatesType>(
					_coordinates_type_combo_box.GetItemData(i))) {
				is_existed = TRUE;
				break;
			}
		}
		//2-3.如果当前不存在“log(x)-logit(y)”类型坐标，则进行添加。
		if (FALSE == is_existed) {
			//2-3-1.获取当前用户选择的坐标类型。
			const int old_item = _coordinates_type_combo_box.GetCurSel();
			//2-3-2.向下拉框中添加“log(x)-logit(y)”类型坐标。
			const int item_t = _coordinates_type_combo_box.AddString(_T("log(x)-logit(y)"));
			_coordinates_type_combo_box.SetItemData(item_t, static_cast<DWORD_PTR>(
				CalibrationFactory::COORDINATES_TYPE_LOGX_LOGITY));
			//2-3-3.恢复当前用户选择的坐标类型。
			_coordinates_type_combo_box.SetCurSel(old_item);
		}
	}
	//3.如果当前用户选择了其它方法作为实验方法。
	else {
		//3-1.获取当前用户选择的坐标类型。
		const int old_item = _coordinates_type_combo_box.GetCurSel();
		//3-2.检测当前坐标类型是否存在"log(x)-logit(y)"类型，如果存在则删除。
		for (int i = 0; i < _coordinates_type_combo_box.GetCount(); ++i) {
			if (CalibrationFactory::COORDINATES_TYPE_LOGX_LOGITY ==
				static_cast<CalibrationFactory::CoordinatesType>(
					_coordinates_type_combo_box.GetItemData(i))) {
				_coordinates_type_combo_box.DeleteString(i);
				break;
			}
		}
		//3-3.恢复当前用户选择的坐标类型。
		if (old_item >= _coordinates_type_combo_box.GetCount()) {
			_coordinates_type_combo_box.SetCurSel(0);
		}
		else {
			_coordinates_type_combo_box.SetCurSel(old_item);
		}
	}
}

/**
 * name: OnCbnSelchangeComboCoordinatesType
 * brief: 坐标类型下拉框选项改变消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnCbnSelchangeComboCoordinatesType() {
	// TODO: Add your control notification handler code here
	//1.如果用户选择的坐标类型，如果获取失败，则直接返回。
	const int item = _coordinates_type_combo_box.GetCurSel();
	if (item < 0) {
		return;
	}
	const CalibrationFactory::CoordinatesType type =
		static_cast<CalibrationFactory::CoordinatesType>(
			_coordinates_type_combo_box.GetItemData(item));
	//2.如果当前选择的坐标类型为log(x)-logit(y)、log(x)-log(y)以及log(x)-y类型
	//  则不允许s0参与拟合。
	if ((CalibrationFactory::COORDINATES_TYPE_LOGX_LOGITY == type) ||
		(CalibrationFactory::COORDINATES_TYPE_LOGX_LOGY == type) ||
		(CalibrationFactory::COORDINATES_TYPE_LOGX_Y == type)) {
		_is_s0_participation_check_box.SetCheck(0);
		_is_s0_participation_check_box.EnableWindow(FALSE);
	}
	//3.如果当前选择的坐标类型为其它类型。
	else {
		_is_s0_participation_check_box.EnableWindow(TRUE);
	}
}

/**
 * name: OnBnClickedButtonCalculate
 * brief: 用户点击“计算”按钮消息响应函数。
 * param: --
 * return: --
 */
void CDlgMain::OnBnClickedButtonCalculate() {
	//TODO: Add your control notification handler code here
	//1.检测输入的拟合数据数量是否合法。
	const unsigned int fitting_data_size = _fitting_data.size();
	/*if(6!=fitting_data_size){
		MessageBox(_T("很抱歉，目前只支持六点定标，请输入六组数据，谢谢！"),
			_T("警告"),MB_ICONWARNING|MB_OK);
		return;
	}*/
	//2.获取当前用户选择的定标信息，并且判断获取是否成功。
	//2-1.获取当前用户选择的定标类型，并且判断获取是否成功。
	int item = _calibration_type_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择定标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_calibration_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationType calibration_type =
		static_cast<CalibrationFactory::CalibrationType>(
			_calibration_type_combo_box.GetItemData(item));
	//2-2.获取当前用户选择的定标方法，并且判断获取是否成功。
	item = _fitting_method_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择定标方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_fitting_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationMethod calibration_method =
		static_cast<CalibrationFactory::CalibrationMethod>(
			_fitting_method_combo_box.GetItemData(item));
	//2-3.获取当前用户选择的实验方法，并且判断获取是否成功。
	item = _experiment_method_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择实验方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_experiment_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::ExperimentMethod experiment_method =
		static_cast<CalibrationFactory::ExperimentMethod>(
			_experiment_method_combo_box.GetItemData(item));
	//2-4.获取当前用户选择的坐标类型，并且判断获取是否成功。
	item = _coordinates_type_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择坐标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_coordinates_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CoordinatesType coordinates_type =
		static_cast<CalibrationFactory::CoordinatesType>(
			_coordinates_type_combo_box.GetItemData(item));
	//2-5.获取当前s0是否参与拟合。
	const BOOL is_s0_participation = _is_s0_participation_check_box.GetCheck();
	//3.对输入数据进行拟合，并且判断拟合是否成功。
	//3-1.声明当前操作所需变量。
	double concs[100] = { 0.0 };
	double lums[100] = { 0.0 };
	for (unsigned int i = 0; i != fitting_data_size; ++i) {
		concs[i] = _fitting_data[i].get_x();
		lums[i] = _fitting_data[i].get_y();
	}
	//4.获取当前用户输入的发光值。
	CString text;
	_luminous_edit.GetWindowText(text);
	if (_T("") == text) {
		MessageBox(_T("请输入发光值！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_luminous_edit.SetFocus();
		return;
	}
	const double lum = static_cast<double>(atof(text));
	//5.计算浓度。
	double conc = 0.0;
	int ret = CalibrationFactory::calculate_concentration(
		calibration_type, calibration_method, experiment_method,
		coordinates_type, is_s0_participation, &_paras[0], _paras.size(),
		_xration, _xbase, _ybase,
		lum, conc);
	if (ret < 0) {
		MessageBox(_T("反算浓度失败，请重试！"),
			_T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}

	text.Format(_T("%.4f"), conc);
	//6.显示计算浓度。
	_concentration_edit.SetWindowText(text);
}

/**
 * name: init_controls
 * breif: 初始化对话框中控件。
 * param: --
 * return: --
 */
void CDlgMain::init_controls() {
	//1.初始化下拉框。
	int item = _calibration_type_combo_box.AddString(_T("Multipoint"));
	_calibration_type_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::CALIBRATION_TYPE_MULTIPOINT));
	item = _calibration_type_combo_box.AddString(_T("One Point"));
	_calibration_type_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::CALIBRATION_ONE_POINT));
	item = _calibration_type_combo_box.AddString(_T("Two Point"));
	_calibration_type_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::CALIBRATION_TWO_POINT));
	_calibration_type_combo_box.SetCurSel(0);
	_calibration_type_combo_box.EnableWindow(FALSE);
	item = _fitting_method_combo_box.AddString(_T("Linear"));
	_fitting_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::CALIBRATION_METHOD_LINEAR));
	item = _fitting_method_combo_box.AddString(_T("cubic polynomial"));
	_fitting_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::CALIBRATION_METHOD_CUBIC_POLYNOMIAL));
	item = _fitting_method_combo_box.AddString(_T("logit-log4P"));
	_fitting_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG4P));
	item = _fitting_method_combo_box.AddString(_T("logit-log5P"));
	_fitting_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG5P));
	_fitting_method_combo_box.SetCurSel(3);
	item = _experiment_method_combo_box.AddString(_T("Sandwich Method"));
	_experiment_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::EXPERIMENT_METHOD_SANDWICH));
	item = _experiment_method_combo_box.AddString(_T("Competition Method"));
	_experiment_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::EXPERIMENT_METHOD_COMPETITION));
	item = _experiment_method_combo_box.AddString(_T("Indirect Method"));
	_experiment_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::EXPERIMENT_METHOD_INDIRECT));
	item = _experiment_method_combo_box.AddString(_T("Capture Method"));
	_experiment_method_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::EXPERIMENT_METHOD_CAPTURE));
	_experiment_method_combo_box.SetCurSel(0);
	/*
	item=_coordinates_type_combo_box.AddString(_T("log(x)-logit(y)"));
	_coordinates_type_combo_box.SetItemData(item,static_cast<DWORD_PTR>(
		CalibrationFactory::COORDINATES_TYPE_LOGX_LOGITY));
		*/
	item = _coordinates_type_combo_box.AddString(_T("log(x)-log(y)"));
	_coordinates_type_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::COORDINATES_TYPE_LOGX_LOGY));
	item = _coordinates_type_combo_box.AddString(_T("x-y"));
	_coordinates_type_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::COORDINATES_TYPE_X_Y));
	item = _coordinates_type_combo_box.AddString(_T("log(x)-y"));
	_coordinates_type_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::COORDINATES_TYPE_LOGX_Y));
	item = _coordinates_type_combo_box.AddString(_T("x-log(y)"));
	_coordinates_type_combo_box.SetItemData(item, static_cast<DWORD_PTR>(
		CalibrationFactory::COORDINATES_TYPE_X_LOGY));
	_coordinates_type_combo_box.SetCurSel(0);
	//2.1初始化列表框。
	_fitting_data_list.SetExtendedStyle((_fitting_data_list.GetExtendedStyle()) |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	_fitting_data_list.InsertColumn(0, _T("浓度"), LVCFMT_LEFT, 100);
	_fitting_data_list.InsertColumn(1, _T("发光值"), LVCFMT_LEFT, 150);
	_fitting_data_list.InsertColumn(2, _T("计算浓度"), LVCFMT_LEFT, 100);
	_fitting_data_list.InsertColumn(3, _T("相对偏差"), LVCFMT_LEFT, 100);

	//2.2初始化列表框--多样本拟合_ghm
	m_multiple_fitting_list.SetExtendedStyle((_fitting_data_list.GetExtendedStyle()) |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_multiple_fitting_list.InsertColumn(0, _T("发光值"), LVCFMT_LEFT, 80);
	m_multiple_fitting_list.InsertColumn(1, _T("六点定标浓度"), LVCFMT_LEFT, 80);
	m_multiple_fitting_list.InsertColumn(2, _T("两点定标浓度"), LVCFMT_LEFT, 80);
	//2.2初始化列表框--两点定标_ghm
	m_two_point_calibration_list.SetExtendedStyle((_fitting_data_list.GetExtendedStyle()) |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_two_point_calibration_list.InsertColumn(0, _T("发光值"), LVCFMT_LEFT, 80);//用户手动输入两点定标时的两发光值
	m_two_point_calibration_list.InsertColumn(1, _T("浓度"), LVCFMT_LEFT, 100);//由发光值计算出的两浓度
	m_two_point_calibration_list.InsertColumn(2, _T("测试点浓度"), LVCFMT_LEFT, 100);//下拉框，两点定标时的两点设置
	m_two_point_calibration_list.InsertColumn(3, _T("浓度比"), LVCFMT_LEFT, 100);//相应浓度（A、B）与原浓度的比值

	//3.初始化图表控件。
	//_curve_chart->set_horizontal_coordinate_title(_T("浓度"));
	//_curve_chart->set_vertical_coordinate_title(_T("发\r\n光\r\n值"));
	//4.初始化文本编辑框。
	_fitting_result_edit.SetReadOnly(TRUE);
	_fitting_result_edit.SetWindowText(_T(""));
	_luminous_edit.SetWindowText(_T(""));
	_concentration_edit.SetWindowText(_T(""));
	_concentration_edit.SetReadOnly(TRUE);
	//5.初始化复选框。
	_is_s0_participation_check_box.SetCheck(0);
	_is_s0_participation_check_box.EnableWindow(FALSE);
	CRect rect;
	_curve_chart->GetWindowRect(&rect);
}

BOOL CDlgMain::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 0x56)
	{
		if (GetKeyState(VK_CONTROL) < 0)
		{
			copy_clipboard_data();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDlgMain::copy_clipboard_data()
{
	if (!IsClipboardFormatAvailable(CF_TEXT))
		return;

	if (!OpenClipboard())
		return;
	HGLOBAL hmem = GetClipboardData(CF_TEXT);
	if (hmem == NULL)
	{
		CloseClipboard();
		return;
	}

	typedef  std::pair<CString, CString> SPair;
	typedef  std::vector<SPair> SVec;
	SVec vec;

	LPSTR pbuff = (LPSTR)GlobalLock(hmem);
	LPSTR pb = pbuff;
	SPair v;
	while (*pbuff != _T('\0'))
	{
		++pbuff;
		if (*pbuff == _T('\t'))
		{
			v.first = CString(pb, pbuff - pb);
			pb = pbuff + 1;
		}
		else if (*pbuff == _T('\n'))
		{
			v.second = CString(pb, pbuff - pb);
			if (v.first == _T(""))
				break;

			vec.push_back(v);
			pb = pbuff + 1;
		}
	}
	GlobalUnlock(hmem);
	CloseClipboard();

	if (vec.empty())
		return;

	_fitting_data.clear();
	_fitting_data_list.DeleteAllItems();

	for (int i = 0; i < vec.size(); ++i)
	{
		CString sconc = vec[i].first;
		CString srlu = vec[i].second;
		_fitting_data.push_back(FittingData(std::atof((LPCSTR)sconc), std::atof((LPCTSTR)srlu)));
		_fitting_data_list.InsertItem(i, sconc);
		_fitting_data_list.SetItemText(i, 1, srlu);
	}
}
/*
 * name:OnBnClickedCopyButton
 * brief: 粘贴剪切板发光值数据到右方list表格
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedCopyButton()
{
	// TODO: Add your control notification handler code here
	copy_multiple_fitting_data();
}
/*
 * name:copy_multiple_fitting_data
 * brief: 复制剪切板多样本发光值数据到右方list表格
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::copy_multiple_fitting_data()
{
	if (!IsClipboardFormatAvailable(CF_TEXT))
		return;

	if (!OpenClipboard())
		return;
	HGLOBAL hmem = GetClipboardData(CF_TEXT);
	if (hmem == NULL)
	{
		CloseClipboard();
		return;
	}

	typedef  std::vector<CString> SVec;
	SVec vec;

	LPSTR pbuff = (LPSTR)GlobalLock(hmem);
	LPSTR pb = pbuff;
	while (*pbuff != _T('\0'))
	{
		++pbuff;
		if (*pbuff == _T('\n'))
		{
			vec.push_back(CString(pb, pbuff - pb));
			pb = pbuff + 1;
		}
	}
	GlobalUnlock(hmem);
	CloseClipboard();

	if (vec.empty())
		return;

	m_multiple_fitting_list.DeleteAllItems();

	for (int i = 0; i < vec.size(); ++i)
	{
		CString slums = vec[i];
		m_multiple_fitting_list.InsertItem(i, slums);
	}
}
/**
 * name: OnBnClickedCalculateButton
 * brief: 用户点击“计算”按钮消息响应函数
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedCalculateButton()
{
	// TODO: Add your control notification handler code here
	const BOOL is_CalculateConcentrationByTwo = m_is_calculateConcentration_by_two_box.GetCheck();
	VECFITDATA fitting_data;
	if (is_CalculateConcentrationByTwo)
	{
		fitting_data.assign(m_two_fitting_data.begin(), m_two_fitting_data.end());
	}
	else
	{
		fitting_data.assign(_fitting_data.begin(), _fitting_data.end());
	}

	//1.检测输入的拟合数据数量是否合法。
	const unsigned int fitting_data_size = fitting_data.size();
	/*if(6!=fitting_data_size)
	{
		MessageBox(_T("很抱歉，目前只支持六点定标，请输入六组数据，谢谢！"),
			_T("警告"),MB_ICONWARNING|MB_OK);
		return;
	}*/
	//2.获取当前用户选择的定标信息，并且判断获取是否成功。
	//2-1.获取当前用户选择的定标类型，并且判断获取是否成功。
	int item = _calibration_type_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择定标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_calibration_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationType calibration_type =
		static_cast<CalibrationFactory::CalibrationType>(
			_calibration_type_combo_box.GetItemData(item));
	//2-2.获取当前用户选择的定标方法，并且判断获取是否成功。
	item = _fitting_method_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择定标方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_fitting_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationMethod calibration_method =
		static_cast<CalibrationFactory::CalibrationMethod>(
			_fitting_method_combo_box.GetItemData(item));
	//2-3.获取当前用户选择的实验方法，并且判断获取是否成功。
	item = _experiment_method_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择实验方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_experiment_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::ExperimentMethod experiment_method =
		static_cast<CalibrationFactory::ExperimentMethod>(
			_experiment_method_combo_box.GetItemData(item));
	//2-4.获取当前用户选择的坐标类型，并且判断获取是否成功。
	item = _coordinates_type_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择坐标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_coordinates_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CoordinatesType coordinates_type =
		static_cast<CalibrationFactory::CoordinatesType>(
			_coordinates_type_combo_box.GetItemData(item));
	//2-5.获取当前s0是否参与拟合。
	const BOOL is_s0_participation = _is_s0_participation_check_box.GetCheck();
	//3.获取list表格中输入的所有发光值的个数
	int luminous_count = 0;//获取右方list表格中输入的所有发光值的个数
	for (int i = 0; m_multiple_fitting_list.GetItemText(i, 0) != _T(""); i++)
	{
		luminous_count++;
	}
	for (int i = 0; i < luminous_count; i++)
	{
		//4.对输入数据进行拟合，并且判断拟合是否成功
		//4.1声明当前操作所需变量
		double concs_[100] = { 0.0 };
		double lums_[100] = { 0.0 };
		for (unsigned int j = 0; j != fitting_data_size; ++j)
		{
			concs_[j] = fitting_data[j].get_x();
			lums_[j] = fitting_data[j].get_y();
		}
		//5.获取当前用户输入的发光值
		CString luminous = m_multiple_fitting_list.GetItemText(i, 0);//获取第0列第i行的发光值
		if (_T("") == luminous)
		{
			MessageBox(_T("请输入发光值!"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}

		const double lum = static_cast<double>(atof(luminous));
		double conc = 0.0;
		//6.计算浓度
		int ret = CalibrationFactory::calculate_concentration(
			calibration_type, calibration_method, experiment_method,
			coordinates_type, is_s0_participation, &_paras[0], _paras.size(),
			_xration, _xbase, _ybase, lum, conc);
		if (ret < 0)
		{
			MessageBox(_T("反算浓度失败"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		CString str_text;
		str_text.Format(_T("%.4lf"), conc);
		//7.2显示计算浓度。
		if (is_CalculateConcentrationByTwo)
		{
			m_multiple_fitting_list.SetItemText(i, 2, str_text);
		}
		else
		{
			m_multiple_fitting_list.SetItemText(i, 1, str_text);
		}
	}
}
/*
 * name:OnBnClickedClearButton
 * brief: “清空”右方list表格数据
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedClearButton()
{
	// TODO: Add your control notification handler code here
	m_multiple_fitting_list.DeleteAllItems();
}
/*
 * name:OnBnClickedAddButton
 * brief: “添加”数据到右方list表格
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedAddButton()
{
	// TODO: Add your control notification handler code here
	//1.置反算浓度值的标志位luminous为true
	bool luminous = true;
	DlgMultipleInput DlgMultipleInput(luminous);
	//2.获取左下方list表格中输入的所有发光值的个数
	int luminous_count = 0;
	for (int i = 0; m_multiple_fitting_list.GetItemText(i, 0) != _T(""); i++)
	{
		luminous_count++;
	}
	//3.输入要添加的某一个发光值
	if (IDOK == DlgMultipleInput.DoModal())
	{
		//DlgMultipleInput DlgMultipleInput(luminous);
		//4.获取当前用户输入的发光值。
		CString text = DlgMultipleInput.get_luminous();
		m_multiple_fitting_list.InsertItem(luminous_count, _T(""));
		m_multiple_fitting_list.SetItemText(luminous_count, 0, text);
	}
}
/*
 * name:OnBnClickedDeleteButton
 * brief: “删除”右方list表格中某一条数据
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedDeleteButton()
{
	// TODO: Add your control notification handler code here
	//1.获取用户选中的数据
	//1.1获取当前选中数据的位置
	POSITION pos = m_multiple_fitting_list.GetFirstSelectedItemPosition();
	if (0 == pos)
	{
		MessageBox(_T("请选中期望删除的内容！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	const int item = m_multiple_fitting_list.GetNextSelectedItem(pos);
	//1.2获取右方list表格中输入的所有发光值的个数
	int luminous_count = 0;
	for (int i = 0; m_multiple_fitting_list.GetItemText(i, 0) != _T(""); i++)
	{
		luminous_count++;
	}
	if ((item < 0) || (item >= luminous_count))
	{
		MessageBox(_T("您选中的内容非法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	//2.从列表控件中删除相应的数据。
	m_multiple_fitting_list.DeleteItem(item);
}
/*
 * name:copy_list_data
 * brief: 复制右方list表格中多样本的浓度值到剪切板
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::copy_list_data()
{
	m_multiple_fitting_list.SetFocus();
	//1.打开剪切板
	if ((!OpenClipboard()) || (!EmptyClipboard()))
	{
		MessageBox(_T("打开剪切板失败！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}

	int cnt = m_multiple_fitting_list.GetItemCount();
	//std::vector<int> nPos;
	const BOOL is_CalculateConcentrationByTwo = m_is_calculateConcentration_by_two_box.GetCheck();
	CString strText;
	for (int i = 0; i < cnt; ++i)
	{
		CString text;
		if (is_CalculateConcentrationByTwo)
			text = m_multiple_fitting_list.GetItemText(i, 2);
		else
			text = m_multiple_fitting_list.GetItemText(i, 1);
		if (i == 0)
			strText = strText + text;
		else
			strText = strText + '\n' + text;
	}
	char* buffer;
	HGLOBAL hData = GlobalAlloc(GMEM_DDESHARE, strText.GetLength() + 1);
	buffer = (char*)GlobalLock(hData);
	memcpy(buffer, LPCSTR(strText), strText.GetLength());
	buffer[strText.GetLength()] = '\0';
	GlobalUnlock(hData);
	SetClipboardData(CF_TEXT, hData);
	CloseClipboard();
}
/*
 * name:OnBnClickedButtonCopy
 * brief: 复制list表格中多样本的浓度值到剪切板
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedButtonCopy()
{
	// TODO: Add your control notification handler code here
	copy_list_data();
}


/*
 * name:OnBnClickedInputLuminousbutton
 * brief: “复制”剪切板发光值到两点定标list表格
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedInputLuminousbutton()
{
	// TODO: Add your control notification handler code here
	if (!IsClipboardFormatAvailable(CF_TEXT))
		return;

	if (!OpenClipboard())
		return;
	HGLOBAL hmem = GetClipboardData(CF_TEXT);
	if (hmem == NULL)
	{
		CloseClipboard();
		return;
	}

	typedef  std::vector<CString> SVec;
	SVec vec;

	LPSTR pbuff = (LPSTR)GlobalLock(hmem);
	LPSTR pb = pbuff;
	while (*pbuff != _T('\0'))
	{
		++pbuff;
		if (*pbuff == _T('\n'))
		{
			vec.push_back(CString(pb, pbuff - pb));
			pb = pbuff + 1;
		}
	}
	GlobalUnlock(hmem);
	CloseClipboard();

	if (vec.empty())
		return;

	m_two_point_calibration_list.DeleteAllItems();

	for (int i = 0; i < vec.size(); ++i)
	{
		CString slums = vec[i];
		m_two_point_calibration_list.InsertItem(i, slums);
	}
}
/*
 * name:OnBnClickedClearButton
 * brief: “清空”2点定标list表格数据
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	m_two_point_calibration_list.DeleteAllItems();
}
/*
 * name:OnBnClickedCalculateConcentrationButton
 * brief: 由发光值“计算浓度”
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedCalculateConcentrationButton()
{
	// TODO: Add your control notification handler code here
	//1.检测输入的拟合数据数量是否合法。
	const unsigned int fitting_data_size = _fitting_data.size();
	if (6 != fitting_data_size)
	{
		MessageBox(_T("很抱歉，目前只支持六点定标，请输入六组数据，谢谢！"),
			_T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	//2.获取当前用户选择的定标信息，并且判断获取是否成功。
	//2-1.获取当前用户选择的定标类型，并且判断获取是否成功。
	int item = _calibration_type_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择定标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_calibration_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationType calibration_type =
		static_cast<CalibrationFactory::CalibrationType>(
			_calibration_type_combo_box.GetItemData(item));
	//2-2.获取当前用户选择的定标方法，并且判断获取是否成功。
	item = _fitting_method_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择定标方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_fitting_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationMethod calibration_method =
		static_cast<CalibrationFactory::CalibrationMethod>(
			_fitting_method_combo_box.GetItemData(item));
	//2-3.获取当前用户选择的实验方法，并且判断获取是否成功。
	item = _experiment_method_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择实验方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_experiment_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::ExperimentMethod experiment_method =
		static_cast<CalibrationFactory::ExperimentMethod>(
			_experiment_method_combo_box.GetItemData(item));
	//2-4.获取当前用户选择的坐标类型，并且判断获取是否成功。
	item = _coordinates_type_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择坐标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_coordinates_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CoordinatesType coordinates_type =
		static_cast<CalibrationFactory::CoordinatesType>(
			_coordinates_type_combo_box.GetItemData(item));
	//2-5.获取当前s0是否参与拟合。
	const BOOL is_s0_participation = _is_s0_participation_check_box.GetCheck();
	//3.计算浓度值，并写入两点定标list表格
	for (int i = 0; i < 2; i++)
	{
		//4.对输入数据进行拟合，并且判断拟合是否成功
		//4.1声明当前操作所需变量
		double concs_[100] = { 0.0 };
		double lums_[100] = { 0.0 };
		for (unsigned int j = 0; j != fitting_data_size; ++j)
		{
			concs_[j] = _fitting_data[j].get_x();
			lums_[j] = _fitting_data[j].get_y();
		}
		//5.获取当前用户输入的发光值
		CString luminous = m_two_point_calibration_list.GetItemText(i, 0);//获取第0列第i行的发光值
		if (_T("") == luminous)
		{
			MessageBox(_T("请输入发光值!"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}

		const double lum = static_cast<double>(atoi(luminous));
		double conc = 0.0;
		//6.计算浓度
		if (CalibrationFactory::calculate_concentration(
			calibration_type, calibration_method, experiment_method,
			coordinates_type, is_s0_participation, &_paras[0], _paras.size(), _xration, _xbase, _ybase, lum, conc) < 0)
		{
			MessageBox(_T("反算浓度失败"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		else
		{
			CString str_text;
			str_text.Format(_T("%.4lf"), conc);
			//7.2显示计算浓度。
			m_two_point_calibration_list.SetItemText(i, 1, str_text);
		}
	}
}

/*
 * name:OnBnClickedConcentrationRatioButton
 * brief: “计算浓度比”
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnBnClickedConcentrationRatioButton()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < 2; i++)
	{
		CString strConc = m_two_point_calibration_list.GetItemText(i, 2);
		if (_T("") == strConc)
		{
			MessageBox(_T("请选择测试点浓度"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}

	}
	m_two_fitting_data.clear();
	//1.定义浓度变量
	double calibrate_concs[2];//由发光值计算出的浓度，即2个校正品定标A、B
	double test_concs[2];//测试点浓度
	//CString strTest_concs[2]={""};//定标点浓度
	//2.计算两个定标品的浓度比
	for (int i = 0; i < 2; i++)
	{
		//2.1计算两个定标品的浓度比
		CString strCalibrate_concs = m_two_point_calibration_list.GetItemText(i, 1);//定标点浓度
		CString strTest_concs = "";
		if (m_two_point_calibration_list.GetItemText(i, 2) == "S0")
		{
			strTest_concs = _fitting_data_list.GetItemText(0, 0);//测试点浓度
		}
		else if (m_two_point_calibration_list.GetItemText(i, 2) == "S1")
		{
			strTest_concs = _fitting_data_list.GetItemText(1, 0);//测试点浓度
		}
		else if (m_two_point_calibration_list.GetItemText(i, 2) == "S2")
		{
			strTest_concs = _fitting_data_list.GetItemText(2, 0);//测试点浓度
		}
		else if (m_two_point_calibration_list.GetItemText(i, 2) == "S3")
		{
			strTest_concs = _fitting_data_list.GetItemText(3, 0);//测试点浓度
		}
		else if (m_two_point_calibration_list.GetItemText(i, 2) == "S4")
		{
			strTest_concs = _fitting_data_list.GetItemText(4, 0);//测试点浓度
		}
		else
		{
			strTest_concs = _fitting_data_list.GetItemText(5, 0);//测试点浓度
		}
		calibrate_concs[i] = atof(strCalibrate_concs);
		test_concs[i] = atof(strTest_concs);
		if (_T("") == strTest_concs)
		{
			MessageBox(_T("请选择测试点"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		if (_T("") == strCalibrate_concs)
		{
			MessageBox(_T("请计算出定标点的浓度值"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		m_concentration_ratio[i] = (double)(calibrate_concs[i] / test_concs[i]);//定标点与测试点的浓度比
		//2.2显示浓度比
		CString str_text;
		str_text.Format(_T("%.4lf"), m_concentration_ratio[i]);
		m_two_point_calibration_list.SetItemText(i, 3, str_text);
	}
	//3.计算新的发光值
	for (int j = 0; j < 6; j++)
	{
		double two_conc = test_concs[0];//测试点A的浓度
		double conc = atof(_fitting_data_list.GetItemText(j, 0));//六点定标时输入的浓度
		if (conc <= two_conc)
		{
			m_two_fitting_data.push_back(FittingData(conc, m_concentration_ratio[0] * atof(_fitting_data_list.GetItemText(j, 1))));
		}
		else
		{
			m_two_fitting_data.push_back(FittingData(conc, m_concentration_ratio[1] * atof(_fitting_data_list.GetItemText(j, 1))));
		}
	}
}
/**
* name: OnBnClickedFittingButton
* breif: 绘制2点定标曲线(此时六点定标的曲线不删除)
* param: --
* return: --
* author: ghm
*/
void CDlgMain::OnBnClickedFittingButton()
{
	// TODO: Add your control notification handler code here		
   //1.检测输入的拟合数据数量是否合法。
	const unsigned int fitting_data_size = _fitting_data.size();
	const unsigned int two_fitting_data_size = m_two_fitting_data.size();
	if ((6 != two_fitting_data_size) || (6 != two_fitting_data_size)) {
		MessageBox(_T("很抱歉，目前只支持六点定标，请输入六组数据，谢谢！"),
			_T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	//2.获取当前用户选择的定标信息，并且判断获取是否成功。
	//2-1.获取当前用户选择的定标类型，并且判断获取是否成功。
	int item = _calibration_type_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择定标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_calibration_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationType calibration_type =
		static_cast<CalibrationFactory::CalibrationType>(
			_calibration_type_combo_box.GetItemData(item));
	//2-2.获取当前用户选择的定标方法，并且判断获取是否成功。
	item = _fitting_method_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择定标方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_fitting_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationMethod calibration_method =
		static_cast<CalibrationFactory::CalibrationMethod>(
			_fitting_method_combo_box.GetItemData(item));
	//2-3.获取当前用户选择的实验方法，并且判断获取是否成功。
	item = _experiment_method_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择实验方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_experiment_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::ExperimentMethod experiment_method =
		static_cast<CalibrationFactory::ExperimentMethod>(
			_experiment_method_combo_box.GetItemData(item));
	//2-4.获取当前用户选择的坐标类型，并且判断获取是否成功。
	item = _coordinates_type_combo_box.GetCurSel();
	if (item < 0) {
		MessageBox(_T("请选择坐标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_coordinates_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CoordinatesType coordinates_type =
		static_cast<CalibrationFactory::CoordinatesType>(
			_coordinates_type_combo_box.GetItemData(item));
	//2-5.获取当前s0是否参与拟合。
	const BOOL is_s0_participation = _is_s0_participation_check_box.GetCheck();
	//3.对六点定标输入数据进行拟合，并且判断拟合是否成功。
	//3-1.声明当前操作所需变量。
	double concs[100] = { 0.0 };
	double lums[100] = { 0.0 };
	for (unsigned int i = 0; i != fitting_data_size; ++i) {
		concs[i] = _fitting_data[i].get_x();
		lums[i] = _fitting_data[i].get_y();
	}
	double a[10], R = 0.0, xbase = 0.0, ybase{}, xration{};
	//3-2.对当前输入数据进行拟合，并且判断拟合是否成功。
	if (CalibrationFactory::calibrate(calibration_type, calibration_method,
		experiment_method, coordinates_type, is_s0_participation, concs, lums,
		fitting_data_size, a, 5, R, xbase, ybase, xration) < 0) {
		MessageBox(_T("数据拟合失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}


	//3-4.显示拟合结果。
	CString text(_T(""));
	if (CalibrationFactory::CALIBRATION_METHOD_LINEAR == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nR2=%.6lf\r\nD=%.6lf"), a[0], a[1], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}
	else if (CalibrationFactory::CALIBRATION_METHOD_CUBIC_POLYNOMIAL == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nc=%.6lf\r\nd=%.6lf\r\nR2=%.6lf\r\nD=%.6lf"),
			a[0], a[1], a[2], a[3], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}
	else if (CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG4P == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nc=%.6lf\r\nd=%.6lf\r\nR2=%.6lf\r\nD=%.6lf"),
			a[0], a[1], a[2], a[3], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}
	else if (CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG5P == calibration_method) {
		text.Format(_T("a=%.6lf\r\nb=%.6lf\r\nc=%.6lf\r\nd=%.6lf\r\nR2=%.6lf\r\nD=%.6lf\r\nE=%.61f"),
			a[1], a[3], a[2], a[0], a[4], R, xbase);
		_fitting_result_edit.SetWindowText(text);
	}

	//3-5.保存当前拟合参数。
	int para_size{};
	switch (calibration_method)
	{
	case CalibrationFactory::CALIBRATION_METHOD_LINEAR:
		para_size = 2;
		break;
	case CalibrationFactory::CALIBRATION_METHOD_CUBIC_POLYNOMIAL:
	case CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG4P:
		para_size = 4;
		break;
	case CalibrationFactory::CALIBRATION_METHOD_LOGIT_LOG5P:
		para_size = 5;
		break;
	default:
	{assert(false); }
	}

	_paras.clear();
	for (int i = 0; i < para_size; ++i)
		_paras.push_back(a[i]);



	//4.对六点定标曲线进行拟合。
	//4-1.清除六点定标曲线、点集内容。
	_curve_chart->clear_points_of_curve();
	_curve_chart->clear_points_of_point_set();
	//4-2.计算横坐标浓度的显示范围。
	//4—2—1.声明当前操作所需变量
	double min_conc = _fitting_data[0].get_x();
	double max_conc = _fitting_data[fitting_data_size - 1].get_x();
	//4—2—1.对计算出的六点定标最值浓度进行坐标变换，并且判断变换是否成功。
	if ((CalibrationFactory::convert_x_y_coordinates(coordinates_type, min_conc) < 0) ||
		(CalibrationFactory::convert_x_y_coordinates(coordinates_type, max_conc) < 0)) {
		MessageBox(_T("对不起,六点定标坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	max_conc *= 1.05;
	//4-3.根据拟合的数据计算定标点上的浓度，并且判断计算是否成功。
	for (unsigned int i = 0; i != fitting_data_size; ++i) {
		//4-3-1.获取当前待拟合数据。
		double cal_conc = 0.0;
		for (unsigned int j = 0; j != fitting_data_size; ++j) {
			concs[j] = _fitting_data[j].get_x();
			lums[j] = _fitting_data[j].get_y();
		}
		//4-3-2.反算浓度，并且判断反算是否成功。
		if (CalibrationFactory::calculate_concentration(calibration_type, calibration_method,
			experiment_method, coordinates_type, is_s0_participation, a, para_size, _xration, _xbase, _ybase, lums[i], cal_conc) < 0) {
			MessageBox(_T("反算浓度失败，请重试！"), _T("警告"),
				MB_ICONWARNING | MB_OK);
			return;
		}

		//4-3-5.对计算出的浓度进行坐标变换，并且判断变换是否成功。
		if (CalibrationFactory::convert_x_y_coordinates(coordinates_type, cal_conc) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//4-3-6.利用当前计算浓度，更新浓度范围。
		if (cal_conc < min_conc) {
			min_conc = cal_conc;
		}
		if (cal_conc > max_conc) {
			max_conc = cal_conc;
		}
	}
	//4-4.计算y轴的范围。
	//4-4-1.声明当前操作所需变量
	double min_lum = _fitting_data[0].get_y();
	double max_lum = _fitting_data[fitting_data_size - 1].get_y();
	//4—4—2.对计算出的六点定标最值发光值进行坐标变换，并且判断变换是否成功。
	if ((CalibrationFactory::convert_x_y_coordinates(coordinates_type,
		_fitting_data[0].get_y(), min_lum) < 0) || (CalibrationFactory::
			convert_x_y_coordinates(coordinates_type, _fitting_data[0].
				get_y(), max_lum) < 0)) {
		MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	if (min_lum > max_lum) {
		const double temp = min_lum;
		min_lum = max_lum;
		max_lum = temp;
	}
	//4-5.计算纵坐标发光值的显示范围。
	//4—5—1.声明当前操作所需变量
	double conc = min_conc;
	double conc_span = abs(max_conc - min_conc) / 1000.0;
	while (conc <= max_conc) {
		double cal_lum = 0.0;
		//4—5—1—1.获取待拟合的六点定标数据
		for (unsigned int i = 0; i != fitting_data_size; ++i) {
			concs[i] = _fitting_data[i].get_x();
			lums[i] = _fitting_data[i].get_y();
		}
		double conc_t = conc;
		//4—5—1—2.对当前的浓度进行坐标转换
		if (CalibrationFactory::convert_to_x_y_coordinates(coordinates_type, conc_t) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//4—5—1—3.反算发光值，并且判断反算是否成功。
		if (CalibrationFactory::calculate_luminous(calibration_type, calibration_method,
			experiment_method, coordinates_type, is_s0_participation, a, para_size, _xration, _xbase, conc_t, cal_lum) < 0) {
			MessageBox(_T("反算浓度失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//4-5-1—4.对计算出的发光值进行坐标变换，并且判断变换是否成功。
		if (CalibrationFactory::convert_x_y_coordinates(
			coordinates_type, _fitting_data[0].get_y(), cal_lum) < 0) {
			MessageBox(_T("坐标转换失败失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//4-5-1—5.利用当前计算发光值，更新浓度范围。
		if (cal_lum < min_lum) {
			min_lum = cal_lum;
		}
		if (cal_lum > max_lum) {
			max_lum = cal_lum;
		}
		conc += conc_span;
	}
	max_lum *= 1.05;

	//8.绘制六点定标曲线
	//8-1.计算当前曲线上的点，用以形成曲线。
	//8-1-1.声明当前操作所需变量。
	conc = min_conc;
	conc_span = abs(max_conc - min_conc) / 1000.0;
	BOOL is_calculated = FALSE;
	//8-1-2.循环计算所有坐标点的浓度。
	while (conc <= max_conc) {
		//a.获取当前待拟合数据。
		double cal_lum = 0.0;
		for (unsigned int i = 0; i != fitting_data_size; ++i) {
			concs[i] = _fitting_data[i].get_x();
			lums[i] = _fitting_data[i].get_y();
		}
		//b.将当前浓度值转换为x-y类型坐标。
		double conc_t = conc;
		if (CalibrationFactory::convert_to_x_y_coordinates(coordinates_type, conc_t) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//c.计算发光值，并且判断计算是否成功。
		if (CalibrationFactory::calculate_luminous(calibration_type, calibration_method,
			experiment_method, coordinates_type, is_s0_participation, a, para_size, _xration, _xbase, conc_t, cal_lum) < 0) {
			MessageBox(_T("反算浓度失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//d.将计算出的发光值转换坐标系。
		if (CalibrationFactory::convert_x_y_coordinates(
			coordinates_type, _fitting_data[0].get_y(), cal_lum) < 0) {
			MessageBox(_T("反算浓度失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//e.添加点到六点定标曲线
		const int result = _curve_chart->add_point_to_curve(conc, cal_lum);
		if (result < 0) {
			if (-1 == result) {
				conc += conc_span;
				continue;
			}
			else {
				MessageBox(_T("向曲线中添加点失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
				return;
			}
		}
		//f.计算下一个拟合点。
		if (fabs(conc - max_conc) < 1.0E-20) {
			is_calculated = TRUE;
		}
		conc += conc_span;
		if ((conc > max_conc) && (FALSE == is_calculated)) {
			conc = max_conc;
			is_calculated = TRUE;
		}
	}
	//8-2.计算点集上的点，用于点集绘制。
	for (unsigned int i = 0; i < fitting_data_size; ++i) {
		//a.计算当前浓度坐标。
		double conc = _fitting_data[i].get_x();
		//b.对当前浓度坐标进行坐标转换。
		if (CalibrationFactory::convert_x_y_coordinates(coordinates_type, conc) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//c.计算当前发光值坐标
		double lum = _fitting_data[i].get_y();
		//d.对当前发光值坐标进行坐标转换。
		if (CalibrationFactory::convert_x_y_coordinates(
			coordinates_type, _fitting_data[0].get_y(), lum) < 0) {
			MessageBox(_T("对不起,坐标转换失败，请重试！"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//e.添加点到六点定标点集
		_curve_chart->add_point_to_point_set(conc, lum);
	}
	//9.绘制2点定标曲线
	//9-1.计算当前曲线上的点，用以形成曲线。
	//9-1-1.声明当前操作所需变量。
	_curve_chart->RedrawWindow();
}

/**
 * name: OnNMDblclkTwoPointCalibrationList
 * breif: 双击2点定标list列表响应函数，使其可选择。
 * param: --
 * return: --
 * author: ghm
 */
void CDlgMain::OnNMDblclkTwoPointCalibrationList(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//1.初始化下拉框
	m_TestPointCombo.InsertString(0, "S0");
	m_TestPointCombo.InsertString(1, "S1");
	m_TestPointCombo.InsertString(2, "S2");
	m_TestPointCombo.InsertString(3, "S3");
	m_TestPointCombo.InsertString(4, "S4");
	m_TestPointCombo.InsertString(5, "S5");

	if (_T("") == m_two_point_calibration_list.GetItemText(0, 0))
	{
		MessageBox(_T("请输入定标品的发光值！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//2..获取选中的行和列
	CRect rc;
	m_nRow = pNMListView->iItem;//获得选中的行   
	m_nCol = pNMListView->iSubItem;//获得选中列 
	//3.移动下拉框到list表格的坐标中
	if (m_nRow < 0)
	{
		return;
	}
	if (pNMListView->iSubItem == 2) //如果选择的是子项;  
	{
		//3.1移动下拉框并显示选择的内容到list
		m_TestPointCombo.SetParent(&m_two_point_calibration_list);//转换坐标为列表框中的坐标  	
		m_two_point_calibration_list.GetSubItemRect(m_nRow, m_nCol, LVIR_LABEL, rc);//获得子项的RECT；    
		m_TestPointCombo.MoveWindow(rc);//移动下拉框到RECT坐标的位置;   
		m_TestPointCombo.SetWindowText(m_multiple_fitting_list.GetItemText(m_nRow, m_nCol));//将该子项中的值放在ComboBox控件中；   
		m_TestPointCombo.ShowWindow(true);//显示ComboBox控件；       
	}
	*pResult = 0;
}
/**
* name: OnCbnKillfocusTestPointCombo
* breif: 下拉框失去焦点响应函数，并显示相应内容到2点定标list表格
* param: --
* return: --
* author: ghm
*/
void CDlgMain::OnCbnKillfocusTestPointCombo()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_TestPointCombo.GetCurSel();//获取选中的行
	CString strText;
	m_TestPointCombo.GetLBText(nIndex, strText);    //得到用户选择的的新的内容,并保存在strText中
	m_two_point_calibration_list.SetItemText(m_nRow, m_nCol, strText);   //设置编辑框的新内容
}
/**
* name: OnCbnSelchangeTestPointCombo
* breif: 下拉框值改变后响应函数，并显示相应内容到2点定标list表格
* param: --
* return: --
* author: ghm
*/
void CDlgMain::OnCbnSelchangeTestPointCombo()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_TestPointCombo.GetCurSel();//获取选中的行
	CString strText;
	m_TestPointCombo.GetLBText(nIndex, strText);    //得到用户选择的的新的内容,并保存在strText中
	m_two_point_calibration_list.SetItemText(m_nRow, m_nCol, strText);   //设置编辑框的新内容
	m_TestPointCombo.ShowWindow(false);
}
/*20170406
* name:OnBnClickedInversePasteButton
* brief: 粘贴剪切板浓度数据到右方list表格
* param: --
* return: --
* author: ghm
*/
void CDlgMain::OnBnClickedInversePasteButton()
{
	// TODO: Add your control notification handler code here
	//1.把剪切板数据根据excl格式换行
	//1.1.判断剪切板是否打开
	if (!IsClipboardFormatAvailable(CF_TEXT))
		return;

	if (!OpenClipboard())
		return;
	HGLOBAL hmem = GetClipboardData(CF_TEXT);
	if (hmem == NULL)
	{
		CloseClipboard();
		return;
	}

	typedef  std::vector<CString> SVec;
	SVec vec;
	//1.2.把剪切板数据根据excl格式进行存储
	LPSTR pbuff = (LPSTR)GlobalLock(hmem);
	LPSTR pb = pbuff;
	while (*pbuff != _T('\0'))
	{
		++pbuff;
		if (*pbuff == _T('\n'))
		{
			vec.push_back(CString(pb, pbuff - pb));
			pb = pbuff + 1;
		}
	}
	GlobalUnlock(hmem);
	CloseClipboard();
	//2.把剪切板数据复制到list表格
	//2.1.判断数组是否为空
	if (vec.empty())
		return;
	//2.1.清空表格内容
	m_multiple_fitting_list.DeleteAllItems();
	//2.1.显示浓度值
	for (int i = 0; i < vec.size(); ++i)
	{
		CString sconc = vec[i];
		m_multiple_fitting_list.InsertItem(i, "");
		m_multiple_fitting_list.SetItemText(i, 1, sconc);
	}
}
/**20170406
* name: OnBnClickedLumsButton
* brief: 用户点击“计算”按钮消息响应函数--反拟合发光值
* param: --
* return: --
* author: ghm
*/
void CDlgMain::OnBnClickedLumsButton()
{
	// TODO: Add your control notification handler code here
	//const BOOL is_CalculateConcentrationByTwo=m_is_calculateConcentration_by_two_box.GetCheck();
	VECFITDATA fitting_data;
	fitting_data.assign(_fitting_data.begin(), _fitting_data.end());

	//1.检测输入的拟合数据数量是否合法。
	const unsigned int fitting_data_size = fitting_data.size();
	//2.获取当前用户选择的定标信息，并且判断获取是否成功。
	//2-1.获取当前用户选择的定标类型，并且判断获取是否成功。
	int item = _calibration_type_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择定标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_calibration_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationType calibration_type =
		static_cast<CalibrationFactory::CalibrationType>(
			_calibration_type_combo_box.GetItemData(item));
	//2-2.获取当前用户选择的定标方法，并且判断获取是否成功。
	item = _fitting_method_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择定标方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_fitting_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CalibrationMethod calibration_method =
		static_cast<CalibrationFactory::CalibrationMethod>(
			_fitting_method_combo_box.GetItemData(item));
	//2-3.获取当前用户选择的实验方法，并且判断获取是否成功。
	item = _experiment_method_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择实验方法！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_experiment_method_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::ExperimentMethod experiment_method =
		static_cast<CalibrationFactory::ExperimentMethod>(
			_experiment_method_combo_box.GetItemData(item));
	//2-4.获取当前用户选择的坐标类型，并且判断获取是否成功。
	item = _coordinates_type_combo_box.GetCurSel();
	if (item < 0)
	{
		MessageBox(_T("请选择坐标类型！"), _T("警告"), MB_ICONWARNING | MB_OK);
		_coordinates_type_combo_box.SetFocus();
		return;
	}
	const CalibrationFactory::CoordinatesType coordinates_type =
		static_cast<CalibrationFactory::CoordinatesType>(
			_coordinates_type_combo_box.GetItemData(item));
	//2-5.获取当前s0是否参与拟合。
	const BOOL is_s0_participation = _is_s0_participation_check_box.GetCheck();
	//3.获取list表格中输入的所有浓度值的个数
	int conc_count = 0;//获取左上方list表格中输入的所有发光值的个数
	for (int i = 0; m_multiple_fitting_list.GetItemText(i, 1) != _T(""); i++)
	{
		conc_count++;
	}
	for (int i = 0; i < conc_count; i++)
	{
		//4.对输入数据进行拟合，并且判断拟合是否成功
		//4.1声明当前操作所需变量
		double concs_[100] = { 0.0 };
		double lums_[100] = { 0.0 };
		for (unsigned int j = 0; j != fitting_data_size; ++j)
		{
			concs_[j] = fitting_data[j].get_x();
			lums_[j] = fitting_data[j].get_y();
		}
		//5.获取当前用户输入的浓度值
		CString conc = m_multiple_fitting_list.GetItemText(i, 1);//获取第1列第i行的浓度值
		if (_T("") == conc)
		{
			MessageBox(_T("请输入浓度值!"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}

		const double iconc = atof(conc);
		double lums = 0.0;
		//6.计算发光值
		if (CalibrationFactory::calculate_luminous(
			calibration_type, calibration_method, experiment_method,
			coordinates_type, is_s0_participation, &_paras[0], _paras.size(), _xration, _xbase,
			iconc, lums) < 0)
		{
			MessageBox(_T("计算发光值失败"), _T("警告"), MB_ICONWARNING | MB_OK);
			return;
		}
		//7.显示发光值
		CString str_text;
		str_text.Format(_T("%.3f"), lums);
		m_multiple_fitting_list.SetItemText(i, 0, str_text);
	}
}
/*20170406
* name:OnBnClickedInverseCopyButton
* brief: 复制右方list表格中多样本的发光值到剪切板
* param: --
* return: --
* author: ghm
*/
void CDlgMain::OnBnClickedInverseCopyButton()
{
	m_multiple_fitting_list.SetFocus();
	// TODO: Add your control notification handler code here
	//1.打开剪切板
	//1.1.判断打开剪切板是否成功
	if ((!OpenClipboard()) || (!EmptyClipboard()))
	{
		MessageBox(_T("打开剪切板失败！"), _T("警告"), MB_ICONWARNING | MB_OK);
		return;
	}
	int cnt = m_multiple_fitting_list.GetItemCount();
	CString strText;
	for (int i = 0; i < cnt; ++i)
	{
		CString text;
		text = m_multiple_fitting_list.GetItemText(i, 0);
		if (i == 0)
			strText = strText + text;
		else
			strText = strText + '\n' + text;
	}
	char* buffer;
	HGLOBAL hData = GlobalAlloc(GMEM_DDESHARE, strText.GetLength() + 1);
	buffer = (char*)GlobalLock(hData);
	memcpy(buffer, LPCSTR(strText), strText.GetLength());
	buffer[strText.GetLength()] = '\0';
	GlobalUnlock(hData);
	SetClipboardData(CF_TEXT, hData);
	//3.关闭剪切板
	CloseClipboard();
}
