#include "datachosseform.h"
#include "ui_datachosseform.h"
#include <QtCore>

DataChosseForm::DataChosseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataChosseForm)
{
    ui->setupUi(this);
}

DataChosseForm::~DataChosseForm()
{
    delete ui;
}

void DataChosseForm::setDataJson(QJsonObject jsonobj)
{
    ui->label->setText(jsonobj.value("itemInfo").toString());
    QJsonArray arr=jsonobj.value("items").toArray();
    for(int i=0;i<arr.count();i++)
    {
        QJsonObject obj=arr.at(i).toObject();
        QString itemName=obj.value("itemName").toString();
        QString itemValue=obj.value("itemValue").toString();
        QListWidgetItem *item=new QListWidgetItem(itemName);
        item->setData(Qt::UserRole,itemValue);
        ui->listWidget->addItem(item);
    }
}

void DataChosseForm::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString value=item->data(Qt::UserRole).toString();
    ui->lineEdit->setText(value);

}

void DataChosseForm::on_lineEdit_textChanged(const QString &arg1)
{
    emit paramChossed(arg1);
}
