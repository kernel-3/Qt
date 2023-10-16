#ifndef MACRO_H
#define MACRO_H
#include <QString>
#include <QMetaType>
#include <queue>
#include <memory>
//有时间在优化类型，暂定QString ??todo
#include "ControlCAN.h"
struct CANFrame
{
    QString TimeStamp ; //系统时间
    QString Bus  ;//CAN通道
    QString Direction ; //传输方向 0发送 1-接收
    QString FrameId;//< ID号
    QString Data ; // 数据
    QString TimeIdenty; //时间标识（隐藏）
    QString TimeIdentyS ;//时间标识S（隐藏）
    QString FrameType ;//帧类型（隐藏）"远程帧" : "数据帧" RemoteFlag
    QString FrameGeShi;//帧格式（隐藏） "扩展帧" : "标准帧"  ExternFlag
    QString Length; //帧长度（隐藏）
};
struct SendData
{

    unsigned int DeviceType;//4
    unsigned int DeviceInd;//通道0 或者1
    unsigned int CANInd;
    std::shared_ptr<VCI_CAN_OBJ> pSend;//发送的真实数据
    unsigned char remoteFlag;/*是否是远程帧。=0时为为数据帧，=1时为远程帧*/
    unsigned char externFlag;/*标准帧，不是扩展帧*/
    unsigned char dataArray[8];
     unsigned int dataDlc;
    unsigned long Len;
    QString uuid;
    QString comStr;//指令
    QString comSynStr;//指令序号
    QString dataStr;//数据
    int duration;//间隔
    QString respStr;
    bool success;
    bool bloop;
    //songjingguo
    //是否为特殊包
    bool isSpecialPackage;
    //发送单个处理的包
    bool sigleFlag;
    /*循环次数*/
    quint64 circleNumber;
    /*指令个数*/
    quint64 orderNumber;
    /*当前指令索引*/
    quint64 orderIndex;
    /*一条指令链循环次数*/
    unsigned int oneLianNumber;
    /*指令id*/
    QString pacakeIdStr;
    /**包计数，处理指令链 从0-1----递增*****/
    quint64 pacageIndex;
};
#endif // MACRO_H
