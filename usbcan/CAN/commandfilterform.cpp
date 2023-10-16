#include "commandfilterform.h"
#include "commontool.h"
#include "ui_commandfilterform.h"
#include <QtCore>

CommandFilterForm::CommandFilterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandFilterForm)
{
    ui->setupUi(this);

    connect(ui->IDcomboBox,SIGNAL(currentTextChanged(const QString &)),
            this,SIGNAL(currentIDChanged(const QString &)));

    connect(ui->ordercomboBox,SIGNAL(currentTextChanged(const QString &)),
            this,SIGNAL(orderChanged(const QString &)));

    connect(ui->orderNumbercomboBox,SIGNAL(currentTextChanged(const QString &)),
            this,SIGNAL(orderNumberChanged(const QString &)));

    connect(ui->datacomboBox,SIGNAL(currentTextChanged(const QString &)),
            this,SIGNAL(dataChanged(const QString &)));

}
//设置所有组件不可用,可用
void CommandFilterForm::mSetAllNotEnable(bool enableFlag)
{
    ui->lineEdit_id->setEnabled(enableFlag);
    ui->lineEdit_command->setEnabled(enableFlag);
    ui->lineEdit_commandSyn->setEnabled(enableFlag);
    ui->lineEdit_data->setEnabled(enableFlag);

    ui->IDcomboBox->setEnabled(enableFlag);
    ui->ordercomboBox->setEnabled(enableFlag);
    ui->orderNumbercomboBox->setEnabled(enableFlag);
    ui->datacomboBox->setEnabled(enableFlag);

}
QLineEdit *CommandFilterForm::mGetIDLineEidt()
{
    return ui->lineEdit_id;
}
CommandFilterForm::~CommandFilterForm()
{
    delete ui;
}


