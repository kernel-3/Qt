#include "reagentdiskscanningdialog.h"
#include "ui_reagentdiskscanningdialog.h"
#pragma execution_character_set("utf-8")

ReagentDiskScanningDialog::ReagentDiskScanningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReagentDiskScanningDialog)
{
    ui->setupUi(this);
	setWindowModality(Qt::ApplicationModal);   
	setAttribute(Qt::WA_ShowModal, true); 
	initUI();
	initSlotAndSignal();
}

ReagentDiskScanningDialog::~ReagentDiskScanningDialog()
{
    delete ui;
}

void ReagentDiskScanningDialog::slotSelectAll()
{
	//将所有的复选框勾选上
	for (auto vec:checkBoxVec)
	{
		vec->setChecked(true);
	}
}

void ReagentDiskScanningDialog::slotScan()
{
	//从集合中找到勾选的复选框进行扫描
	for (auto vec : checkBoxVec)
	{
		if (vec->checkState()== Qt::Checked)
		{
			//开始扫描
			//在扫描过程中，对话框中所有按钮均为失效状态
			//如果扫描失败，系统将提示用户试剂盘扫描失败
		}
		
	}
}

void ReagentDiskScanningDialog::slotExit()
{
	this->close();
}

void ReagentDiskScanningDialog::initSlotAndSignal()
{
	connect(ui->btnSelectAll, &QPushButton::clicked, this, &ReagentDiskScanningDialog::slotSelectAll);
	connect(ui->btnScan, &QPushButton::clicked, this, &ReagentDiskScanningDialog::slotScan);
	connect(ui->btnExit, &QPushButton::clicked, this, &ReagentDiskScanningDialog::slotExit);
}

void ReagentDiskScanningDialog::initUI()
{
	ui->ReaDiskScanningView->horizontalHeader()->setVisible(false);
	ui->ReaDiskScanningView->verticalHeader()->setVisible(false);
	ui->ReaDiskScanningView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->ReaDiskScanningView->setColumnCount(2);
	ui->ReaDiskScanningView->setColumnWidth(0, 30);
	ui->ReaDiskScanningView->setColumnWidth(1, 321);
	ui->ReaDiskScanningView->setRowCount(2);
	ui->ReaDiskScanningView->setItem(0, 0, new QTableWidgetItem(""));
	ui->ReaDiskScanningView->setItem(0, 1, new QTableWidgetItem("试剂盘位置号"));
	ui->ReaDiskScanningView->item(0, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	QCheckBox* checkBox = new QCheckBox();
	QWidget* boxWidget  = new QWidget(this);
	QHBoxLayout* hBox = new QHBoxLayout();
	checkBox->setStyleSheet("QCheckBox::indicator:checked {image: url(../reagentDemo/right.png);}"
		"QCheckBox::indicator{width:25px;height:25px}"
		);
	checkBoxVec.append(checkBox);
	hBox->addWidget(checkBox);
	hBox->setMargin(0);
	hBox->setAlignment(checkBox, Qt::AlignCenter);
	boxWidget->setLayout(hBox);
	ui->ReaDiskScanningView->setCellWidget(1, 0, boxWidget);
	
}
