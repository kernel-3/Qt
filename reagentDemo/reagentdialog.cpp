#include <QRandomGenerator>
#include "reagentdialog.h"
#include "ui_reagentdialog.h"

#pragma execution_character_set("utf-8")

ReagentDialog::ReagentDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReagentDialog)
{
    ui->setupUi(this);
    setWindowTitle("试剂模块");
    initReagentInfoUI();
    initReagentStatusUI();
    initSlotAndSingal();
}

ReagentDialog::~ReagentDialog()
{
    delete ui;
}

void ReagentDialog::slotManualRegistration()
{
    //手动注册试剂或底物时设备必须在空闲时使用，否则提示设备正在运行
    QDialog  reaRegistertionDlg ;
    reaRegistertionDlg.setWindowTitle("手动注册条码");
    reaRegistertionDlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    reaRegistertionDlg.setMaximumWidth(500);
    reaRegistertionDlg.setMaximumHeight(300);
    QLabel barCodeName(&reaRegistertionDlg);
    barCodeName.setText("BarCode");
    barCodeName.setStyleSheet("QLabel{font-family:'宋体';font-size:20px;color:black;}");
    barCodeName.move(140, 105);
    barCodeName.show();
    QLineEdit barCodeNum(&reaRegistertionDlg);
	barCodeNum.setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{20}$")));
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
    connect(&btnCannel, &QPushButton::clicked, this, [&reaRegistertionDlg] {
       reaRegistertionDlg.close() ;
	});
    connect(&btnOk, &QPushButton::clicked, &reaRegistertionDlg, [this] {
        slotVerifyBarCodeWhetherLegal();
    });
	reaRegistertionDlg.exec();
}
 
void ReagentDialog::slotDeleteReagentInfo()
{
    //删除试剂或底物时设备必须是空闲状态，否则提示设备正在运行
	if (QMessageBox::question(this, tr("问题"),
		tr("是否确定要删除？"),
		tr("取消"),
		tr("确定")))
    {
       //系统将删除指定位置上的试剂或底物信息
    }
}

void ReagentDialog::slotReagentDiskScanning()
{
    ReagentDiskScanningDialog*reaDiskScanningDlg = new ReagentDiskScanningDialog();
    reaDiskScanningDlg->setWindowTitle("试剂盘扫描");
    reaDiskScanningDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    reaDiskScanningDlg->setMaximumWidth(500);
    reaDiskScanningDlg->setMaximumHeight(300);
    reaDiskScanningDlg->show();

}

void ReagentDialog::slotReagentDiskRoation()
{
    //只能在Stand By或Sleep状态下使用。在其它状态下使用此两项功能时，系统将会提示用户“仪器状态不正确”
}

void ReagentDialog::slotVerifyBarCodeWhetherLegal()
{
	QMessageBox::warning(this, tr("警告"), tr("底物或试剂条码非法警告！"), tr("确定"));

}

void ReagentDialog::slotOnReagentStatusSelectTableClicked(const QModelIndex& index)
{
	//点击左表，将对应数据更新到右表
	if (index.isValid()) {
		QString cellText = index.data().toString();

		//使用随机数填充
		QStandardItem* new_item;
		for (int j = 0;j<5;j++)
		{
			for (int i = 0; i < 17; i++)
			{
				QString testValueNum = QString::number(QRandomGenerator::global()->bounded(0, 100));
				new_item = new QStandardItem(testValueNum);
				new_item->setData(testValueNum, Qt::InitialSortOrderRole);
				new_item->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
				reagentStastusModel->setItem(i, j, new_item);
			}
		}
		
	}
}

void ReagentDialog::initReagentInfoUI()
{
	ui->reaInfoTable->setMinimumWidth(1003);
	QHeaderView* header = new QHeaderView(Qt::Horizontal, ui->reaInfoTable);
	ui->reaInfoTable->setHorizontalHeader(header);
	ui->reaInfoTable->verticalHeader()->setDefaultSectionSize(30);
	ui->reaInfoTable->horizontalHeader()->setDefaultSectionSize(100);
	QStringList reaInfoTableHeader;
	reaInfoTableHeader << "试剂盘位置号" << "项目名称" << "项目有效次数" << "试剂类型" << "试剂编号"
		<< "试剂批号" << "试剂序列号" << "项目名称" << "过期日期" << "试剂瓶规格";

	QStandardItemModel* model = new QStandardItemModel(this);
	int columCount = reaInfoTableHeader.count();
	model->setColumnCount(columCount);
	for (int i = 0; i < columCount; i++)
	{
		model->setHeaderData(i, Qt::Horizontal, reaInfoTableHeader.at(i));
	}
	ui->reaInfoTable->setModel(model);
}

void ReagentDialog::initReagentStatusUI()
{
	initReagentStatusUISelect();
	initReagentStatusUIDisaply();
}

void ReagentDialog::initReagentStatusUISelect()
{
	SortHeaderView* header = new SortHeaderView(Qt::Horizontal, ui->selectSection);
	ui->selectSection->setHorizontalHeader(header);
	ui->selectSection->verticalHeader()->setDefaultSectionSize(30);
	ui->selectSection->horizontalHeader()->setDefaultSectionSize(165);
	ui->selectSection->verticalHeader()->setVisible(false);
	ui->selectSection->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStandardItemModel* model = new QStandardItemModel(this);
	model->setColumnCount(2);
	model->setHeaderData(0, Qt::Horizontal, QString("项目名称"));
	model->setHeaderData(1, Qt::Horizontal, QString("项目有效次数"));

	//---testData
	QStandardItem* new_item;
	for (int i = 0;i<17;i++)
	{
		QString testValueChar = 'A' + i;
		new_item = new QStandardItem(testValueChar);
		new_item->setData(testValueChar, Qt::InitialSortOrderRole);
		new_item->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
		model->setItem(i, 0, new_item);
	}
	//使用随机数填充
	QRandomGenerator* rand_gen = QRandomGenerator::global();
	for (int i = 0; i < 17; i++)
	{
		QString testValueNum = QString::number(rand_gen->bounded(0, 100));
		new_item = new QStandardItem(testValueNum);
		new_item->setData(testValueNum, Qt::InitialSortOrderRole);
		new_item->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
		model->setItem(i, 1, new_item);
	}
	//---
	MySortFilterProxyModel* proxyModel = new MySortFilterProxyModel(this);
	proxyModel->setSortRole(Qt::InitialSortOrderRole);
	proxyModel->setSourceModel(model);
	ui->selectSection->setModel(proxyModel);
	ui->selectSection->setSortingEnabled(true);
    ui->selectSection->sortByColumn(0,Qt::AscendingOrder);

	connect(header, &SortHeaderView::sortOrderChanged,
		this, [this, header, proxyModel](int logicIndex, SortHeaderView::SortOrder order) {
		QTableView* view = ui->selectSection;
		if (logicIndex < 0 /*|| order == SortHeaderView::NoOrder*/) {
			header->setSortIndicator(-1, Qt::DescendingOrder);
			proxyModel->sort(-1, Qt::DescendingOrder);
		}
		else {
			switch (order) {
			case SortHeaderView::DescOrder:
				view->sortByColumn(logicIndex, Qt::DescendingOrder);
				break;
			case SortHeaderView::AscOrder:
				view->sortByColumn(logicIndex, Qt::AscendingOrder);
				break;
			}
		}
	});
	connect(ui->selectSection, &QTableView::clicked, this,&ReagentDialog::slotOnReagentStatusSelectTableClicked);
}

void ReagentDialog::initReagentStatusUIDisaply()
{
	QHeaderView* header = new QHeaderView(Qt::Horizontal, ui->displaySection);
	ui->displaySection->setHorizontalHeader(header);
	ui->displaySection->verticalHeader()->setDefaultSectionSize(30);
	ui->displaySection->horizontalHeader()->setDefaultSectionSize(132);
	ui->displaySection->verticalHeader()->setVisible(false);
	QStringList displayHorizontalHeader;
	displayHorizontalHeader << "模块名称"<< "试剂类型"<< "试剂位置"<< "试剂剩余有效次数"<< "过期日期";
	
    reagentStastusModel = new QStandardItemModel(this);
	int columCount = displayHorizontalHeader.count();
	reagentStastusModel->setColumnCount(columCount);
	for (int i = 0; i < columCount; i++)
	{
		reagentStastusModel->setHeaderData(i, Qt::Horizontal, displayHorizontalHeader.at(i));
	}
	ui->displaySection->setModel(reagentStastusModel);
}

void ReagentDialog::initSlotAndSingal()
{
    connect(ui->manualRegistration, &QPushButton::clicked, this, &ReagentDialog::slotManualRegistration);
    connect(ui->deleteReagentInfo, &QPushButton::clicked, this, &ReagentDialog::slotDeleteReagentInfo);
    connect(ui->reagentDiskScanning, &QPushButton::clicked, this, &ReagentDialog::slotReagentDiskScanning);
    connect(ui->reagentDIskRoation, &QPushButton::clicked, this, &ReagentDialog::slotReagentDiskRoation);
}


MySortFilterProxyModel::MySortFilterProxyModel(QObject* parent)
{
}

bool MySortFilterProxyModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
	if (!source_left.isValid() || !source_right.isValid())
		return false;

	if ((source_left.column() == 1) && (source_right.column() == 1))
	{
		QVariant leftData = sourceModel()->data(source_left);
		QVariant rightData = sourceModel()->data(source_right);

		if (leftData.canConvert<QString>() && rightData.canConvert<QString>())
		{
			return rightData.toInt() > leftData.toInt();
		}
	}

	return QSortFilterProxyModel::lessThan(source_left, source_right);
}
