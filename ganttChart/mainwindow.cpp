#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "canttchartview.h"
#include "cantttimebaritem.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CanttChartView* view = new CanttChartView(this);

	view->setAxisRange(QDateTime::fromString("2024-01-16 12:00:00", "yyyy-MM-dd hh:mm:ss"),
		QDateTime::fromString("2024-01-16 13:00:00", "yyyy-MM-dd hh:mm:ss"),
		QStringList() << "SP" << "RN" << "Gripper3D" << "SN" << "WP" << "DP" << "Incu" << "ASN");

	CanttTimeBarItem* item = view->addPlanTimeBar("SP",
		QDateTime::fromString("2024-01-16 12:00:05", "yyyy-MM-dd hh:mm:ss"),
		QDateTime::fromString("2024-01-16 12:00:10", "yyyy-MM-dd hh:mm:ss"));
	item->addEvent(QDateTime::fromString("2024-01-16 12:00:05", "yyyy-MM-dd hh:mm:ss"), CanttTimeBarItem::RotationEvent);

	CanttTimeBarItem* item1 = view->addRealTimeBar("SP",
		QDateTime::fromString("2024-01-16 12:00:05", "yyyy-MM-dd hh:mm:ss"),
		QDateTime::fromString("2024-01-16 12:00:10", "yyyy-MM-dd hh:mm:ss"));
	item1->addEvent(QDateTime::fromString("2024-01-16 12:00:05", "yyyy-MM-dd hh:mm:ss"), CanttTimeBarItem::TakeoffEvent);
	view->addRealTimeBar("Gripper3D",
		QDateTime::fromString("2024-01-16 12:00:20", "yyyy-MM-dd hh:mm:ss"),
		QDateTime::fromString("2024-01-16 12:00:30", "yyyy-MM-dd hh:mm:ss"));

	setCentralWidget(view);
	showMaximized();
}

MainWindow::~MainWindow()
{
	delete ui;
}
