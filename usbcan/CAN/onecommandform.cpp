#include "onecommandform.h"
#include "commontool.h"
#include "ui_onecommandform.h"

OneCommandForm::OneCommandForm(QWidget *parent) : QWidget(parent), ui(new Ui::OneCommandForm)
{
    ui->setupUi(this);
    setTitleVisible(false);
}

OneCommandForm::~OneCommandForm()
{
    delete ui;
}

QStringList OneCommandForm::commandString()
{
    QStringList strs;
    strs.append(ui->lineEdit_id->text().remove(" "));
    strs.append(ui->lineEdit_command->text().remove(" "));
    strs.append(ui->lineEdit_commandSyn->text().remove(" "));
    strs.append(ui->lineEdit_data->text().remove(" "));
    strs.append(ui->spinBox_cmdms->text().remove(" "));
    return strs;
}

bool OneCommandForm::isChecked()
{
    return ui->checkBox->isChecked();
}

void OneCommandForm::setTitleVisible(bool visible)
{
    QList< QLabel * > labels = findChildren< QLabel * >();
    foreach (QLabel *label, labels)
    {
        label->setVisible(visible);
    }
    if(visible)
        setMinimumHeight(40);
    else
        setMinimumHeight(30);
}

void OneCommandForm::restoreData(QStringList strs)
{
    if(strs.count()!=6)
        return;
    QString check=strs.at(0);
    ui->checkBox->setChecked(check.toInt());
    ui->lineEdit_id->setText(strs.at(1));
    ui->lineEdit_command->setText(strs.at(2));
    ui->lineEdit_commandSyn->setText(strs.at(3));
    ui->lineEdit_data->setText(strs.at(4));
    QString dalay=strs.at(5);
    ui->spinBox_cmdms->setValue(dalay.toInt());
}

void OneCommandForm::on_pushButton_clicked()
{
    emit sendCommand();
}

void OneCommandForm::on_lineEdit_data_textChanged(const QString &arg1)
{
    commonTool->checkData(arg1);
}

void OneCommandForm::on_lineEdit_commandSyn_textChanged(const QString &arg1)
{
    commonTool->checkValue(arg1,CommonTool::two);
}

void OneCommandForm::on_lineEdit_command_textChanged(const QString &arg1)
{
    commonTool->checkValue(arg1,CommonTool::two);
}
