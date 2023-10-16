#ifndef CANFRAMEMODEL_H
#define CANFRAMEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QList>
#include <QVector>
#include <QDebug>
#include <QMutex>
#include <QApplication>
#include <QPalette>
#include "macro.h"
enum class Column {
    index = 0,//索引
    TimeStamp = 1, //系统时间
    Bus       = 2, //CAN通道
    Direction = 3, //传输方向
    FrameId   = 4, //< ID号
    Data      = 5, // 数据
    TimeIdenty      = 6, //时间标识（隐藏）
    TimeIdentyS =7,//时间标识S（隐藏）
    FrameType =8,//帧类型（隐藏）
    FrameGeShi =9,//帧格式（隐藏）
    Length    = 10, //帧长度（隐藏）
    NUM_COLUMN
};

class CANFrameModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CANFrameModel(QObject *parent = 0);
    virtual ~CANFrameModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    int columnCount(const QModelIndex &) const;
    //获取总的帧数
    int totalFrameCount();
    //大面积刷新??todo
    void sendRefresh();
    void clearFrames();
    //0-不过滤，1-仅接收 2-不接收
    void helperAddFrameByFilter(QVector<QSharedPointer<CANFrame>>&containter,
                                int frametype/*发送帧or接收帧0发送 1-接收*/,
                                int byFilter);
    //设置过滤帧ID
    void setIDFilterValue(int value){filterID = value;}
    //处理最大数目添加数目
    void dealAddFrame(const QSharedPointer<CANFrame>& frame);
private:
    QVector<QSharedPointer<CANFrame>> frames;
    //界面显示的
    QVector<QSharedPointer<CANFrame>> filteredFrames;
    QMutex mutex;
    int lastUpdateNumFrames;
    //预分配大小
    uint32_t preallocSize;
    //发送帧，接收帧 都是(0-隐藏，1-显示)
    bool sendFrameShowFlag =true;
    bool revieveFrameShowFlag =true;
    //ID过滤0-不过滤，1-仅接收 2-不接收
    int iDFlagFliter =0;
    //请求过滤的CANID
    int filterID =-1;
    //指令序号过滤0-不过滤，1-仅接收 2-不接收
    int orderFlagFliter=0;
    //最大数目
    int maxReceiveMaxNumber =10000;
public slots:
    //发送帧或者接收帧
    void sendFrameCheckedSlot(int unCheck);
    void receiveFrameCheckedSlot(int unCheck);
    //ID过滤
    void iDComBOxChangedFlilterSlot(int value);
    //指令序号过滤??todo
    void orderComBOxChangedFlilterSlot(int value);
    /*******************添加数据的接口*******************************/
    void addFrames(const QVector<QSharedPointer<CANFrame>>&);
    void addFrame(const QSharedPointer<CANFrame>& frame);
};

#endif // CANFRAMEMODEL_H
