#include "canframemodel.h"

CANFrameModel::CANFrameModel(QObject *parent):
    QAbstractTableModel(parent)
{
    int maxFramesDefault;
    if (QSysInfo::WordSize > 32)
    {
        qDebug() << "64位系统需要大的分配";
        maxFramesDefault = 10000000;
    }
    else
    {
        qDebug() << "32位系统，需要多考虑";
        maxFramesDefault = 2000000;
    }

    preallocSize = maxFramesDefault;
    frames.reserve(preallocSize);
    filteredFrames.reserve(preallocSize);
    lastUpdateNumFrames = 0;

}
void CANFrameModel::addFrames(const QVector<QSharedPointer<CANFrame>>&pFrames)
{
    if(frames.length() > frames.capacity() * 0.99)
    {
        mutex.lock();
        qDebug() << "Frames count: " << frames.length() << " of " << frames.capacity() << " capacity, removing first " << (int)(frames.capacity() * 0.05) << " frames";
        frames.remove(0, (int)(frames.capacity() * 0.05));
        qDebug() << "Frames removed, new count: " << frames.length();
        mutex.unlock();
    }

    if(filteredFrames.length() > filteredFrames.capacity() * 0.99)
    {
        mutex.lock();
        qDebug() << "filteredFrames count: " << filteredFrames.length() << " of " << filteredFrames.capacity() << " capacity, removing first " << (int)(filteredFrames.capacity() * 0.05) << " frames";
        filteredFrames.remove(0, (int)(filteredFrames.capacity() * 0.05));
        qDebug() << "filteredFrames removed, new count: " << filteredFrames.length();
        mutex.unlock();
    }

    foreach(const auto& frame, pFrames)
    {
        addFrame(frame);
    }

}
//处理最大数目添加数目
void CANFrameModel::dealAddFrame(const QSharedPointer<CANFrame>& frame)
{
    int framesNumber = frames.size();
    if(framesNumber>maxReceiveMaxNumber){
        //上移动
        QVector<QSharedPointer<CANFrame>>tempFrameVector;
        for(int i=1;i<frames.size();++i){
            tempFrameVector.append(frames.at(i));
        }
        tempFrameVector.append(frame);
        beginResetModel();
        frames = tempFrameVector;
        endResetModel();


    }else{
        frames.append(frame);
    }

    int flterframesNumber = filteredFrames.size();
    if(flterframesNumber>maxReceiveMaxNumber){
        //上移动
        QVector<QSharedPointer<CANFrame>>tempFrameVector;
        for(int i=1;i<filteredFrames.size();++i){
            tempFrameVector.append(filteredFrames.at(i));
        }

        tempFrameVector.append(frame);
        beginResetModel();
        filteredFrames = tempFrameVector;
        endResetModel();



    }else{

        beginInsertRows(QModelIndex(), filteredFrames.count(), filteredFrames.count());
        filteredFrames.append(frame);
        endInsertRows();
    }
}
void CANFrameModel::addFrame(const QSharedPointer<CANFrame>& frame)
{
    /*TODO: remove mutex */
    mutex.lock();
    lastUpdateNumFrames++;
    dealAddFrame(frame);
    //    frames.append(frame);
    //    beginInsertRows(QModelIndex(), filteredFrames.count(), filteredFrames.count());
    //    filteredFrames.append(frame);
    //    endInsertRows();
    mutex.unlock();
    //qDebug()<<"添加一条帧数据!!";
}

//发送帧或者接收帧
void CANFrameModel::sendFrameCheckedSlot(int unCheck)
{
    if(0 == unCheck){
        sendFrameShowFlag = false;
    }else {
        //复选上了
        sendFrameShowFlag  = true;
    }
    sendRefresh();
}
void CANFrameModel::receiveFrameCheckedSlot(int unCheck)
{
    if(0 == unCheck){
        revieveFrameShowFlag = false;
    }else {
        //复选上了
        revieveFrameShowFlag  = true;
    }
    sendRefresh();
}
//ID过滤
void CANFrameModel::iDComBOxChangedFlilterSlot(int value)
{
    iDFlagFliter = value;
    sendRefresh();
}
//指令序号过滤
void CANFrameModel::orderComBOxChangedFlilterSlot(int value)
{
    orderFlagFliter = value;
}
int CANFrameModel::rowCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    if (filteredFrames.data())
    {
        int rows = filteredFrames.count();
        return rows;
    }
    return 0;
}
QVariant CANFrameModel::data(const QModelIndex &index, int role) const
{
    QString tempString;
    QSharedPointer<CANFrame> thisFrame;
    QVariant ts;
    if (!index.isValid())
        return QVariant();

    if (index.row() >= (filteredFrames.count()))
        return QVariant();
    thisFrame = filteredFrames.at(index.row());
    if (role == Qt::BackgroundRole)
    {
        //发送帧设置背景色
        if(0 == thisFrame.get()->Direction.toInt()){
            return QColor(Qt::darkGray);
        }else{
            return QApplication::palette().color(QPalette::Base);

        }

    }

    if (role == Qt::TextAlignmentRole)
    {
        switch(Column(index.column()))
        {
        case Column::index:
        case Column::TimeStamp:
        case Column::Bus:
        case Column::Direction:
        case Column::FrameId:
        case Column::Data:
        case Column::TimeIdenty:
        case Column::TimeIdentyS:
        case Column::FrameType:
        case Column::FrameGeShi:
        case Column::Length:
            return Qt::AlignHCenter;
        default:
            return Qt::AlignLeft;
        }
    }

    if (role == Qt::ForegroundRole)
    {
        //??todo
        return QApplication::palette().color(QPalette::WindowText);
    }

    if (role == Qt::DisplayRole) {
        //??todo重点要去优化的
        switch (Column(index.column()))
        {
        case Column::index:
            return index.row();
        case Column::TimeStamp:
            return thisFrame.get()->TimeStamp;
        case Column::Bus:
            return thisFrame.get()->Bus;
        case Column::Direction:
            if(thisFrame.get()->Direction==QString("0")){
                return QString("发送");
            }else if(thisFrame.get()->Direction==QString("1")){
                return QString("接收");
            }
        case Column::FrameId:
            return thisFrame.get()->FrameId;
        case Column::Data:
            return thisFrame.get()->Data;
        case Column::TimeIdenty:
            return thisFrame.get()->TimeIdenty;
        case Column::TimeIdentyS:
            return thisFrame.get()->TimeIdentyS;
        case Column::FrameType:
            return thisFrame.get()->FrameType;
        case Column::FrameGeShi:
            return thisFrame.get()->FrameGeShi;
        case Column::Length:
            return thisFrame.get()->Length;

        default:
            return tempString;
        }
    }
    return QVariant();
}
QVariant CANFrameModel::headerData(int section, Qt::Orientation orientation,
                                   int role ) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (Column(section))
        {
        case Column::index:
            return QString(tr("索引"));
        case Column::TimeStamp:
            return QString(tr("系统时间"));
        case Column::Bus:
            return QString(tr("CAN通道"));
        case Column::Direction:
            return QString(tr("传输方向"));
        case Column::FrameId:
            return QString(tr("ID号"));
        case Column::Data:
            return QString(tr("数据"));
        case Column::TimeIdenty:
            return QString(tr("时间标识"));
        case Column::TimeIdentyS:
            return QString(tr("时间标识S"));
        case Column::FrameType:
            return QString(tr("帧类型"));
        case Column::FrameGeShi:
            return QString(tr("帧格式"));
        case Column::Length:
            return QString(tr("帧长度"));
        default:
            return QString("");
        }
    }
    else
        return QString::number(section + 1);
    return QVariant();
}
int CANFrameModel::columnCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return (int)Column::NUM_COLUMN;
}
int CANFrameModel::totalFrameCount()
{
    int count;
    count = frames.count();
    return count;
}
CANFrameModel::~CANFrameModel()
{
    frames.clear();
    filteredFrames.clear();
}
//0-不过滤，1-仅接收 2-不接收
void CANFrameModel::helperAddFrameByFilter(QVector<QSharedPointer<CANFrame>>&containter,
                                           int frametype/*发送帧or接收帧0发送 1-接收*/,int byFilter)
{

    int count = frames.count();
    bool ok;
    for (int i = 0; i < count; i++){
        //接收帧与发送帧都显示
        if(frametype == 3){
            if(0==byFilter){
                containter.append(frames[i]);
            }else if(1 == byFilter){
                if(frames[i].get()->FrameId.toInt(&ok,16) == filterID){
                    containter.append(frames[i]);
                }
            }else if(2==byFilter){
                if(frames[i].get()->FrameId.toInt(&ok,16) != filterID){
                    containter.append(frames[i]);
                }
            }
        }else{
            //ID过滤0-不过滤，1-仅接收 2-不接收
            if(frametype == frames[i].get()->Direction.toInt(&ok,10)){
                if(0==byFilter){
                    containter.append(frames[i]);
                }else if(1 == byFilter){
                    if(frames[i].get()->FrameId.toInt(&ok,10) == filterID){
                        containter.append(frames[i]);
                    }
                }else if(2==byFilter){
                    if(frames[i].get()->FrameId.toInt(&ok,10) != filterID){
                        containter.append(frames[i]);
                    }
                }
            }
        }
    }

}
//大面积刷新
void CANFrameModel::sendRefresh()
{
    //qDebug() << "界面大规模刷新";
    //qDebug()<<"sendFrame is check??"<<sendFrameShowFlag<<"  receiveFram is check??"<<revieveFrameShowFlag;
    //接收帧与发送帧都没有复选
    if((false == sendFrameShowFlag) &&(false == revieveFrameShowFlag)){
        filteredFrames.clear();
        filteredFrames.reserve(preallocSize);
        mutex.lock();
        beginResetModel();
        lastUpdateNumFrames = 0;
        endResetModel();
        mutex.unlock();
    }
    QVector<QSharedPointer<CANFrame>> tempContainer;
    //接收帧与发送帧都复选上了
    if((true == sendFrameShowFlag) &&(true == revieveFrameShowFlag)){
        helperAddFrameByFilter(tempContainer,3,iDFlagFliter);
        mutex.lock();
        beginResetModel();
        filteredFrames.clear();
        filteredFrames.append(tempContainer);
        filteredFrames.reserve(preallocSize);
        lastUpdateNumFrames = 0;
        endResetModel();
        mutex.unlock();
    }
    /*发送帧*/
    if((true == sendFrameShowFlag) &&(false == revieveFrameShowFlag)){
        helperAddFrameByFilter(tempContainer,0,iDFlagFliter);
        mutex.lock();
        beginResetModel();
        filteredFrames.clear();
        filteredFrames.append(tempContainer);
        filteredFrames.reserve(preallocSize);
        lastUpdateNumFrames = 0;
        endResetModel();
        mutex.unlock();
    }
    //接收帧
    if((false == sendFrameShowFlag) &&(true == revieveFrameShowFlag)){
        helperAddFrameByFilter(tempContainer,1,iDFlagFliter);
        mutex.lock();
        beginResetModel();
        filteredFrames.clear();
        filteredFrames.append(tempContainer);
        filteredFrames.reserve(preallocSize);
        lastUpdateNumFrames = 0;
        endResetModel();
        mutex.unlock();
    }




}
void CANFrameModel::clearFrames()
{
    mutex.lock();
    this->beginResetModel();
    frames.clear();
    filteredFrames.clear();

    frames.shrink_to_fit();
    filteredFrames.shrink_to_fit();

    QVector<QSharedPointer<CANFrame>>().swap(frames);
    QVector<QSharedPointer<CANFrame>>().swap(filteredFrames);


    frames.reserve(preallocSize);
    filteredFrames.reserve(preallocSize);
    this->endResetModel();
    lastUpdateNumFrames = 0;
    mutex.unlock();

    // emit updatedFiltersList();
}
