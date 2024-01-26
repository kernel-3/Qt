#ifndef CANTTTIMEBARITEM_H
#define CANTTTIMEBARITEM_H

#include <QGraphicsRectItem>
#include <QDateTime>
#include "definition.h"

class CanttTimeBarItem : public QGraphicsRectItem
{
public:
    enum {Type = canttTimeBarType};
    enum TimeType {
        PlanTime,
        RealTime
    };
    enum EventType {
        TakeoffEvent,
        RotationEvent,
        SwitchChannelEvent,
        LandEvent
    };

    explicit CanttTimeBarItem(const QDateTime &start, const QDateTime &end, TimeType type, double factor);

    void addEvent(const QDateTime &dateTime, EventType type);

private:
    QGraphicsItem *createEventItem(EventType type);

private:
    double m_pFactor;

    QDateTime m_startDateTime;
    QDateTime m_endDateTime;
};

#endif // CANTTTIMEBARITEM_H
