#include "mainwindow.h"
#include "addcommanddialog.h"
#include "commandfilterform.h"
#include "commontool.h"
#include "excel/kqexcel.h"
#include "onecommandform.h"
#include "qtlog/qtlog.h"
#include "ui_mainwindow.h"
#include <QBitArray>
#include <QDesktopServices>
#include <QFileDialog>
#include <QInputDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSettings>
#include <QTime>
#include <QtCore>
#include <stdexcept>
#define KQUuid QUuid::createUuid().toString().replace(QRegExp("[{}-]"), "")

Q_DECLARE_METATYPE(QJsonObject)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置波特率
    ui->boundRatecomboBox->setCurrentIndex(10);

    /**********model view************************/
    //显示发送，显示接收
    ui->checkBox_send->setChecked(true);
    ui->checkBox_receive->setChecked(true);

    initModelView();
    /**********excel************************/
    QStringList logStr;
    logStr<<"系统时间"<<"can通道"<<"传输方向"<<"ID"<<"数据";
    sendCsvPath =  QString("%1/%2.csv").arg(qApp->applicationDirPath()).arg("接收帧与发送帧");

    GauGene::QtLog::songlogging(sendCsvPath, logStr.join(",").toUtf8());


    /**********指令链区域元素可以自由拖拽************************/
    ui->listWidget->setMovement(QListView::Snap);
    ui->listWidget->setDragDropMode(QListView::InternalMove);
    ui->listWidget->setSelectionMode(QListView::ExtendedSelection);

    //根据配置文件添加最近的几条命令
    addOneOrderSlot();
    ui->widget_info->setVisible(false);
    //设置分离器
    ui->splitter->setStretchFactor(1, 1);
    //读取，另存为指令按钮不可用
    ui->pushButton_save->setVisible(false);
    ui->pushButton_read->setVisible(false);
    //接收帧线程
    canthread = new CANThread();
    connect(canthread, &CANThread::getProtocolData, this, &MainWindow::onGetProtocolData);
    connect(canthread, &CANThread::boardInfo, this, &MainWindow::onBoardInfo);
    //获取包的反馈信息
    connect(canthread->mGetThread(),SIGNAL(sendResult(std::shared_ptr<SendData>, bool)),
            this,SLOT(slot_send_res(std::shared_ptr<SendData>, bool)));
    //指令链
    connect(canthread->mGetThread(),SIGNAL(sendCmdLineResult(SendData, bool)),
            this,SLOT(slot_send_cmdLine_res(SendData, bool)));

    //指定项
    connect(canthread->mGetThread(),SIGNAL(sendSelectRowResult(SendData, bool)),
            this,SLOT(slot_selectRow_cmdLine_res(SendData, bool)));
    readJson();
    readCommandList();
    restoreWindow();

    initSignalAndSlot();
    //5分钟清空下内存
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mClearMemorySlot()));
    timer->start(5*60*1000);
    //设置不可用
    // setNotEnableExpectChannelCombox(false);
}
//显示到界面
void MainWindow::modelShowFunction(SendData sendData)
{
    /********************model变化***********************************/
    quint8 command[2], commandSyn[2], dataSend[4];
    //指令
    QString comStr = sendData.comStr;
    toUChar2(commonTool->str2int(comStr), command);
    //指令序号
    QString comSynStr = sendData.comSynStr;
    toUChar2(commonTool->str2int(comSynStr), commandSyn);
    //真实的数据
    QString dataStr = sendData.dataStr;
    QStringList dataSplits = dataStr.split(commonTool->unNumberRegExp());
    if (dataSplits.count() == 1)
    {
        toUChar4(commonTool->str2int(dataStr), dataSend);
    }
    CANFrame currentFrame;
    currentFrame.TimeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz dddd");
    currentFrame.Bus = ui->channelComboBox->currentText();
    //发送帧
    currentFrame.Direction =QString("0");
    //id
    QString idStr = QString::number(sendData.pSend->ID,16);
    quint32 idNum = commonTool->str2int(idStr);

    //标准帧ID 只取小11位
    idNum = idNum & 0x7FF;
    currentFrame.FrameId = idStr;
    //长度
    currentFrame.Length = "0x" + QString::number(sendData.Len, 16).toUpper();

    //data
    QString str = "";

    str = "x| ";
    if(sendData.Len==1){
        str +=  QString("%1 ").arg(( unsigned char )command[1], 2, 16, QChar('0')).toUpper()
                +QString("%1 ").arg(( unsigned char )command[0], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )commandSyn[1], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )commandSyn[0], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[3], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[2], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[1], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[0], 2, 16, QChar('0')).toUpper();

    }
    str += QString("\n   %1 : %2 : %3").arg(comStr).arg(comSynStr).arg(dataStr);
    currentFrame.Data= str;
    //智能指针接口
    // QVector<QSharedPointer<CANFrame>> currentframes;
    auto framePtr = QSharedPointer<CANFrame>(new CANFrame(currentFrame));
    //currentframes.append(std::move(framePtr));
    model->addFrame(std::move(framePtr));
    //显示到最底部
    ui->canFramesView->scrollToBottom();
    ui->canFramesView->update();
}
//选择指定项
void MainWindow::slot_selectRow_cmdLine_res(SendData sendData, bool result)
{
    if(!result){
        //        QMessageBox::information(this, tr("提示"), tr("指令发送错误"));
        //        return;
    }
    //界面变化
    modelShowFunction(sendData);
    /***************界面左下角特殊处理 已循环个数**********************/
    //是否为特殊包
    if(true == sendData.sigleFlag){

        mSlecetRowNumber++;
        /*一条指令链循环次数*/
        quint64 oneLianNumber = sendData.oneLianNumber;

        if(0== oneLianNumber){
            return;
        }

        if(sendData.pacageIndex == oneLianNumber &&(mSlecetRowNumber%oneLianNumber ==0)){

            // 吧一页的数据，推送到发送线程
            if(ui->spinBox_loopTimes->value()>=ui->spinBox_loop->value()-1){
                ui->spinBox_loop->setEnabled(true);
                ui->spinBox_loopTimes->setEnabled(true);
                ui->spinBox_loopTimes->setValue(ui->spinBox_loop->value());
                return;
            }
            //循环次数变化
            int circleNumber = ui->spinBox_loopTimes->value();
            circleNumber++;

            ui->spinBox_loopTimes->setValue(circleNumber);

            canthread->mGetThread()->sendSelectRowData(mOneRowYeVector);

        }


    }
    return ;
}
//指令链
void MainWindow::slot_send_cmdLine_res(SendData sendData, bool result)
{
    if(!result){
        //        QMessageBox::information(this, tr("提示"), tr("指令发送错误"));
        //        return;
    }
    //界面变化
    modelShowFunction(sendData);

    qDebug()<<"current slot_send_cmdLine_res thread is:"<<QThread::currentThreadId();
    /***************界面左下角特殊处理 已循环个数**********************/
    //是否为特殊包
    if(true == sendData.isSpecialPackage){
        mSpeCialCmdLineNumber++;
        // /*循环次数*/
        quint64 circleNumber = sendData.circleNumber;
        /*指令个数*/
        quint64 orderNumber = sendData.orderNumber;
        /*当前指令索引*/
        quint64 orderIndex = sendData.orderIndex;
        quint64 oneLianNumber = sendData.oneLianNumber;

        if(0== oneLianNumber){
            return;
        }
        //设置到哪步
        if(orderIndex<=0){
            ui->listWidget->setCurrentRow(0);
        }
        ui->listWidget->setCurrentRow(orderIndex);


        if(sendData.pacageIndex == oneLianNumber &&(mSpeCialCmdLineNumber%oneLianNumber ==0)){
            // 吧一页的数据，推送到发送线程
            if(ui->spinBox_loopTimes->value()>=ui->spinBox_loop->value()-1){
                ui->spinBox_loop->setEnabled(true);
                ui->spinBox_loopTimes->setEnabled(true);
                ui->spinBox_loopTimes->setValue(ui->spinBox_loop->value());
                return;
            }
            //循环次数变化
            int circleNumber = ui->spinBox_loopTimes->value();
            circleNumber++;
            ui->spinBox_loopTimes->setValue(circleNumber);
            canthread->mGetThread()->sendCmdLineData(mOneYeVector);

        }


    }
    return ;
}
//清空下内存
void MainWindow::mClearMemorySlot()
{
    clearModelDataSlot();
}
void MainWindow::slot_send_res(std::shared_ptr<SendData> sendData, bool result)
{
    if(!result){
        //        QMessageBox::information(this, tr("提示"), tr("指令发送错误"));
        //        return;
    }
    /********************model变化***********************************/
    quint8 command[2], commandSyn[2], dataSend[4];
    //指令
    QString comStr = sendData->comStr;
    toUChar2(commonTool->str2int(comStr), command);
    //指令序号
    QString comSynStr = sendData->comSynStr;
    toUChar2(commonTool->str2int(comSynStr), commandSyn);
    //真实的数据
    QString dataStr = sendData->dataStr;
    QStringList dataSplits = dataStr.split(commonTool->unNumberRegExp());
    if (dataSplits.count() == 1)
    {
        toUChar4(commonTool->str2int(dataStr), dataSend);
    }
    CANFrame currentFrame;
    currentFrame.TimeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz dddd");
    currentFrame.Bus = ui->channelComboBox->currentText();
    //发送帧
    currentFrame.Direction =QString("0");
    //id
    QString idStr = QString::number(sendData->pSend->ID,16);
    quint32 idNum = commonTool->str2int(idStr);

    //标准帧ID 只取小11位
    idNum = idNum & 0x7FF;
    currentFrame.FrameId = idStr;
    //长度
    currentFrame.Length = "0x" + QString::number(sendData->Len, 16).toUpper();

    //data
    QString str = "";

    str = "x| ";
    if(sendData->Len==1){
        str +=  QString("%1 ").arg(( unsigned char )command[1], 2, 16, QChar('0')).toUpper()
                +QString("%1 ").arg(( unsigned char )command[0], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )commandSyn[1], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )commandSyn[0], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[3], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[2], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[1], 2, 16, QChar('0')).toUpper()+
                QString("%1 ").arg(( unsigned char )dataSend[0], 2, 16, QChar('0')).toUpper();

    }
    str += QString("\n   %1 : %2 : %3").arg(comStr).arg(comSynStr).arg(dataStr);
    currentFrame.Data= str;
    //智能指针接口
    // QVector<QSharedPointer<CANFrame>> currentframes;
    auto framePtr = QSharedPointer<CANFrame>(new CANFrame(currentFrame));
    //currentframes.append(std::move(framePtr));
    model->addFrame(std::move(framePtr));
    //显示到最底部
    ui->canFramesView->scrollToBottom();
    ui->canFramesView->update();


    return ;
}
void MainWindow::initSignalAndSlot()
{
    /***********songjingguo*********/
    //+号
    connect(ui->pushButton_addOne,SIGNAL(clicked()),this,SLOT(addOneOrderSlot()));
    //-号
    connect(ui->pushButton_reduceOne,SIGNAL(clicked()),this,SLOT(reduceOneSlot()));
    //发送按钮
    connect(ui->sendBtn,SIGNAL(clicked()),this,SLOT(sendBtnClickedSlot()));
    //清空ModelView数据按钮
    connect(ui->cleanListBtn,SIGNAL(clicked()),this,SLOT(clearModelDataSlot()));
    //打开设备
    connect(ui->startCANpushButton,SIGNAL(clicked()),this,SLOT(allDeviceOpenSlot()));
    //发送选择项
    connect(ui->sendSelectPushButton,SIGNAL(clicked()),this,SLOT(sendSelectItemSlot()));
    //停止循环按钮按下
    connect(ui->pushButton_stop,SIGNAL(clicked()),this,SLOT(stopSendCommandSlot()));
    //显示发送复选框选择
    connect(ui->checkBox_send,SIGNAL(toggled(bool)),this,SLOT(sendCheckSlot(bool)));
    //显示接收复选框选择
    connect(ui->checkBox_receive,SIGNAL(toggled(bool)),this,SLOT(receiveCheckSlot(bool)));
    //过滤功能
    //id filer
    connect(ui->widget_filter,SIGNAL(currentIDChanged(const QString &)),
            this,SLOT(idFilterSlot(const QString &)));
    //发送指令链表
    connect(ui->pushButton_sendList,SIGNAL(clicked()),this,SLOT(sendCommandListSlot()));
    //刷新指令
    connect(ui->pushButton_refresh,SIGNAL(clicked()),this,SLOT(refreshOrderSlot()));
    //读取指令连文件
    connect(ui->pushButton_read,SIGNAL(clicked()),this,SLOT(readOrderFileSlot()));
    //保存指令链文件
    connect(ui->pushButton_save,SIGNAL(clicked()),this,SLOT(saveOrderFileSlot()));
    //清空指令链列表
    connect(ui->pushButton_clearList,SIGNAL(clicked()),this,SLOT(clearOrderListSlot()));
    //保存指令链列表
    connect(ui->pushButton_saveList,SIGNAL(clicked()),this,SLOT(saveOrderListSlot()));

}
//id过滤
void MainWindow::idFilterSlot(const QString &IdChangedText)
{
    //0-不过滤，1-仅接收 2-不接收
    if(nullptr!=ui->widget_filter->mGetIDLineEidt()){
        QString idFilterValue = ui->widget_filter->mGetIDLineEidt()->text();
        if(idFilterValue.isEmpty()){

            QMessageBox::warning(this, "警告", "请输入过滤ID！！！");
            return;
        }
        bool ok;
        model->setIDFilterValue(idFilterValue.toLongLong(&ok,16));
        if(IdChangedText == QString("不过滤")){
            model->iDComBOxChangedFlilterSlot(0);

        }else if(IdChangedText == QString("仅接收")){
            model->iDComBOxChangedFlilterSlot(1);
        }else if(IdChangedText == QString("不接收")){
            model->iDComBOxChangedFlilterSlot(2);
        }
    }

    //根据内容自动放大
    // ui->canFramesView->resizeRowsToContents();
}
//显示接收复选框选择
void MainWindow::receiveCheckSlot(bool isChecked)
{
    model->receiveFrameCheckedSlot(isChecked);
    //根据内容自动放大
    //  ui->canFramesView->resizeRowsToContents();
}
//显示发送复选框选择
void MainWindow::sendCheckSlot(bool isChecked)
{
    model->sendFrameCheckedSlot(isChecked);
    //根据内容自动放大
    //  ui->canFramesView->resizeRowsToContents();
}
MainWindow::~MainWindow()
{
    saveWindow();
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        QListWidgetItem *item = ui->listWidget->currentItem();
        if (!item)
            return;
        if (QMessageBox::Yes == QMessageBox::question(0, "提示", "是否删除此指令？"))
        {
            delete item;
        }
    }
    return;
}
void MainWindow::onGetProtocolData(VCI_CAN_OBJ *vci, unsigned int dwRel, unsigned int channel)
{

    QVector<QSharedPointer<CANFrame>> currentframes;
    CANFrame frame;
    for (unsigned int i = 0; i < dwRel; i++)
    {
        //时间
        frame.TimeStamp =  QTime::currentTime().toString("hh:mm:ss zzz");
        if (vci[i].TimeFlag == 1)
        {
            //时间
            QString timeIdenty = "0x" + QString("%1").arg(vci[i].TimeStamp, 8, 16, QChar('0')).toUpper();
            frame.TimeIdenty = timeIdenty;
            QString TimeIdentyS = QString("%1").arg(QVariant(vci[i].TimeStamp * 0.1).toUInt(), 8, 10, QChar('0'));
            frame.TimeIdentyS = TimeIdentyS;
        }
        else
        {
            //时间
            frame.TimeIdenty= "无";
            frame.TimeIdentyS= "无";
        }
        //通道
        frame.Bus = "CH" + QString::number(channel);
        //传输方向 0发送 1-接收
        frame.Direction = QString("1");
        //ID
        frame.FrameId = "0x" + QString("%1").arg(vci[i].ID, 8, 16, QChar('0')).toUpper();
        //类型
        if(vci[i].RemoteFlag == 1){
            frame.FrameType = "远程帧";
        }else{
            frame.FrameType = "数据帧";
        }
        //格式
        if(vci[i].ExternFlag == 1){
            frame.FrameGeShi = "扩展帧";
        }else{
            frame.FrameGeShi = "标准帧";
        }
        QString str = "";
        //数据帧显示数据
        if (vci[i].RemoteFlag == 0) {
            //长度
            frame.Length ="0x" + QString::number(vci[i].DataLen, 16).toUpper();
            //数据
            str = "x|";
            for (int j = 0; j < vci[i].DataLen; j++)
                str += QString("%1 ").arg(vci[i].Data[j], 2, 16, QChar('0')).toUpper();
            frame.Data = str;

        }else{
            frame.Data =  "0x0";
        }
        auto framePtr = QSharedPointer<CANFrame>(new CANFrame(frame));
        model->addFrame(std::move(framePtr));
        currentframes.append(framePtr);
    }
    //添加到model中
    // model->addFrames(currentframes);
    /***************接收帧写入csv**********************/
    QList<QVariant> oneList;
    oneList<<frame.TimeStamp;
    oneList<<frame.Bus;
    oneList<<"接收";
    oneList<<frame.FrameId;
    oneList<<frame.Data;

    QStringList logStr;
    //系统时间
    logStr<<frame.TimeStamp;
    //can通道
    logStr<<frame.Bus;
    //传送方向
    logStr<<"接收";
    //id
    logStr<<frame.FrameId;
    //真实的数据
    logStr<<frame.Data;
    GauGene::QtLog::songlogging(sendCsvPath, logStr.join(",").toUtf8());

}

QString versionStr(unsigned short ver)
{
    return "V" + QString::number((ver & 0x0FFF) / 0x100, 16).toUpper() + "." + QString("%1 ").arg((ver & 0x0FFF) % 0x100, 2, 16, QChar('0')).toUpper();
}

void MainWindow::onBoardInfo(VCI_BOARD_INFO vbi)
{
    ui->label_9->setText(QString::number(vbi.can_Num));
    ui->label_10->setText(versionStr(vbi.hw_Version));
    ui->label_12->setText(versionStr(vbi.in_Version));
    ui->label_13->setText(QString::number(vbi.irq_Num));
}
bool MainWindow::deviceClose()
{

    bool flag = canthread->closeDevice();
    if(true == flag){
        return true;

    }else{
        return false;
    }

}
//打开
bool MainWindow::deviceOpen()
{

    unsigned int baundRate = 0;
    if (ui->boundRatecomboBox->currentText().indexOf("Kbps") != -1)
        baundRate = ui->boundRatecomboBox->currentText().remove("Kbps").toUInt();
    else
        baundRate = QVariant(ui->boundRatecomboBox->currentText().remove("Mbps").toFloat()).toUInt();
    //打开设备
    bool dev = canthread->openDevice(4,
                                     QVariant(ui->deveciveIndexComboBox->currentIndex()).toUInt(),
                                     baundRate);
    if (dev == true)
    {

        return  true;
    }
    else{
        QMessageBox::warning(this, "警告", "打开设备失败！");
        return false;
    }

}

void MainWindow::sendBtnClickedSlot()
{
    bool atleastone = false;
    for (int i = 0; i < ui->layout_command->count(); i++)
    {
        QLayoutItem *item = ui->layout_command->itemAt(i);
        OneCommandForm *widget = dynamic_cast< OneCommandForm * >(item->widget());
        if (!widget->isChecked())
            continue;
        atleastone = true;
        QStringList commandStr = widget->commandString();
        QString errStr;
        sendCommand(commandStr);
    }
    //如果一条都没有勾选 则发送第一条
    if (!atleastone)
    {
        QLayoutItem *item = ui->layout_command->itemAt(0);
        OneCommandForm *widget = dynamic_cast< OneCommandForm * >(item->widget());
        QStringList commandStr = widget->commandString();
        QString errStr;
        sendCommand(commandStr);
    }
}

void MainWindow::clearModelDataSlot()
{
    model->clearFrames();
}


bool MainWindow::canInit()  //初始化
{
    if (canthread->initCAN())
    {
        return true;
    }
    else{
        QMessageBox::warning(this, "警告", "CAN初始化失败！");
        return false;
    }

}

bool MainWindow::canStart()  //启动
{
    if (canthread->startCAN())
    {

        canthread->start();
        return true;
    }
    else{
        QMessageBox::warning(this, "警告", "CAN启动失败！");
        return false;
    }

}
void MainWindow::toUChar2(quint16 num, quint8 *bytes)
{
    bytes[0] = num & 0xff;         //取低字节
    bytes[1] = (num >> 8) & 0xff;  //取高字节
}
void MainWindow::toUChar4(quint32 num, quint8 *bytes)
{
    bytes[0] = num & 0xff;          //取低字节
    bytes[1] = (num >> 8) & 0xff;   //取高字节
    bytes[2] = (num >> 16) & 0xff;  //取高字节
    bytes[3] = (num >> 24) & 0xff;  //取高字节
}

void MainWindow::qwait(qint64 ms)
{
    if (ms < 1)
        return;
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec();
}

void MainWindow::readJson()
{
    QString path = QString("%1/json/command.json").arg(QApplication::applicationDirPath());
    // 打开json文件
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open file:" << file.fileName();
        return;
    }

    // 读取json数据
    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qWarning() << "Failed to parse json:" << error.errorString();
        return;
    }

    // 解析json对象
    if (!doc.isArray())
    {
        qWarning() << "Invalid json format.";
        return;
    }
    QJsonArray arr = doc.array();

    // 输出json数据
    QGridLayout *layout_unit = ui->gridLayout_unit;
    for (int i = layout_unit->count() - 1; i >= 0; i--)
    {
        QLayoutItem *item = layout_unit->takeAt(i);
        delete item->widget();
    }
    void (QComboBox::*comboxActivated)(int) = &QComboBox::activated;  //函数指针
    for (int i = 0; i < arr.count(); i++)
    {
        QJsonObject obj = arr.at(i).toObject();
        QString unitName = obj.value("unitName").toString();
        QJsonArray unitCommands = obj.value("unitCommands").toArray();
        QComboBox *combox = new QComboBox;
        builtComboBox(combox, unitCommands);
        connect(combox, comboxActivated, this, &MainWindow::addCommand);
        //connect(combox, &QComboBox::destroyed, [](){qDebug()<<"combox destroyed";});
        layout_unit->addWidget(new QLabel(unitName, this), i, 0);
        layout_unit->addWidget(combox, i, 1);
    }
    layout_unit->setColumnStretch(1, 1);
}

void MainWindow::readCommandList()
{
    QString curText;
    if (ui->comboBox_commandList->count())
        curText = ui->comboBox_commandList->currentText();
    QString path = QString("%1/json/commandList.json").arg(QApplication::applicationDirPath());
    QFile file(path);
    QByteArray oldjson;
    if (file.open(QFile::ReadOnly))
    {
        oldjson = file.readAll();
        file.close();
    }
    QJsonDocument doc = QJsonDocument::fromJson(oldjson);
    QJsonArray arr;
    if (doc.isArray())
        arr = doc.array();
    ui->comboBox_commandList->clear();
    for (int i = 0; i < arr.count(); i++)
    {
        QJsonObject obj = arr.at(i).toObject();
        QString commandGroup = obj.value("commandGroup").toString();
        QVariant varObj = QVariant::fromValue(obj);
        ui->comboBox_commandList->addItem(commandGroup, varObj);
    }
    if (!curText.isEmpty())
        ui->comboBox_commandList->setCurrentText(curText);
}

void MainWindow::builtComboBox(QComboBox *box, const QJsonArray &jsonArr)
{
    box->clear();
    for (int i = 0; i < jsonArr.count(); i++)
    {
        QJsonObject obj = jsonArr.at(i).toObject();
        QJsonDocument doc(obj);
        QString text = obj.value("name").toString();
        QByteArray value = doc.toJson();
        box->addItem(text, value);
        mCommandMap.insert(text, value);
    }
}
void MainWindow::initModelView()
{
    model = new CANFrameModel(this);
    ui->canFramesView->setModel(model);
    //设置选中模式为选中行
    ui->canFramesView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置选中单个
    ui->canFramesView->setSelectionMode( QAbstractItemView::SingleSelection);
    //设置列隐藏
    for(int i=6;i<=10;++i){
        ui->canFramesView->setColumnHidden(i,true);
    }
    ui->canFramesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::sendCommand(QStringList commandSplit, bool bloop)
{

    if (commandSplit.count() != 5)
    {
        qDebug()<<tr("错误指令")<<endl;
        return ;
    }
    //线程开启
    canthread->mGetThread()->mSendStart();


    QString idStr = commandSplit.at(0);
    quint32 idNum = commonTool->str2int(idStr);

    //标准帧ID 只取小11位
    idNum = idNum & 0x7FF;
    unsigned char data[8];
    memset(data, 0, 8);
    quint8 command[2], commandSyn[2], dataSend[4];
    //指令
    QString comStr = commandSplit.at(1);
    toUChar2(commonTool->str2int(comStr), command);
    memcpy(data, command, 2);
    //指令序号
    QString comSynStr = commandSplit.at(2);
    toUChar2(commonTool->str2int(comSynStr), commandSyn);
    memcpy(data + 2, commandSyn, 2);
    //真实的数据
    QString dataStr = commandSplit.at(3);
    QStringList dataSplits = dataStr.split(commonTool->unNumberRegExp());
    if (dataSplits.count() == 1)
    {
        toUChar4(commonTool->str2int(dataStr), dataSend);
        memcpy(data + 4, dataSend, 4);
    }
    else if (dataSplits.count() == 2)
    {
        quint8 bytes[2];
        QString splitStr = dataSplits.first();
        toUChar2(commonTool->str2int(splitStr), bytes);
        data[4] = bytes[0];
        data[5] = bytes[1];

        splitStr = dataSplits.last();
        toUChar2(commonTool->str2int(splitStr), bytes);
        data[6] = bytes[0];
        data[7] = bytes[1];
    }
    else if (dataSplits.count() == 4)
    {
        QString splitStr = dataSplits.at(0);
        data[4] = commonTool->str2int(splitStr);

        splitStr = dataSplits.at(1);
        data[5] = commonTool->str2int(splitStr);

        splitStr = dataSplits.at(2);
        data[6] = commonTool->str2int(splitStr);

        splitStr = dataSplits.at(3);
        data[7] = commonTool->str2int(splitStr);
    }

    unsigned int dlc = 8;

    SendData  tempData;
    tempData.DeviceType = 4;
    tempData.DeviceInd = QVariant(ui->deveciveIndexComboBox->currentIndex()).toUInt();
    tempData.remoteFlag =0;
    tempData.externFlag = 0;
    for(unsigned int j = 0;j < 8;j++){
        tempData.dataArray[j] = data[j];
    }
    tempData.dataDlc = 8;
    tempData.comStr = comStr;
    tempData.comSynStr = comSynStr;
    tempData.dataStr = dataStr;
    tempData.duration = commandSplit.at(4).toInt();
    tempData.bloop = bloop;
    //can唯一标识
    tempData.pacakeIdStr = idStr;
    this->sendData(tempData);
}
//4.发送数据
void MainWindow::sendData(const SendData&data)
{
    //wwc 智能指针管理局部变量
    auto shared_vcp = std::make_shared<VCI_CAN_OBJ>();
    shared_vcp->ID = commonTool->str2int(data.pacakeIdStr);
    shared_vcp->RemoteFlag = data.remoteFlag;
    shared_vcp->ExternFlag = data.externFlag;
    shared_vcp->DataLen = data.dataDlc;
    for(unsigned int j = 0;j < data.dataDlc;j++)
        shared_vcp->Data[j] = data.dataArray[j];


    //改为在单独线程里发送 不要卡主进程
    auto shared_msg = std::make_shared<SendData>();
    shared_msg->DeviceType=4;
    shared_msg->DeviceInd=QVariant(ui->deveciveIndexComboBox->currentIndex()).toUInt();
    //
    shared_msg->CANInd=QVariant(ui->deveciveIndexComboBox->currentIndex()).toUInt();
    shared_msg->pSend= shared_vcp;
    shared_msg->Len=1;
    shared_msg->uuid=QUuid::createUuid().toString();
    shared_msg->comStr = data.comStr;
    shared_msg->comSynStr = data.comSynStr;
    shared_msg->dataStr = data.dataStr;
    shared_msg->duration = data.duration;
    shared_msg->bloop = data.bloop;

    //指令ID
    shared_msg->pacakeIdStr = data.pacakeIdStr;

    //发送线程工作
    canthread->mGetThread()->sendData(shared_msg);

}
QString MainWindow::saveDir()
{
    QString iniPath = QString("%1/config.ini").arg(qApp->applicationDirPath());
    QSettings iniFile(iniPath, QSettings::IniFormat);
    QString lastDir = iniFile.value("lastDir", QString("%1/commandList").arg(qApp->applicationDirPath())).toString();
    QDir dir(lastDir);
    if (!dir.exists())
        dir.mkdir(lastDir);
    return lastDir;
}

void MainWindow::setSaveDir(QString dir)
{
    QString iniPath = QString("%1/config.ini").arg(qApp->applicationDirPath());
    QSettings iniFile(iniPath, QSettings::IniFormat);
    iniFile.setValue("lastDir", dir);
}

void MainWindow::saveWindow()
{
    QString iniPath = QString("%1/config.ini").arg(qApp->applicationDirPath());
    QSettings iniFile(iniPath, QSettings::IniFormat);
    iniFile.setValue("geometry", saveGeometry());
    iniFile.setValue("state", saveState());

    QStringList commands;
    for (int i = 0; i < ui->layout_command->count(); i++)
    {
        QLayoutItem *item = ui->layout_command->itemAt(i);
        OneCommandForm *widget = dynamic_cast< OneCommandForm * >(item->widget());
        QString check = widget->isChecked() ? "1" : "0";
        QStringList commandStr = widget->commandString();
        commandStr.prepend(check);
        commands.append(commandStr.join("_"));
    }
    iniFile.setValue("commands", commands.join("#"));
}

void MainWindow::restoreWindow()
{
    QString iniPath = QString("%1/config.ini").arg(qApp->applicationDirPath());
    QSettings iniFile(iniPath, QSettings::IniFormat);
    restoreGeometry(iniFile.value("geometry").toByteArray());
    restoreState(iniFile.value("state").toByteArray());
    QString commands = iniFile.value("commands").toString();
    QStringList commandSplit = commands.split("#");
    for (int i = 1; i < commandSplit.count(); i++)
        addOneOrderSlot();

    for (int i = 0; i < ui->layout_command->count(); i++)
    {
        QLayoutItem *item = ui->layout_command->itemAt(i);
        OneCommandForm *widget = dynamic_cast< OneCommandForm * >(item->widget());
        QString dataStr = commandSplit.at(i);
        widget->restoreData(dataStr.split("_"));
    }
}
//打开设备失败的时候，设置只有通道commbox可用，其他都是灰色不可用
void MainWindow::setNotEnableExpectChannelCombox(bool flag)
{
    //通道commbox除外
    ui->channelComboBox->setEnabled(true);
    //加，减号不可用
    ui->pushButton_addOne->setEnabled(flag);
    ui->pushButton_reduceOne->setEnabled(flag);
    //指令区
    for (int i = ui->layout_command->count() - 1; i >= 0; i--)
    {
        QLayoutItem *item = ui->layout_command->itemAt(i);
        if(nullptr!=item){

            if(nullptr!=item->widget()){
                item->widget()->setEnabled(flag);
            }

        }
    }
    //预定义指令区
    QGridLayout *layout_unit = ui->gridLayout_unit;
    for (int i = layout_unit->count() - 1; i >= 0; i--)
    {
        QLayoutItem *item = layout_unit->itemAt(i);
        if(nullptr!=item){
            if(nullptr!=item->widget()){
                item->widget()->setEnabled(flag);
            }

        }
    }
    //发送
    ui->sendBtn->setEnabled(flag);
    //刷新
    ui->pushButton_refresh->setEnabled(flag);
    //指令链下拉
    ui->comboBox_commandList->setEnabled(flag);
    //保存指令链
    ui->pushButton_saveList->setEnabled(flag);
    //读取
    ui->pushButton_read->setEnabled(flag);
    //另存为
    ui->pushButton_save->setEnabled(flag);
    //清空列表
    ui->pushButton_clearList->setEnabled(flag);
    //循环
    ui->spinBox_loop->setEnabled(flag);
    //已循环
    ui->spinBox_loopTimes->setEnabled(flag);
    //停止
    ui->pushButton_stop->setEnabled(flag);
    //间隔(ms)
    ui->spinBox->setEnabled(flag);
    //指令链 list
    ui->listWidget->setEnabled(flag);
    //发送选择项
    ui->sendSelectPushButton->setEnabled(flag);
    //发送指令链
    ui->pushButton_sendList->setEnabled(flag);
    //显示发送
    ui->checkBox_send->setEnabled(flag);
    //显示接收
    ui->checkBox_receive->setEnabled(flag);
    //清空
    ui->cleanListBtn->setEnabled(flag);
    //ID,指令，指令序号，数据
    ui->widget_filter->mSetAllNotEnable(flag);


}
void MainWindow::allDeviceOpenSlot()
{
    if (ui->startCANpushButton->text() == tr("打开设备"))
    {

        if((true == deviceOpen()) &&(true == canInit())&&(true == canStart())){

            ui->startCANpushButton->setText(tr("关闭设备"));
            //设置可用
            //setNotEnableExpectChannelCombox(true);
            return;

        }else{
            //设置不可用
            //setNotEnableExpectChannelCombox(false);
            return;
        }

    }
    if (ui->startCANpushButton->text() == tr("关闭设备"))
    {
        bool flag = deviceClose();
        //关闭设备成功
        if(true == flag){
            ui->startCANpushButton->setText(tr("打开设备"));
            //设置不可用
            //setNotEnableExpectChannelCombox(false);
            if((canthread!=nullptr)&&(canthread->isRunning())){
                canthread->stop();

            }
        }

    }
}

void MainWindow::refreshOrderSlot()
{
    readJson();
    readCommandList();
    qDebug() << "refresh command list success" << endl;

}

void MainWindow::addCommand()
{
    QComboBox *combox = dynamic_cast< QComboBox * >(sender());
    if (!combox)
        return;
    QByteArray ba = combox->currentData().toByteArray();

    // 20230508 改为了QWidget
    AddCommandDialog *dlg = new AddCommandDialog(this);
    dlg->setWindowFlag(Qt::Tool);
    dlg->setCommandJson(ba);
    dealAddDialogTest(dlg);
    dlg->show();
    connect(dlg, &AddCommandDialog::finished, [=](bool result) {
        if (!result)
        {
            dlg->deleteLater();
            return;
        }
        QList< QStringList > commandStrs = dlg->commandStrings();
        dlg->deleteLater();
        if (!commandStrs.count())
            return;
        QString text = QString("%1: %2 : %3").arg(combox->currentText()).arg(commandStrs.count()).arg(commandStrs.first().join(" "));
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(text);

        QStringList fullData;
        foreach (QStringList strs, commandStrs)
        {
            fullData << strs.join("_");
        }
        item->setToolTip(fullData.join("\n"));
        item->setData(Qt::UserRole, fullData);
        item->setData(Qt::UserRole + 1, ba);
        item->setData(Qt::UserRole + 2, combox->currentText());
        ui->listWidget->addItem(item);
    });
}

void MainWindow::dealAddDialogTest(AddCommandDialog *dlg)
{
    connect(dlg, &AddCommandDialog::commandTest, [this, dlg]() {
        QList< QStringList > commandStrs = dlg->commandStrings();
        foreach (QStringList command, commandStrs)
        {
            sendCommand(command);
        }
    });
}

void MainWindow::sendCommandListSlot()
{

    if(ui->listWidget->count()<=0){
        QMessageBox::information(this, "提示", "指令链中没有指令");
        return;
    }
    //设置计数器
    mSpeCialCmdLineNumber =0;
    canthread->mGetThread()->mSendStart();
    // ui界面不能够修改
    ui->spinBox_loop->setEnabled(false);
    ui->spinBox_loopTimes->setEnabled(false);
    ui->spinBox_loopTimes->setValue(0);
    //循环次数
    ui->spinBox_loopTimes->setValue(0);
    mLoopStop = false;
    //一条指令链循环个个数
    unsigned int oneLianNumber =0;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item!=nullptr){
            QStringList fullData = item->data(Qt::UserRole).toStringList();
            oneLianNumber+= fullData.size();
        }
    }
    //发送一页的单元
    quint64 OneYeNumber =0;
    QVector<SendData>oneYeVector;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item!=nullptr){

            QStringList fullData = item->data(Qt::UserRole).toStringList();
            for(int index=0;index<fullData.size();++index){
                SendData currentData;
                OneYeNumber++;
                /*循环次数*/
                unsigned int circleNumber = ui->spinBox_loop->value();
                /*指令个数*/
                unsigned int orderNumber = ui->listWidget->count();
                /*当前指令索引*/
                unsigned int orderIndex = i;
                /*一页的大小*/
                //获取发送的内容
                currentData.pacageIndex = OneYeNumber;
                currentData.isSpecialPackage = true;
                currentData.circleNumber = circleNumber;
                currentData.orderNumber = orderNumber;
                currentData.orderIndex = orderIndex;
                currentData.oneLianNumber = oneLianNumber;
                auto ptr = mSplitCmdToSendData(fullData.at(index),currentData);
                oneYeVector.push_back(ptr);
            }

        }


    }
    mOneYeVector = oneYeVector;
    // 吧一页的数据，推送到发送线程
    if(nullptr!=canthread->mGetThread()){
        if(mOneYeVector.size()<=0){
            return;
        }
        canthread->mGetThread()->sendCmdLineData(oneYeVector);
    }
}
//分离命令赋值到结构
SendData MainWindow::mSplitCmdToSendData(const QString &cmd,SendData &valueData)
{
    QStringList commandSplit = cmd.split("_");
    if (commandSplit.count() != 5)
    {
        qDebug()<<tr("错误指令")<<endl;
        SendData temp;
        return  temp;
    }
    QString idStr = commandSplit.at(0);
    quint32 idNum = commonTool->str2int(idStr);

    //标准帧ID 只取小11位
    idNum = idNum & 0x7FF;
    unsigned char data[8];
    memset(data, 0, 8);
    quint8 command[2], commandSyn[2], dataSend[4];
    //指令
    QString comStr = commandSplit.at(1);
    toUChar2(commonTool->str2int(comStr), command);
    memcpy(data, command, 2);
    //指令序号
    QString comSynStr = commandSplit.at(2);
    toUChar2(commonTool->str2int(comSynStr), commandSyn);
    memcpy(data + 2, commandSyn, 2);
    //真实的数据
    QString dataStr = commandSplit.at(3);
    QStringList dataSplits = dataStr.split(commonTool->unNumberRegExp());
    if (dataSplits.count() == 1)
    {
        toUChar4(commonTool->str2int(dataStr), dataSend);
        memcpy(data + 4, dataSend, 4);
    }
    else if (dataSplits.count() == 2)
    {
        quint8 bytes[2];
        QString splitStr = dataSplits.first();
        toUChar2(commonTool->str2int(splitStr), bytes);
        data[4] = bytes[0];
        data[5] = bytes[1];

        splitStr = dataSplits.last();
        toUChar2(commonTool->str2int(splitStr), bytes);
        data[6] = bytes[0];
        data[7] = bytes[1];
    }
    else if (dataSplits.count() == 4)
    {
        QString splitStr = dataSplits.at(0);
        data[4] = commonTool->str2int(splitStr);

        splitStr = dataSplits.at(1);
        data[5] = commonTool->str2int(splitStr);

        splitStr = dataSplits.at(2);
        data[6] = commonTool->str2int(splitStr);

        splitStr = dataSplits.at(3);
        data[7] = commonTool->str2int(splitStr);
    }

    unsigned int dlc = 8;

    valueData.DeviceType = 4;
    valueData.DeviceInd = QVariant(ui->deveciveIndexComboBox->currentIndex()).toUInt();
    valueData.remoteFlag =0;
    valueData.externFlag = 0;
    for(unsigned int j = 0;j < 8;j++){
        valueData.dataArray[j] = data[j];
    }
    valueData.dataDlc = 8;
    valueData.comStr = comStr;
    valueData.comSynStr = comSynStr;
    valueData.dataStr = dataStr;
    valueData.duration = commandSplit.at(4).toInt();
    //???
    valueData.bloop = false;
    //can唯一标识
    valueData.pacakeIdStr = idStr;



    //wwc 智能指针管理局部变量
    auto shared_vcp = std::make_shared<VCI_CAN_OBJ>();
    shared_vcp->ID = commonTool->str2int(valueData.pacakeIdStr);
    shared_vcp->RemoteFlag = valueData.remoteFlag;
    shared_vcp->ExternFlag = valueData.externFlag;
    shared_vcp->DataLen = valueData.dataDlc;
    for(unsigned int j = 0;j < valueData.dataDlc;j++)
        shared_vcp->Data[j] = valueData.dataArray[j];


    //改为在单独线程里发送 不要卡主进程
    SendData shared_msg;
    shared_msg.DeviceType=4;
    shared_msg.DeviceInd=QVariant(ui->deveciveIndexComboBox->currentIndex()).toUInt();
    //
    shared_msg.CANInd=QVariant(ui->deveciveIndexComboBox->currentIndex()).toUInt();
    shared_msg.pSend= shared_vcp;
    shared_msg.Len=1;
    shared_msg.uuid=QUuid::createUuid().toString();
    shared_msg.comStr = valueData.comStr;
    shared_msg.comSynStr = valueData.comSynStr;
    shared_msg.dataStr = valueData.dataStr;
    shared_msg.duration = valueData.duration;
    shared_msg.bloop = valueData.bloop;

    //指令ID
    shared_msg.pacakeIdStr = valueData.pacakeIdStr;
    shared_msg.isSpecialPackage = valueData.isSpecialPackage;
    shared_msg.pacageIndex = valueData.pacageIndex;
    shared_msg.isSpecialPackage = true;
    shared_msg.circleNumber = valueData.circleNumber;
    shared_msg.orderNumber = valueData.orderNumber;
    shared_msg.orderIndex = valueData.orderIndex;
    shared_msg.oneLianNumber = valueData.oneLianNumber;
    //单独包
    shared_msg.sigleFlag = valueData.sigleFlag;

    return shared_msg;
}
void MainWindow::addOneOrderSlot()
{
    int count = ui->layout_command->count();
    OneCommandForm *widget = new OneCommandForm(this);
    widget->setTitleVisible(!count);
    ui->layout_command->insertWidget(count, widget);

    connect(widget, &OneCommandForm::sendCommand, this, [this, widget] {
        sendCommand(widget->commandString());
    });
}

void MainWindow::reduceOneSlot()
{
    int count = ui->layout_command->count();
    if (count > 1)
    {
        QLayoutItem *item = ui->layout_command->takeAt(count - 1);
        if (item)
        {
            QWidget *widget = item->widget();
            if (widget)
                widget->deleteLater();
        }
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QStringList fullData = item->data(Qt::UserRole).toStringList();
    QList< QStringList > commandStrs;
    foreach (QString str, fullData)
    {
        commandStrs << str.split("_");
    }
    QString optionId = item->data(Qt::UserRole + 2).toString();
    QByteArray ba = item->data(Qt::UserRole + 1).toByteArray();
    if (ba.isEmpty())
        ba = mCommandMap.value(optionId);

    // 20230508 改为了QWidget
    AddCommandDialog *dlg = new AddCommandDialog(this);
    dlg->setWindowFlag(Qt::Tool);
    dlg->setCommandJson(ba);
    dlg->setCommandValue(commandStrs);
    dealAddDialogTest(dlg);
    dlg->show();

    connect(dlg, &AddCommandDialog::finished, [=](bool result) {
        if (!result)
        {
            dlg->deleteLater();
            return;
        }

        QList< QStringList > commandStrs = dlg->commandStrings();
        dlg->deleteLater();
        if (!commandStrs.count())
            return;
        QStringList fullData;
        foreach (QStringList strs, commandStrs)
        {
            fullData << strs.join("_");
        }
        QString text = QString("%1: %2 : %3").arg(optionId).arg(commandStrs.count()).arg(commandStrs.first().join(" "));
        item->setText(text);
        item->setToolTip(fullData.join("\n"));
        item->setData(Qt::UserRole, fullData);
    });
}

void MainWindow::readOrderFileSlot()
{
    QString path = QFileDialog::getOpenFileName(0, "保存文件", saveDir(), "*.json");
    if (path.isEmpty())
        return;
    setSaveDir(QFileInfo(path).absolutePath());
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(this, "提示", "文件打开失败");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isEmpty())
        return;
    if (ui->listWidget->count() && QMessageBox::Yes == QMessageBox::question(0, "提示", "是否先清空列表里的指令？"))
    {
        ui->listWidget->clear();
    }
    QJsonArray arr = doc.array();
    for (int i = 0; i < arr.count(); i++)
    {
        QJsonObject obj = arr.at(i).toObject();
        QString commandStr = obj.value("command").toString().remove(" ");
        QStringList commandSplit = commandStr.split("_");
        QString name = obj.value("name").toString().remove(" ");
        QString text = QString("%1: %2").arg(name).arg(commandSplit.join(" "));
        QListWidgetItem *item = new QListWidgetItem;
        item->setData(Qt::UserRole, commandSplit);
        item->setData(Qt::UserRole + 2, name);
        item->setData(Qt::UserRole + 1, mCommandMap.value(name));
        item->setText(text);
        ui->listWidget->addItem(item);
    }
}

void MainWindow::saveOrderFileSlot()
{
    if (!ui->listWidget->count())
        return;

    QString path = QFileDialog::getSaveFileName(0, "保存文件", saveDir(), "*.json");
    if (path.isEmpty())
        return;
    setSaveDir(QFileInfo(path).absolutePath());
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QMessageBox::information(this, "提示", "文件打开失败");
        return;
    }
    QJsonArray arr;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QJsonObject obj;
        obj["command"] = item->data(Qt::UserRole).toStringList().join("_");
        obj["name"] = item->data(Qt::UserRole + 2).toString();
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    file.write(doc.toJson(QJsonDocument::Indented));

    QDesktopServices::openUrl(QUrl("file:///" + QFileInfo(path).absolutePath()));
}

void MainWindow::clearOrderListSlot()
{
    ui->listWidget->clear();
}
void MainWindow::saveOrderListSlot()
{
    QString path = QString("%1/json/commandList.json").arg(QApplication::applicationDirPath());
    QFile file(path);
    QByteArray oldjson;
    if (file.open(QFile::ReadOnly))
    {
        oldjson = file.readAll();
        file.close();
    }
    QJsonDocument doc = QJsonDocument::fromJson(oldjson);
    QJsonArray arr;
    if (doc.isArray())
        arr = doc.array();
    QHash< QString, QJsonObject > objMap;
    QStringList keys;
    for (int i = 0; i < arr.count(); i++)
    {
        QJsonObject obj = arr.at(i).toObject();
        QString commandGroup = obj.value("commandGroup").toString();
        objMap.insert(commandGroup, obj);
        keys.append(commandGroup);
    }
    QInputDialog dlg;
    dlg.setComboBoxItems(keys);
    dlg.setComboBoxEditable(true);
    dlg.setTextValue(ui->comboBox_commandList->currentText());
    dlg.setLabelText(QString("请选择或输入组名"));
    dlg.exec();
    QString chooseKey = dlg.textValue();
    if (chooseKey.isEmpty())
        return;
    if (!objMap.contains(chooseKey))
    {
        QJsonObject &obj = objMap[chooseKey];
        obj["commandGroup"] = chooseKey;
        keys.append(chooseKey);
    }
    QJsonObject &obj = objMap[chooseKey];
    QJsonArray commandItems;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QJsonObject obj;
        obj["command"] = QJsonArray::fromStringList(item->data(Qt::UserRole).toStringList());
        obj["name"] = item->data(Qt::UserRole + 2).toString();
        commandItems.append(obj);
    }
    obj["commandItems"] = commandItems;
    QJsonArray arrNew;
    foreach (QString key, keys)
    {
        arrNew.append(objMap.value(key));
    }
    doc.setArray(arrNew);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QMessageBox::information(this, "提示", "文件打开失败");
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    readCommandList();

}

void MainWindow::on_comboBox_commandList_activated(const QString &)
{
    QJsonObject obj = ui->comboBox_commandList->currentData().value< QJsonObject >();
    QJsonArray arr = obj.value("commandItems").toArray();
    if (!arr.count())
        return;
    if (ui->listWidget->count() && QMessageBox::Yes == QMessageBox::question(0, "提示", "是否先清空列表里的指令？"))
    {
        ui->listWidget->clear();
    }
    for (int i = 0; i < arr.count(); i++)
    {
        QJsonObject obj = arr.at(i).toObject();
        QJsonArray commandArr = obj.value("command").toArray();
        if (!commandArr.count())
            continue;
        QStringList fullData;
        for (int i = 0; i < commandArr.count(); i++)
        {
            fullData << commandArr.at(i).toString();
        }
        QString name = obj.value("name").toString().remove(" ");
        QString text = QString("%1: %2 : %3").arg(name).arg(fullData.count()).arg(fullData.first());
        QListWidgetItem *item = new QListWidgetItem;
        item->setToolTip(fullData.join("\n"));
        item->setData(Qt::UserRole, fullData);
        item->setData(Qt::UserRole + 2, name);
        item->setData(Qt::UserRole + 1, mCommandMap.value(name));
        item->setText(text);
        ui->listWidget->addItem(item);
    }
}

//发送选择项
void MainWindow::sendSelectItemSlot()
{
    if(ui->listWidget->count()<=0){
        QMessageBox::information(this, "提示", "指令链中没有指令!!!!");
        return;
    }
    //线程开启
    canthread->mGetThread()->mSendStart();
    // ui界面不能够修改
    ui->spinBox_loop->setEnabled(false);
    ui->spinBox_loopTimes->setEnabled(false);
    //计数为0
    mSlecetRowNumber = 0;
    ui->spinBox_loopTimes->setValue(0);
    //一条指令链循环个个数
    quint64 oneLianNumber =0;
    QListWidgetItem *currentItem = ui->listWidget->currentItem();
    if(currentItem!=nullptr){
        QStringList fullData = currentItem->data(Qt::UserRole).toStringList();
        oneLianNumber+= fullData.size();
    }
    //发送选中的那行数据
    QVector<SendData>oneHangVector;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item!=nullptr){
            if (!item->isSelected())
                continue;
            QStringList fullData = item->data(Qt::UserRole).toStringList();

            for(int index=0;index<fullData.size();++index){
                SendData currentData;
                //获取发送的内容
                quint64 nextIndex = index+1;
                currentData.pacageIndex = nextIndex;
                currentData.isSpecialPackage = true;
                currentData.sigleFlag = true;
                currentData.oneLianNumber = oneLianNumber;
                auto ptr = mSplitCmdToSendData(fullData.at(index),currentData);
                oneHangVector.push_back(ptr);
            }
        }

    }
    mOneRowYeVector = oneHangVector;
    // 吧一行的数据，推送到发送线程
    if(nullptr!=canthread->mGetThread()){
        if(mOneRowYeVector.size()<=0){
            return;
        }
        canthread->mGetThread()->sendSelectRowData(oneHangVector);
    }
}

void MainWindow::stopSendCommandSlot()
{

    // ui界面能够修改
    ui->spinBox_loop->setEnabled(true);
    ui->spinBox_loopTimes->setEnabled(true);
    mLoopStop = true;
    //清空队列
    canthread->mGetThread()->clearSendQue();
    //设置停止
    canthread->mGetThread()->stop();




}
