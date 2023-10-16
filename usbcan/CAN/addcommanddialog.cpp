#include "addcommanddialog.h"
#include "commontool.h"
#include "datachosseform.h"
#include "ui_addcommanddialog.h"
#include <QtCore>
#include <QtWidgets>

AddCommandDialog::AddCommandDialog(QWidget *parent) : QWidget(parent), ui(new Ui::AddCommandDialog), mCurrentRow(-1)
{
    ui->setupUi(this);
    mEventFilter = new FocusEventFilter(this);
    connect(mEventFilter, &FocusEventFilter::focusIn, [this](int row) { mCurrentRow = row; });

    //增加条数 之前只有一条
    ui->widget_oneCommand->setVisible(false);
    QHeaderView *header = ui->treeWidget->header();
    for (int col = 0; col < header->count(); col++)
    {
        if (3 != col)
            header->resizeSection(col, 70);
    }
}

AddCommandDialog::~AddCommandDialog()
{
    delete ui;
}

void AddCommandDialog::setCommandJson(QByteArray jsonStr)
{
    //    QJsonDocument doc = QJsonDocument::fromJson(jsonStr);
    //    if (doc.isEmpty())
    //        return;
    //    QJsonObject obj = doc.object();
    //    ui->label_commandName->setText(obj.value("name").toString());
    //    ui->lineEdit_id->setText(obj.value("id").toString());
    //    ui->lineEdit_command->setText(obj.value("command").toString());
    //    ui->lineEdit_commandSyn->setText(obj.value("frameId").toString());
    //    ui->spinBox->setValue(obj.value("duration").toString().toInt());

    //    QJsonArray arr = obj.value("data").toArray();
    //    mType = arr.count();
    //    if (mType)
    //        changeParam("0x00", 0);
    //    for (int i = 0; i < arr.count(); i++)
    //    {
    //        DataChosseForm *widget = new DataChosseForm(this);
    //        widget->setDataJson(arr.at(i).toObject());
    //        ui->layout_data->addWidget(widget);
    //        connect(widget, &DataChosseForm::paramChossed, [=](QString param) {
    //            changeParam(param, i);
    //            //qDebug() << param << i;
    //        });
    //    }

    //增加条数 之前只有一条
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr);
    if (doc.isEmpty())
        return;
    QJsonObject obj = doc.object();
    ui->label_commandName->setText(obj.value("name").toString());
    QString id = obj.value("id").toString();
    QString command = obj.value("command").toString();
    QString frameId = obj.value("frameId").toString();
    int duration = obj.value("duration").toString().toInt();
    int count = obj.value("count").toString("1").toInt();
    for (int row = 0; row < count; row++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        ui->treeWidget->addTopLevelItem(item);
        QLineEdit *lineEditId = new QLineEdit(id, this);
        ui->treeWidget->setItemWidget(item, 0, lineEditId);

        QLineEdit *lineEditCommand = new QLineEdit(command, this);
        ui->treeWidget->setItemWidget(item, 1, lineEditCommand);

        QLineEdit *lineEditFrameId = new QLineEdit(commonTool->numStrAdd(frameId, row), this);
        ui->treeWidget->setItemWidget(item, 2, lineEditFrameId);

        QLineEdit *lineEditData = new QLineEdit(this);
        ui->treeWidget->setItemWidget(item, 3, lineEditData);

        QSpinBox *lineEditDuration = new QSpinBox(this);
        lineEditDuration->setMaximum(999999);
        lineEditDuration->setValue(duration);
        ui->treeWidget->setItemWidget(item, 4, lineEditDuration);

        lineEditId->installEventFilter(mEventFilter);
        lineEditCommand->installEventFilter(mEventFilter);
        lineEditFrameId->installEventFilter(mEventFilter);
        lineEditData->installEventFilter(mEventFilter);
        lineEditDuration->installEventFilter(mEventFilter);
        mEventFilter->setWatchRow(lineEditId, row);
        mEventFilter->setWatchRow(lineEditCommand, row);
        mEventFilter->setWatchRow(lineEditFrameId, row);
        mEventFilter->setWatchRow(lineEditData, row);
        mEventFilter->setWatchRow(lineEditDuration, row);

        connect(lineEditCommand,&QLineEdit::textChanged,[](const QString &text){commonTool->checkValue(text, CommonTool::two);});
        connect(lineEditFrameId,&QLineEdit::textChanged,[](const QString &text){commonTool->checkValue(text, CommonTool::two);});
        connect(lineEditData,&QLineEdit::textChanged,[](const QString &text){commonTool->checkData(text);});
    }

    QJsonArray arr = obj.value("data").toArray();
    mType = arr.count();
    if (!mType)
        mType = 1;
    changeParam("0x00", 0);
    for (int i = 0; i < arr.count(); i++)
    {
        DataChosseForm *widget = new DataChosseForm(this);
        widget->setDataJson(arr.at(i).toObject());
        ui->layout_data->addWidget(widget);
        connect(widget, &DataChosseForm::paramChossed, [=](QString param) { changeParam(param, i); });
    }
}

void AddCommandDialog::setCommandValue(QList< QStringList > strsList)
{
    //    qDebug() << strs;
    //    if (5 != strs.count())
    //        return;
    //    ui->lineEdit_id->setText(strs.at(0));
    //    ui->lineEdit_command->setText(strs.at(1));
    //    ui->lineEdit_commandSyn->setText(strs.at(2));
    //    ui->lineEdit_data->setText(strs.at(3));
    //    QString duration = strs.at(4);
    //    ui->spinBox->setValue(duration.toInt());

    int minRow = std::min(strsList.count(), ui->treeWidget->topLevelItemCount());
    for (int row = 0; row < minRow; row++)
    {
        QStringList strs = strsList.at(row);
        if (5 != strs.count())
            continue;
        QString id = strs.at(0);
        QString command = strs.at(1);
        QString frameId = strs.at(2);
        QString dataStr = strs.at(3);
        int duration = strs.at(4).toInt();
        QLineEdit *lineEditId = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 0));
        QLineEdit *lineEditCommand = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 1));
        QLineEdit *lineEditFrameId = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 2));
        QLineEdit *lineEditData = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 3));
        QSpinBox *lineEditDuration = dynamic_cast< QSpinBox * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 4));
        if (!(lineEditId && lineEditCommand && lineEditFrameId && lineEditData && lineEditDuration))
            continue;
        lineEditId->setText(id);
        lineEditCommand->setText(command);
        lineEditFrameId->setText(frameId);
        lineEditData->setText(dataStr);
        lineEditDuration->setValue(duration);
    }
}

QList< QStringList > AddCommandDialog::commandStrings()
{
    //    QStringList str;
    //    str.append(ui->lineEdit_id->text());
    //    str.append(ui->lineEdit_command->text());
    //    str.append(ui->lineEdit_commandSyn->text());
    //    str.append(ui->lineEdit_data->text());
    //    str.append(ui->spinBox->text());
    //    return str;

    QList< QStringList > strsList;
    for (int row = 0; row < ui->treeWidget->topLevelItemCount(); row++)
    {
        QLineEdit *lineEditId = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 0));
        QLineEdit *lineEditCommand = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 1));
        QLineEdit *lineEditFrameId = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 2));
        QLineEdit *lineEditData = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 3));
        QSpinBox *lineEditDuration = dynamic_cast< QSpinBox * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 4));
        if (!(lineEditId && lineEditCommand && lineEditFrameId && lineEditData && lineEditDuration))
            continue;
        QStringList strs;
        strs << lineEditId->text();
        strs << lineEditCommand->text();
        strs << lineEditFrameId->text();
        strs << lineEditData->text();
        strs << lineEditDuration->text();
        strsList.append(strs);
    }
    return strsList;
}

void AddCommandDialog::changeParam(QString param, int index)
{
    auto changEdit = [=](QLineEdit *lineEdit, QString param, int index) {
        QString text = lineEdit->text();
        QVector< QString > dataSplit = text.split(commonTool->unNumberRegExp()).toVector();
        if (dataSplit.count() < mType)
        {
            dataSplit.clear();
            dataSplit.resize(mType);
            dataSplit.fill("0x00");
        }
        dataSplit.replace(index, param);
        lineEdit->setText(dataSplit.toList().join(","));
    };

    if (mCurrentRow < 0)
    {
        for (int row = 0; row < ui->treeWidget->topLevelItemCount(); row++)
        {
            QLineEdit *lineEdit = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(row), 3));
            changEdit(lineEdit, param, index);
        }
    }
    else
    {
        QLineEdit *lineEdit = dynamic_cast< QLineEdit * >(ui->treeWidget->itemWidget(ui->treeWidget->topLevelItem(mCurrentRow), 3));
        changEdit(lineEdit, param, index);
    }
}

void AddCommandDialog::on_pushButton_ok_clicked()
{
    if(!checkInput())
        return;
    //改为QWidget
    //accept();
    emit finished(true);
    hide();

}

void AddCommandDialog::on_pushButton_cancel_clicked()
{
    //改为QWidget
    //reject();
    emit finished(false);
    hide();
}

void AddCommandDialog::on_pushButton_send_clicked()
{
    if(!checkInput())
        return;
    emit commandTest();
}


void AddCommandDialog::on_lineEdit_data_textChanged(const QString &arg1)
{
    commonTool->checkData(arg1);
}

void AddCommandDialog::on_lineEdit_commandSyn_textChanged(const QString &arg1)
{
    commonTool->checkValue(arg1, CommonTool::two);
}

void AddCommandDialog::on_lineEdit_command_textChanged(const QString &arg1)
{
    commonTool->checkValue(arg1, CommonTool::two);
}

bool AddCommandDialog::checkInput()
{
    QList< QStringList > strsList = commandStrings();
    foreach (QStringList strs, strsList)
    {
        foreach (QString str, strs)
        {
            if (str.isEmpty())
            {
                QMessageBox::information(this, "提示", "指令错误！");
                return false;
            }
        }
    }
    return true;
}

/***************************************************************************************************/

FocusEventFilter::FocusEventFilter(QObject *parent) : QObject(parent)
{
}

bool FocusEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
        emit focusIn(mWatchedMap.value(watched));
    return false;
}

void FocusEventFilter::setWatchRow(QObject *watched, int row)
{
    mWatchedMap[watched] = row;
}
