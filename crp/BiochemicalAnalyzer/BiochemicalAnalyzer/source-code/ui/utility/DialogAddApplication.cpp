// source-code/ui/utility/DialogAddApplication.cpp : implementation file
//

#include"stdafx.h"
#include"DialogAddApplication.h"
#include"afxdialogex.h"
#include"../../global/Theme.h"
#include"../common/DialogMessageBox.h"
#include"../common/DialogItemAndProfileKey.h"
#include"../common/DialogItemAndProfileKeys.h"
#include"../../../../../include/mfctoolkit/layout/MtLayoutRect.h"
#include"../../../../../include/mfctoolkit/control/MtImageEdit.h"
#include"../../../../../include/mfctoolkit/control/MtImageStatic.h"
#include"../../../../../include/mfctoolkit/control/MtImageButton.h"
#include"../../../../../include/mfctoolkit/layout/MtHorizonLayout.h"
#include"../../../../../include/mfctoolkit/layout/MtVerticalLayout.h"
#include"../../../../../include/mfctoolkit/tool/MtCharacterSet.h"
#include"../UiCustom.h"
#include"../../data/utility/Application.h"
#include"../../data/utility/Applications.h"
#include"../../data/common/Item.h"
#include"../../data/utility/AnalyzeApplication.h"
#include"../../global/Database.h"
#include"../../global/DatabaseManager.h"
#include"../../../../../include/mfctoolkit/control/MtStrictEdit.h"
#include"../../data/utility/CalibrationApplication.h"
#include"../../data/utility/RangeApplication.h"
#include"../../data/utility/StandardApplication.h"
#include"../../data/common/Items.h"
#include"../../data/common/Module.h"
#include"../../data/common/SpecimenType.h"
#include"../../data/common/Modules.h"
#include"../../data/common/SpecimenTypes.h"
#include"../../data/utility/ApplicationParameter.h"
#include"../../data/utility/ApplicationParameters.h"
#include<vector>

//DialogAddApplication dialog

IMPLEMENT_DYNAMIC(DialogAddApplication,DialogModalBase)

/**
 * name: DialogAddApplication
 * breif: ���캯����
 * param: pParent - ָ�򸸴���ָ�롣
 * return: --
 */
DialogAddApplication::DialogAddApplication(CWnd *pParent/*=NULL*/)
	:DialogModalBase(DialogAddApplication::IDD,pParent)
	,_module_id(0)
	,_specimen_type_id(0)
	,_item_id(0)
	,_no_static(new MtImageStatic)
	,_test_name_static(new MtImageStatic)
	,_app_code_static(new MtImageStatic)
	,_no_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_test_name_edit(new MtImageEdit)
	,_app_code_edit(new MtStrictEdit(MtStrictEdit::TYPE_NUMBER))
	,_child_dialog(new DialogItemAndProfileKeys(1))
	,_ok_button(new MtImageButton)
	,_cancel_button(new MtImageButton)
	,_child_layout_1(new MtHorizonLayout)
	,_child_layout_2(new MtHorizonLayout)
	,_child_layout_3(new MtHorizonLayout)
	,_child_layout_4(new MtHorizonLayout)
	,_main_layout(new MtVerticalLayout){
}

/**
 * name: ~DialogAddApplication
 * brief: ����������
 * param: --
 * return: --
 */
DialogAddApplication::~DialogAddApplication(){
	delete _main_layout;
	delete _child_layout_1;
	delete _child_layout_2;
	delete _child_layout_3;
	delete _child_layout_4;
	delete _no_static;
	delete _test_name_static;
	delete _app_code_static;
	delete _no_edit;
	delete _test_name_edit;
	delete _app_code_edit;
	delete _child_dialog;
	delete _ok_button;
	delete _cancel_button;
}

/**
 * name: get_module_id
 * breif: ��ȡģ���ʶ��
 * param: --
 * return: ����ģ���ʶ��
 */
int DialogAddApplication::get_module_id() const{
	return(_module_id);
}

/**
 * name: get_specimen_type_id
 * breif: ��ȡ�������ͱ�ʶ��
 * param: --
 * return: �����������ͱ�ʶ��
 */
int DialogAddApplication::get_specimen_type_id() const{
	return(_specimen_type_id);
}

/**
 * name: get_item_id
 * brief: ��ȡ��Ŀ��ʶ��
 * param: --
 * return: ������Ŀ��ʶ��
 */
int DialogAddApplication::get_item_id() const{
	return(_item_id);
}

/**
 * name: DoDataExchange
 * breif: ֧��DDX/DDV��
 * param: pDX -
 * return: --
 */
void DialogAddApplication::DoDataExchange(CDataExchange *pDX){
	DialogModalBase::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_STATIC_NO,*_no_static);
	DDX_Control(pDX,IDC_STATIC_TEST_NAME,*_test_name_static);
	DDX_Control(pDX,IDC_STATIC_APP_CODE,*_app_code_static);
	DDX_Control(pDX,IDC_EDIT_NO,*_no_edit);
	DDX_Control(pDX,IDC_EDIT_TEST_NAME,*_test_name_edit);
	DDX_Control(pDX,IDC_EDIT_APP_CODE,*_app_code_edit);
	DDX_Control(pDX,IDC_BUTTON_OK,*_ok_button);
	DDX_Control(pDX,IDC_BUTTON_CANCEL,*_cancel_button);
}

/**
 * name: OnInitDialog
 * breif: �Ի����ʼ�����⺯����
 * param: --
 * return: �˺���һֱ����TRUE��
 */
BOOL DialogAddApplication::OnInitDialog(){
	DialogModalBase::OnInitDialog();
	//TODO:Add extra initialization here
	/////////////////////////////////////////////////////////////////
	//1.��ʼ����ǰ�Ի��򴰿ڡ�
	init_window();
	//2.��ʼ����ǰ�Ի����пؼ���
	init_controls();
	/////////////////////////////////////////////////////////////////
	return(TRUE);//return TRUE unless you set the focus to a control
	//EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogAddApplication,DialogModalBase)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_ITEM_OR_PROFILE_BUTTON_CLICKED,&DialogAddApplication::OnItemOrProfileButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_OK,&DialogAddApplication::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL,&DialogAddApplication::OnBnClickedButtonCancel)
END_MESSAGE_MAP()

//DialogAddApplication message handlers

/**
 * name: OnSize
 * brief: �Ի���ߴ������Ϣ��Ӧ�������˴�����
 *        ���¶Ի����в�����Ϣ��
 * param: nType - ָ�����µ����ߴ�ʱ��������͡�
 *        cx - ��ǰ�Ի���ͻ�����ȡ�
 *        cy - ��ǰ�Ի���ͻ����߶ȡ�
 * return: --
 */
void DialogAddApplication::OnSize(UINT nType,int cx,int cy){
	DialogModalBase::OnSize(nType,cx,cy);
	//TODO: Add your message handler code here
	//1.������ǰ���ֳߴ硣
	_main_layout->resize(cx,cy);
}

/**
 * name: OnDestroy
 * breif: �Ի���������Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAddApplication::OnDestroy(){
	DialogModalBase::OnDestroy();
	//TODO: Add your message handler code here
	//1.�����ǰ�ӶԻ����Ѿ���������������ٲ�����
	if(0!=_child_dialog->GetSafeHwnd()){
		_child_dialog->DestroyWindow();
	}
}

/**
 * name: OnItemOrProfileButtonClicked
 * brief: �û������Ŀ����ϰ�ť��Ϣ��Ӧ������
 * param: wParam - �������ͣ�1.��Ŀ 2.��ϣ���
 *        lParam - ������š�
 * return: �˺���һֱ�����㡣
 */
LRESULT DialogAddApplication::OnItemOrProfileButtonClicked(WPARAM wParam,LPARAM lParam){
	//1.�����ǰ����Ϊ��Ŀ������
	if(1==static_cast<int>(wParam)){
		CString item_no(_T(""));
		item_no.Format(_T("%d"),static_cast<int>(lParam));
		_no_edit->SetWindowText(item_no);
	}
	//2.�����ǰ����Ϊ����������
	else{
		//��ʱʲôҲ������
	}
	//3.�������е��ˣ�ֱ�ӷ����㡣
	return(0);
}

/**
 * name: OnBnClickedButtonOk
 * brief: �û������ȷ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAddApplication::OnBnClickedButtonOk(){
	//TODO: Add your control notification handler code here
	//1.���塣
	typedef std::shared_ptr<Item> PtrToItem;
	typedef std::shared_ptr<ApplicationParameter> PtrToParameter;
	typedef std::vector<PtrToParameter> Parameters;
	//2.����������Ŀ����Ƿ�Ϸ���
	//2-1.��ȡ��ǰ�������Ŀ��š�
	CString text(_T(""));
	_no_edit->GetWindowText(text);
	//2-2.����������Ŀ���Ϊ�գ�����ʾ�����ء�
	Theme *theme=Theme::instance();
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING151),this);
		_no_edit->SetFocus();
		return;
	}
	//2-3.��⵱ǰ�������Ŀ����Ƿ��ظ���
	Items *items=Items::instance();
	int temp=MtCharacterSet::to_integer(text);
	if(items->is_no_existed(temp)>=0){
		WarningMessageBox(theme->get_string(IDS_STRING160),this);
		_no_edit->SetFocus();
		return;
	}
	//2-4.��¼�������Ŀ��š�
	PtrToItem item(new Item);
	if(!static_cast<bool>(item)){
		WarningMessageBox(theme->get_string(IDS_STRING157),this);
		return;
	}
	item->set_no(temp);
	//3.�ж��������Ŀ�����Ƿ�Ϸ���
	//3-1.��ȡ�������Ŀ���ơ�
	_test_name_edit->GetWindowText(text);
	//��Ŀ�����Ƿ�Ϊ�ս��ں����жϡ�
	//3-2.��¼�������Ŀ���ơ�
	item->set_name(text);
	item->set_alias(text);//����Ĭ������Ŀ������ͬ��
	//4.����������Ŀ��ʶ�Ƿ�Ϸ���
	//4-1.��ȡ�������Ŀ��ʶ��
	_app_code_edit->GetWindowText(text);
	//4-2.����������Ŀ��ʶΪ�գ�����ʾ�����ء�
	if(_T("")==text){
		WarningMessageBox(theme->get_string(IDS_STRING153),this);
		_app_code_edit->SetFocus();
		return;
	}
	//4-3.��⵱ǰ�������Ŀ��ʶ�Ƿ��ظ���
	temp=MtCharacterSet::to_integer(text);
	if(items->is_id_existed(temp)>=0){
		WarningMessageBox(theme->get_string(IDS_STRING155),this);
		_app_code_edit->SetFocus();
		return;
	}
	//4-4.��¼�������Ŀ��ʶ��
	item->set_id(temp);
	//5.������Ŀ��Ĭ��״̬��
	item->set_status(Item::STATUS_NORMAL);//��ĿĬ��״̬Ϊ��ͨ״̬��
	//6.����û��������Ŀ��Ϣ�Ƿ�Ϸ���������Ϸ�����ʾ�û�����ֱ�ӷ��ء�
	//6-1.����������Ŀ��Ϣ�Ƿ�Ϸ���
	int result=item->is_valid(&text);
	//6-2.����������Ŀ��ʶ���Ϸ���
	if(-1==result){
		WarningMessageBox(text,this);
		_app_code_edit->SetFocus();
		return;
	}
	//6-3.����������Ŀ��Ų��Ϸ���
	else if(-2==result){
		WarningMessageBox(text,this);
		_no_edit->SetFocus();
		return;
	}
	//6-4.����������Ŀ���Ʋ��Ϸ���
	else if(-3==result){
		WarningMessageBox(text,this);
		_test_name_edit->SetFocus();
		return;
	}
	//6-5.�������δ֪ԭ�򲻺Ϸ���
	else if(result<0){
		ErrorMessageBox(theme->get_string(IDS_STRING152),this);
		_test_name_edit->SetFocus();
		return;
	}
	//7.ѯ���û��Ƿ�ȷ�ϱ��浱ǰ��Ŀ��
	if(IDNO==QuestionMessageBox(theme->get_string(
		IDS_STRING164),this)){
		return;
	}
	//8.�����û��������Ŀ��Ϣ����Ϊ��Ŀ����Ĭ�ϵ���Ŀ��������������Щ������
	//8-1.��ȡĿ�����ݿ����ʵ��ָ�롣
	Database *database=(DatabaseManager::instance())->
		get_database(DatabaseManager::DATABASE_NAME_MAIN);
	//8-2.����Ŀ�����ݿ⴦�����񣬲����ж������Ƿ�ɹ���
	if(database->begin_trans()<0){
		WarningMessageBox(theme->get_string(IDS_STRING492),this);
		return;
	}
	//8-3.����Ŀ��Ϣ�ύ�����ݿ��У������ж��ύ�Ƿ�ɹ���
	if(item->commit(1,(*database))<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING492),this);
		return;
	}
	//8-4.Ϊ��ǰ��Ŀ����Ĭ�ϲ���������Ĭ�ϲ����ύ�����ݿ��С�
	//8-4-1.��ȡ��ǰϵͳ��ģ�������Լ���������������
	const unsigned int module_count=Modules::instance()->get_count();
	const unsigned int specimen_type_count=SpecimenTypes::instance()->get_count();
	if((module_count<=0)||(specimen_type_count<=0)){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING490),this);
		return;
	}
	//8-4-2.Ϊ��Ŀ����Ĭ�ϲ���������Ĭ�ϲ����ύ�����ݿ��С�
	//8-4-2-1.���������洢������
	Parameters parameters;
	//8-4-2-2.����Ϊ��Ŀ����Ĭ�ϲ������������ύ�����ݿ��У������浽�����С�
	for(unsigned int m=0;m!=module_count;++m){
		//a.��ȡ��ǰ��ģ���ʶ��
		const int module_id=((Modules::instance())->get_by_index(m))->get_id();
		//b.�����������ͣ�Ϊ��Ŀ������Ӧ��Ĭ�ϲ�����
		for(unsigned int s=0;s!=specimen_type_count;++s){
			//b-1.��ȡ��ǰ�������ͱ�ʶ��
			const int specimen_type_id=((SpecimenTypes::instance())->
				get_by_index(s))->get_id();
			//b-2.����һ��Ĭ�ϲ�����
			PtrToParameter parameter(new ApplicationParameter(
				module_id,specimen_type_id,item->get_id()));
			//b-3.�ж�Ĭ�ϲ��������Ƿ�Ϸ���
			if(!static_cast<bool>(parameter)){
				database->rollback_trans();
				WarningMessageBox(theme->get_string(IDS_STRING491),this);
				return;
			}
			//b-4.��Ĭ�ϲ�������ΪĬ��ֵ��
			parameter->reset_default_value(item->get_no());
			//b-5.�����ݿ��ύĬ�ϲ����������ж��ύ�Ƿ�ɹ���
			if(parameter->commit(1,*database,FALSE)<0){
				database->rollback_trans();
				WarningMessageBox(theme->get_string(IDS_STRING492),this);
				return;
			}
			//b-5.��Ĭ�ϲ������浽�����С�
			parameters.push_back(parameter);
		}
	}
	//8-4-2-3.�ύ���ݿ�����,�����ж��ύ�Ƿ�ɹ���
	if(database->commit_trans()<0){
		database->rollback_trans();
		WarningMessageBox(theme->get_string(IDS_STRING492),this);
		return;
	}
	//8-5.�����û��������Ŀ�Լ���Ŀ������Ϣ��
	//8-5-1.������Ŀ��Ϣ��
	if((Items::instance())->add(item)<0){
		ErrorMessageBox(theme->get_string(IDS_STRING493),this);
		return;
	}
	//8-5-2.������Ŀ������Ϣ��
	for(unsigned int index=0;index!=parameters.size();++index){
		if((ApplicationParameters::instance())->add(parameters[index])<0){
			ErrorMessageBox(theme->get_string(IDS_STRING493),this);
			return;
		}
	}
	//9.����ģ���ʶ���������ͱ�ʶ����Ŀ��ʶ��
	_module_id=((Modules::instance())->get_by_index(0))->get_id();
	_specimen_type_id=((SpecimenTypes::instance())->
		get_by_index(0))->get_id();
	_item_id=item->get_id();
	//10.�������е��������˳���ǰ�Ի���
	EndDialog(IDOK);
}

/**
 * name: OnBnClickedButtonCancel
 * brief: �û������ȡ������ť��Ϣ��Ӧ������
 * param: --
 * return: --
 */
void DialogAddApplication::OnBnClickedButtonCancel(){
	//TODO: Add your control notification handler code here
	EndDialog(IDCANCEL);
}

/**
 * name: init_window
 * brief: ��ʼ����ǰ�Ի��򴰿ڡ�
 * param: --
 * return: --
 */
void DialogAddApplication::init_window(){
	//1.������ʼ����ǰ�������������
	Theme *theme=Theme::instance();
	//2.���õ�ǰ�Ի��򴰿ڱ��⡣
	SetWindowText(theme->get_string(IDS_STRING148));
}

/**
 * name: init_controls
 * brief: ��ʼ�������пؼ���
 * param: --
 * return: --
 */
void DialogAddApplication::init_controls(){
	//1.������ʼ����ǰ�������������
	CRect rect;
	GetClientRect(rect);
	Theme *theme=Theme::instance();
	//2.��ʼ����ǰ�Ի����пؼ���
	//2-1.��ʼ����̬�ı���
	_no_static->set_text_color(255,50,50,50);
	_no_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_test_name_static->set_text_color(255,50,50,50);
	_test_name_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	_app_code_static->set_text_color(255,50,50,50);
	_app_code_static->set_text_alignment(
		MtImageStatic::ALIGNMENT_LEFT|MtImageStatic::ALIGNMENT_VCENTER);
	//2-2.��ʼ���ı��༭��	
	_no_edit->set_text_color(50,50,50);
	_no_edit->load_background_image(theme->get_image(29),1,3);
	_no_edit->set_background_image_stretching_factors(5,5,5,5);
	_no_edit->EnableWindow(FALSE);
	_no_edit->SetLimitText(3);
	_test_name_edit->set_text_color(50,50,50);
	_test_name_edit->load_background_image(theme->get_image(29),1,3);
	_test_name_edit->set_background_image_stretching_factors(5,5,5,5);
	_app_code_edit->set_text_color(50,50,50);
	_app_code_edit->load_background_image(theme->get_image(29),1,3);
	_app_code_edit->set_background_image_stretching_factors(5,5,5,5);
	CString text(_T(""));
	text.Format(_T("%d"),(Items::instance())->assign_id());
	_app_code_edit->SetWindowText(text);
	_app_code_edit->SetLimitText(3);
	//2-3.��ʼ���ӶԻ���
	_child_dialog->Create(DialogItemAndProfileKeys::IDD,this);
	//2-4.��ʼ����ť��
	_ok_button->set_text_color(255,50,50,50);
	_ok_button->load_background_image(theme->get_image(32),1,4);
	_ok_button->set_background_image_stretching_factors(5,5,5,5);
	_cancel_button->set_text_color(255,50,50,50);
	_cancel_button->load_background_image(theme->get_image(32),1,4);
	_cancel_button->set_background_image_stretching_factors(5,5,5,5);
	//3.��ʼ���Ի����в��֡�
	//3-1.��ʼ���Ӳ���1��
	_child_layout_1->add_fixed_window(_no_static,100);
	_child_layout_1->add_fixed_window(_no_edit,50);
	//3-2.��ʼ���Ӳ���2��
	_child_layout_2->add_fixed_window(_test_name_static,100);
	_child_layout_2->add_fixed_window(_test_name_edit,150);
	//3-3.��ʼ���Ӳ���3��
	_child_layout_3->add_fixed_window(_app_code_static,100);
	_child_layout_3->add_fixed_window(_app_code_edit,50);
	//3-4.��ʼ���Ӳ���4��
	_child_layout_4->add_fixed_window(_ok_button,200);
	_child_layout_4->add_stretch(1);
	_child_layout_4->add_fixed_window(_cancel_button,200);
	_child_layout_4->add_stretch(1);
	//3-5.��ʼ�����֡�
	_main_layout->set_margin(BORDER_SIZE+5,TITLE_SIZE+5,BORDER_SIZE+5,BORDER_SIZE+5);
	_main_layout->add_fixed_layout(_child_layout_1,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_2,24);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_3,24);
	_main_layout->add_spacing(5);
	_main_layout->add_window(_child_dialog,1);
	_main_layout->add_spacing(5);
	_main_layout->add_fixed_layout(_child_layout_4,40);
	//4.���õ�ǰ���ֳߴ硣
	_main_layout->resize(rect.Width(),rect.Height());
	//5.��ʾ��ǰ�ӶԻ���
	_child_dialog->ShowWindow(SW_SHOW);
}