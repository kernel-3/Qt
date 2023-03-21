#include "reagent.h"
#include "ui_reagentw.h"
#pragma execution_character_set("utf-8")

Reagent::Reagent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Reagent)
{
    ui->setupUi(this);
    setWindowTitle("试剂模块");
    initReagentInfoUI();
    initReagentStatusUI();
    initSlotAndSingal();
}

Reagent::~Reagent()
{
    delete ui;
}

void Reagent::slotManualRegistration()
{
    //手动注册试剂或底物时设备必须在空闲时使用，否则提示设备正在运行
    QDialog  reaRegistertionDlg ;
    reaRegistertionDlg.setWindowTitle("手动注册条码");
    reaRegistertionDlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    reaRegistertionDlg.setMinimumWidth(500);
    reaRegistertionDlg.setMinimumHeight(300);
    QLabel barCodeName(&reaRegistertionDlg);
    barCodeName.setText("BarCode");
    barCodeName.setStyleSheet("QLabel{font-family:'宋体';font-size:20px;color:black;}");
    barCodeName.move(140, 105);
    barCodeName.show();
    QLineEdit barCodeNum(&reaRegistertionDlg);
    barCodeNum.move(220, 105);
    barCodeNum.show();
    QPushButton btnCannel(&reaRegistertionDlg);
	btnCannel.setText("取消");
	btnCannel.move(150, 180);
	btnCannel.show();
    QPushButton btnOk(&reaRegistertionDlg);
    btnOk.setText("确定");
    btnOk.move(280, 180);
	btnOk.show();  
    connect(&btnCannel, &QPushButton::clicked, this, [this,&reaRegistertionDlg] {
       reaRegistertionDlg.close() ;
	});
    connect(&btnOk, &QPushButton::clicked, &reaRegistertionDlg, [this] {
        slotVerifyBarCodeWhetherLegal();
    });
	reaRegistertionDlg.exec();
}
 
void Reagent::slotDeleteReagentInfo()
{
    //删除试剂或底物时设备必须是空闲状态，否则提示设备正在运行
	if (QMessageBox::question(this, tr("问题"),
		tr("是否确定要删除？"),
		tr("取消"),
		tr("确定")))
    {
       //系统将删除指定位置上的试剂或底物信息
        int oo = 11;
    }
}

void Reagent::slotReagentDiskScanning()
{
	//QDialog  *reaDiskScanningDlg = new QDialog(this);
 //   reaDiskScanningDlg->setWindowTitle("试剂盘扫描");
 //   reaDiskScanningDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
 //   reaDiskScanningDlg->setMinimumWidth(500);
 //   reaDiskScanningDlg->setMinimumHeight(300);

	//QTableView *reaDislPosition = new QTableView(reaDiskScanningDlg);

 //   reaDiskScanningDlg.exec();
}

void Reagent::slotReagentDiskRoation()
{
}

void Reagent::slotVerifyBarCodeWhetherLegal()
{
	QMessageBox::warning(this, tr("警告"), tr("底物或试剂条码非法警告！"), tr("确定"));

}

void Reagent::initReagentInfoUI()
{
    ui->reaInfoTable->setMinimumWidth(1003);
    ui->reaInfoTable->horizontalHeader()->setVisible(false);
    ui->reaInfoTable->verticalHeader()->setVisible(false);
    ui->reaInfoTable->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    ui->reaInfoTable->setColumnCount(10);
    ui->reaInfoTable->setRowCount(1);
    ui->reaInfoTable->setItem(0, 0, new QTableWidgetItem("试剂盘位置号"));
    ui->reaInfoTable->setItem(0, 1, new QTableWidgetItem("项目名称"));
    ui->reaInfoTable->setItem(0, 2, new QTableWidgetItem("项目有效次数"));
    ui->reaInfoTable->setItem(0, 3, new QTableWidgetItem("试剂类型"));
    ui->reaInfoTable->setItem(0, 4, new QTableWidgetItem("试剂编号"));
    ui->reaInfoTable->setItem(0, 5, new QTableWidgetItem("试剂批号"));
    ui->reaInfoTable->setItem(0, 6, new QTableWidgetItem("试剂序列号"));
    ui->reaInfoTable->setItem(0, 7, new QTableWidgetItem("项目名称"));
    ui->reaInfoTable->setItem(0, 8, new QTableWidgetItem("过期日期"));
    ui->reaInfoTable->setItem(0, 9, new QTableWidgetItem("试剂瓶规格"));

}

void Reagent::initReagentStatusUI()
{
    ui->selectSection->setMaximumWidth(202);
	ui->selectSection->horizontalHeader()->setVisible(false);
	ui->selectSection->verticalHeader()->setVisible(false);
    ui->selectSection->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    ui->selectSection->setColumnCount(2);
	ui->selectSection->setRowCount(1);
	ui->selectSection->setItem(0, 0, new QTableWidgetItem("项目名称"));
	ui->selectSection->setItem(0, 1, new QTableWidgetItem("项目有效次数"));
    
	ui->displaySection->horizontalHeader()->setVisible(false);
	ui->displaySection->verticalHeader()->setVisible(false);
    ui->displaySection->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
	ui->displaySection->setColumnCount(5);
    ui->displaySection->setRowCount(1);
	ui->displaySection->setItem(0, 0, new QTableWidgetItem("模块名称"));
	ui->displaySection->setItem(0, 1, new QTableWidgetItem("试剂类型"));
	ui->displaySection->setItem(0, 2, new QTableWidgetItem("试剂位置"));
	ui->displaySection->setItem(0, 3, new QTableWidgetItem("试剂剩余有效次数"));
	ui->displaySection->setColumnWidth(3, 150);
	ui->displaySection->setItem(0, 4, new QTableWidgetItem("过期日期"));
}

void Reagent::initSlotAndSingal()
{
    connect(ui->manualRegistration, &QPushButton::clicked, this, &Reagent::slotManualRegistration);
    connect(ui->deleteReagentInfo, &QPushButton::clicked, this, &Reagent::slotDeleteReagentInfo);
    connect(ui->reagentDiskScanning, &QPushButton::clicked, this, &Reagent::slotReagentDiskScanning);
    connect(ui->reagentDIskRoation, &QPushButton::clicked, this, &Reagent::slotReagentDiskRoation);
}

