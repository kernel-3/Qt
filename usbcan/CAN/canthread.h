#ifndef CANTHREAD_H
#define CANTHREAD_H

#include "ControlCAN.h"
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <memory>
#include <mutex>
#include <queue>
#include "dequeadapter.h"
#include "slt/plf_queue.h"
#include "sendthread.h"
#include "slt/macro.h"
#include "qtlog/qtlog.h"
class CANThread : public QThread
{
    Q_OBJECT
public:
    CANThread();
    ~CANThread();
    void stop();
    SendThread *mGetThread(){return  mSendThread;}
    //1.打开设备
    bool openDevice(unsigned int deviceType, unsigned int debicIndex, unsigned int baundRate);

    //2.初始化CAN
    bool initCAN();

    //3.启动CAN
    bool startCAN();
    //5.关闭设备
    bool closeDevice();

    //0.复位设备，  复位后回到3
    bool reSetCAN();

    unsigned int m_deviceType;
    unsigned int m_debicIndex;
    unsigned int m_baundRate;
    unsigned int m_debicCom;

    bool stopped;

signals:
    void getProtocolData(VCI_CAN_OBJ *vci, unsigned int dwRel, unsigned int channel);
    void boardInfo(VCI_BOARD_INFO vbi);



private:
    void run();
    void sleep(int msec);
private:
    SendThread *mSendThread;
};


#endif  // CANTHREAD_H
