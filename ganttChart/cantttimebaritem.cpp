#include "cantttimebaritem.h"
#include "definition.h"

#include <QBrush>
#include <QPen>
#include <QCursor>
#include <QPoint>
#include <QLabel>
#include <QGraphicsProxyWidget>

const int eventItemYOffset = 2;

CanttTimeBarItem::CanttTimeBarItem(const QDateTime& start, const QDateTime& end, TimeType type, double factor)
	: QGraphicsRectItem(nullptr),
	m_pFactor(factor),
	m_startDateTime(start),
	m_endDateTime(end)
{
	double width = (end.toMSecsSinceEpoch() - start.toMSecsSinceEpoch()) / m_pFactor;

	setRect(0, 0, width, canttTimeBarHeight);
	setCursor(QCursor(Qt::PointingHandCursor));

	if (CanttTimeBarItem::PlanTime == type)
	{
		setBrush(QBrush(QColor(92, 201, 221)));
	}
	else
	{
		setBrush(QBrush(QColor(233, 252, 74)));
	}

	QPen pen;
	pen.setStyle(Qt::NoPen);
	setPen(pen);
}

void CanttTimeBarItem::addEvent(const QDateTime& dateTime, CanttTimeBarItem::EventType type)
{
	if (dateTime < m_startDateTime || dateTime > m_endDateTime)
	{
		return;
	}

	QGraphicsItem* item = createEventItem(type);

	double x = (dateTime.toMSecsSinceEpoch() - m_startDateTime.toMSecsSinceEpoch()) / m_pFactor;

	item->setPos(x, eventItemYOffset);
}

QGraphicsItem* CanttTimeBarItem::createEventItem(CanttTimeBarItem::EventType type)
{
	QLabel* label = new QLabel;
	label->setStyleSheet("QLabel {"
		"background-color: transparent;"
		"min-height: 12px;"
		"max-height: 12px;"
		"font-size: 11px;"
		"padding-left: -2px;"
		"border-width: 0 0 0 12;"
		"border-image: url(:/img/event/takeoff.png) 0 0 0 64;}");
	label->setToolTip(QStringLiteral("开始起飞\n人员：张三\n地点：xxx根据地"));

	switch (type)
	{
	case CanttTimeBarItem::TakeoffEvent:
		label->setText(QStringLiteral("起飞"));
		break;
	case CanttTimeBarItem::RotationEvent:
		label->setText(QStringLiteral("转角"));
		break;
	case CanttTimeBarItem::SwitchChannelEvent:
		label->setText(QStringLiteral("切换频道"));
		break;
	case CanttTimeBarItem::LandEvent:
		label->setText(QStringLiteral("降落"));
		break;
	default:
		break;
	}

	QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget(this);
	proxy->setWidget(label);

	return proxy;
}
