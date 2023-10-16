#include "canthread.h"
#include "ControlCAN.h"
#include <QTime>
#include <QCoreApplication>
#include <QMetaType>
#include <string.h>
#include <QUuid>
#include <QTimer>
#include "qtlog/qtlog.h"
CANThread::CANThread()
{
    qRegisterMetaType<std::shared_ptr<SendData>>("std::shared_ptr<SendData>");

    stopped = false;
    //发送帧线程
    mSendThread=new SendThread(this);


    mSendThread->start();

}

CANThread::~CANThread()
{
   mSendThread->stop();
   mSendThread->wait();
}

void CANThread::stop()
{
    stopped = true;
}


//1.打开设备
bool CANThread::openDevice(unsigned int deviceType,unsigned int debicIndex,unsigned int baundRate)
{
    m_deviceType = deviceType;/* USBCAN-2A或USBCAN-2C或CANalyst-II */
    m_debicIndex = debicIndex;/* 第1个设备 */
    m_baundRate = baundRate;
    unsigned int dwRel;
    dwRel = VCI_OpenDevice(m_deviceType, m_debicIndex, 0);
    if(dwRel != 1)
        return false;
    else
        qDebug()<<"open success";
    return true;
}

//2.初始化CAN
bool CANThread::initCAN()
{
    unsigned int dwRel = VCI_ClearBuffer(m_deviceType, m_debicIndex, 0);
    dwRel = VCI_ClearBuffer(m_deviceType, m_debicIndex, 1);
    VCI_INIT_CONFIG vic;
    vic.AccCode=0x80000008;
    vic.AccMask=0xFFFFFFFF;
    vic.Filter=1;
    vic.Mode=0;
    switch (m_baundRate) {
    case 10:
        vic.Timing0=0x31;
        vic.Timing1=0x1c;
        break;
    case 20:
        vic.Timing0=0x18;
        vic.Timing1=0x1c;
        break;
    case 40:
        vic.Timing0=0x87;
        vic.Timing1=0xff;
        break;
    case 50:
        vic.Timing0=0x09;
        vic.Timing1=0x1c;
        break;
    case 80:
        vic.Timing0=0x83;
        vic.Timing1=0xff;
        break;
    case 100:
        vic.Timing0=0x04;
        vic.Timing1=0x1c;
        break;
    case 125:
        vic.Timing0=0x03;
        vic.Timing1=0x1c;
        break;
    case 200:
        vic.Timing0=0x81;
        vic.Timing1=0xfa;
        break;
    case 250:
        vic.Timing0=0x01;
        vic.Timing1=0x1c;
        break;
    case 400:
        vic.Timing0=0x80;
        vic.Timing1=0xfa;
        break;
    case 500:
        vic.Timing0=0x00;
        vic.Timing1=0x1c;
        break;
    case 666:
        vic.Timing0=0x80;
        vic.Timing1=0xb6;
        break;
    case 800:
        vic.Timing0=0x00;
        vic.Timing1=0x16;
        break;
    case 1000:
        vic.Timing0=0x00;
        vic.Timing1=0x14;
        break;
    case 33:
        vic.Timing0=0x09;
        vic.Timing1=0x6f;
        break;
    case 66:
        vic.Timing0=0x04;
        vic.Timing1=0x6f;
        break;
    case 83:
        vic.Timing0=0x03;
        vic.Timing1=0x6f;
        break;
    default:
        break;
    }
    dwRel = VCI_InitCAN(m_deviceType, m_debicIndex, 0, &vic);
    dwRel = VCI_InitCAN(m_deviceType, m_debicIndex, 1, &vic);
    if(dwRel !=1)
        return false;
    else
        qDebug()<<"init success";

    VCI_BOARD_INFO vbi;
    dwRel = VCI_ReadBoardInfo(m_deviceType, m_debicIndex, &vbi);
    if(dwRel != 1)
        return false;
    else
        emit boardInfo(vbi);
    return true;
}

//3.启动CAN
bool CANThread::startCAN()
{
    if(VCI_StartCAN(m_deviceType, m_debicIndex, 0) !=1)
    {
        qDebug()<<"start 0 fail.";
        return false;
    }
    else
        qDebug()<<"start 0 success.";
    if(VCI_StartCAN(m_deviceType, m_debicIndex, 1) !=1)
    {
        qDebug()<<"start 1 fail.";
        return false;
    }
    else
        qDebug()<<"start 1 success.";
    return true;
}

//5.关闭设备
bool CANThread::closeDevice()
{
    unsigned int dwRel;
    dwRel =VCI_CloseDevice(m_deviceType, m_debicIndex);


    if(dwRel != 1)
        return false;
    else
        qDebug()<<"close device failed";
    return true;
}

//0.复位设备，  复位后回到3
bool CANThread::reSetCAN()
{
    if(VCI_ResetCAN(m_deviceType, m_debicIndex, 0) !=1)
    {
        qDebug()<<"reset 0 fail.";
        return false;
    }
    else
        qDebug()<<"reset 0 success.";
    if(VCI_ResetCAN(m_deviceType, m_debicIndex, 1) !=1)
    {
        qDebug()<<"reset 1 fail.";
        return false;
    }
    else
        qDebug()<<"reset 1 success.";
    return true;
}

void CANThread::run()
{
    while(!stopped)
    {
        unsigned int dwRel;
        VCI_CAN_OBJ vco[2500];
        dwRel = VCI_Receive(m_deviceType, m_debicIndex, 0, vco,2500,0);
        if(dwRel > 0)
            emit getProtocolData(vco,dwRel,0);
        dwRel = VCI_Receive(m_deviceType, m_debicIndex, 1, vco,2500,0);
        if(dwRel > 0)
            emit getProtocolData(vco,dwRel,1);
        sleep(30);
    }
    stopped = false;
}
void CANThread::sleep(int msec)
{
   QTime dieTime = QTime::currentTime().addMSecs(msec);
   while( QTime::currentTime() < dieTime )
       QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
