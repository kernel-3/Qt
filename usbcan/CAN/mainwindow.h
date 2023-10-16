#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canthread.h"
#include <QComboBox>
#include <QMainWindow>
#include <QMutex>
#include <QEventLoop>
#include <QTimer>
#include "SLT/canframemodel.h"
namespace Ui
{
class MainWindow;
}

class QListWidgetItem;
class QKeyEvent;
class AddCommandDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
    //初始化信号与槽
    void initSignalAndSlot();
    //发送数据
    void sendData(const SendData&data);

protected:
    void keyPressEvent(QKeyEvent *event);
private:

    //打开设备失败的时候，设置只有通道commbox可用，其他都是灰色不可用
    void setNotEnableExpectChannelCombox(bool flag);
    CANFrameModel *model;
    /************csv测试*******************/
    QString sendCsvPath;
    QString receiveCsvPath;
    //半个小时清空下内存
    QTimer *timer;
private slots:
    //清空下内存
    void mClearMemorySlot();
    //获取接收can帧
    void onGetProtocolData(VCI_CAN_OBJ *vci, unsigned int dwRel, unsigned int channel);
    //读取板块信息
    void onBoardInfo(VCI_BOARD_INFO vbi);
    /**总的打开设备接口******************/
    void allDeviceOpenSlot();
    bool deviceOpen();
    bool deviceClose();
    //初始化can
    bool canInit();
    //启动CAN
    bool canStart();
    //发送命令
    void sendBtnClickedSlot();
    //清空ModelView数据
    void clearModelDataSlot();
    //发送选择项************ssssssssssss*************************
    void sendSelectItemSlot();
    //显示发送复选框选择
    void sendCheckSlot(bool isChecked);
    //显示接收复选框选择
    void receiveCheckSlot(bool isChecked);
    //id过滤
    void idFilterSlot(const QString &IdChanged);
    //+号
    void addOneOrderSlot();
    //-号
    void reduceOneSlot();
    //停止指令链循环，按下停止按钮
    void stopSendCommandSlot();
    //发送指令链
    void sendCommandListSlot();
    //分离命令赋值到结构
    SendData mSplitCmdToSendData(const QString &cmd,SendData&valueData);
    //刷新新的指令
    void refreshOrderSlot();
    //读取指令连文件
    void readOrderFileSlot();
    //保存指令链文件
    void saveOrderFileSlot();
    //清空指令链列表
    void clearOrderListSlot();
    //保存指令链列表
    void saveOrderListSlot();

    void addCommand();
    void dealAddDialogTest(AddCommandDialog *dlg);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_comboBox_commandList_activated(const QString &arg1);
    //wwc 发送命令在多条的时候使用异步
    void slot_send_res(std::shared_ptr<SendData> sendData, bool result);
    //指令链
    void slot_send_cmdLine_res(SendData sendData, bool result);
    //选择指定项
    void slot_selectRow_cmdLine_res(SendData sendData, bool result);
    //显示到界面
    void modelShowFunction(SendData sendData);
private:
    void toUChar2(quint16 num, quint8 *bytes);
    void toUChar4(quint32 num, quint8 *bytes);
    void qwait(qint64 ms);

private:
    void readJson();
    void readCommandList();
    void builtComboBox(QComboBox *box, const QJsonArray &jsonArr);

    //初始化model view
    void initModelView();
    //发送消息**
    void sendCommand(QStringList commandSplit, bool bloop = false);


    //窗体的基本操作
    void saveWindow();
    void restoreWindow();
    QString saveDir();
    void setSaveDir(QString dir);
private:
    Ui::MainWindow *ui;
    CANThread *canthread;
    QHash<QString,QByteArray> mCommandMap;
    QMutex mLock;
    bool mLoopStop=false;
    //一页数据
    QVector<SendData>mOneYeVector;
    //一行数据
    QVector<SendData>mOneRowYeVector;
    //指令链个数
    quint64 mSpeCialCmdLineNumber=0;
    //选择项个数
    quint64 mSlecetRowNumber =0;
};

#endif  // MAINWINDOW_H
