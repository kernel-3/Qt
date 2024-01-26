#include "canttchartscene.h"
#include "definition.h"
#include "cantttimebaritem.h"

#include <QBrush>
#include <QPen>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QCheckBox>
#include <QGraphicsProxyWidget>
#include <QCursor>

const int firstHorizantalGridWidth = 100;
const int horizontalGridWidth = 40;
const int verticalGridHeight = 40;
const int horizontalAxisTextHeight = 21;
const int horizontalAxisTextOffset = 5;
const QPoint axisStartPoint = QPoint(20, 40);
const QPoint platformHeaderOffset = QPoint(6, 10);
const QColor gridLineColor = QColor(48, 85, 93);
const QColor scaleDateColor = QColor(253, 201, 115);
const QColor scaleTimeColor = QColor(208, 216, 237);

CanttChartScene::CanttChartScene(QObject* parent) : QGraphicsScene(parent),
m_rowCount(0), m_columnCount(0), m_stepTimeValue(0, 0, 1)
{
	setBackgroundBrush(QBrush(QColor(43, 48, 54)));

	m_perPixelHMsecs = m_stepTimeValue.msecsSinceStartOfDay() / (double)horizontalGridWidth;
}

void CanttChartScene::setAxisRange(const QDateTime& start, const QDateTime& end, const QStringList& platforms)
{
	if (start >= end || 0 == platforms.count())
	{
		return;
	}

	m_rowCount = platforms.count();
	m_startDateTime = start;
	m_endDateTime = end;
	m_platforms = platforms;
	m_firstTimeBarStartX = axisStartPoint.x() + firstHorizantalGridWidth;
	m_firstTimeBarStartY = axisStartPoint.y();

	//清空现有图形项
	clear();

	//绘制前先预留足够空间
	double sceneMiniWidth = m_firstTimeBarStartX + horizontalGridWidth
		+ (end.toMSecsSinceEpoch() - start.toMSecsSinceEpoch()) / m_perPixelHMsecs;
	double sceneMiniHeight = m_firstTimeBarStartY + platforms.count() * verticalGridHeight;

	setSceneRect(0, 0, sceneMiniWidth, sceneMiniHeight + 1000);

	drawVerticalAxis(platforms);

	QDateTime startDateTime = start;
	QDate startDate = start.date();

	double x = m_firstTimeBarStartX;
	int z = 0;
	for (; x <= sceneMiniWidth; x += horizontalGridWidth)
	{
		QGraphicsTextItem* timeItem = new QGraphicsTextItem(startDateTime.toString("mm:ss"));
		//QGraphicsTextItem* timeItem = new QGraphicsTextItem(QString::number(z++));
		timeItem->setDefaultTextColor(scaleTimeColor);
		timeItem->setZValue(std::numeric_limits<int>::min());
		timeItem->setPos(x - horizontalAxisTextOffset, axisStartPoint.y() - horizontalAxisTextHeight);
		addItem(timeItem);

		if (x == axisStartPoint.x() + firstHorizantalGridWidth)
		{
			QGraphicsTextItem* dateItem = new QGraphicsTextItem(startDateTime.toString("hh:mm"));
			dateItem->setDefaultTextColor(scaleDateColor);
			dateItem->setZValue(std::numeric_limits<int>::min());
			addItem(dateItem);
			dateItem->setPos(x - horizontalAxisTextOffset, axisStartPoint.y() - horizontalAxisTextHeight * 2);
		}
		else
		{
			if (startDateTime.date() > startDate)
			{
				QGraphicsTextItem* dateItem = new QGraphicsTextItem(startDateTime.toString("hh:mm"));
				dateItem->setDefaultTextColor(scaleDateColor);
				dateItem->setZValue(std::numeric_limits<int>::min());
				addItem(dateItem);
				dateItem->setPos(x - horizontalAxisTextOffset, axisStartPoint.y() - horizontalAxisTextHeight * 2);
				startDate = startDateTime.date();
			}
		}

		startDateTime = startDateTime.addMSecs(m_stepTimeValue.msecsSinceStartOfDay());

		m_columnCount++;

		if (startDateTime > QDateTime::currentDateTime())
		{
			break;
		}
	}

	drawGridLines();

	QRectF rect = this->sceneRect();
	setSceneRect(0, 0, rect.width() + 200, rect.height() + 200);
}

void CanttChartScene::drawVerticalAxis(const QStringList& platforms)
{
	if (platforms.count() == 0)
	{
		return;
	}

	const double maxY = this->height();

	//绘制垂直表头
	int index = 0;
	for (double y = axisStartPoint.y(); y <= maxY; y += verticalGridHeight)
	{
		if (index > platforms.count() - 1)
		{
			break;
		}

		QCheckBox* box = new QCheckBox;
		box->setObjectName("PlatformCheckBox");
		box->setStyleSheet("#PlatformCheckBox {"
			"color: rgb(205, 218, 235);"
			"background-color: rgb(43, 48, 54);"
			"}"
			"#PlatformCheckBox::indicator:unchecked {"
			"border-image: url(:/img/checkbox/timebar-show.png) 0 0 0 0 stretch;"
			"}"
			"#PlatformCheckBox::indicator:checked {"
			"border-image: url(:/img/checkbox/timebar-hide.png) 0 0 0 0 stretch;"
			"}");
		connect(box, &QCheckBox::clicked, [=](bool checked) {
			auto list = m_plaformTimeBarHash.values(box->text());

			if (checked)
			{
				foreach(QGraphicsItem * item, list)
				{
					item->hide();
				}
			}
			else
			{
				foreach(QGraphicsItem * item, list)
				{
					item->show();
				}
			}
			});
		box->setText(platforms.at(index));
		QGraphicsProxyWidget* proxy = addWidget(box);
		proxy->setCursor(QCursor(Qt::PointingHandCursor));
		proxy->setPos(QPoint(axisStartPoint.x(), y) + platformHeaderOffset);
		m_platformStartYHash.insert(platforms.at(index), y);
		index++;
	}
}

CanttTimeBarItem* CanttChartScene::addPlanTimeBar(const QString& platform, const QDateTime& start, const QDateTime& end)
{
	if (!m_platformStartYHash.keys().contains(platform))
	{
		return nullptr;
	}

	//添加到缓存
	auto pair = qMakePair(start, end);
	m_planTimeBarTemp.insert(platform, pair);


	//绘制时间条图形项
	CanttTimeBarItem* item = new CanttTimeBarItem(start, end, CanttTimeBarItem::PlanTime, m_perPixelHMsecs);

	double x = m_firstTimeBarStartX + (start.toMSecsSinceEpoch() - m_startDateTime.toMSecsSinceEpoch()) / m_perPixelHMsecs;
	double y = m_platformStartYHash.value(platform) + 3;

	addItem(item);
	item->setPos(x, y);

	m_plaformTimeBarHash.insert(platform, item);

	return item;
}

CanttTimeBarItem* CanttChartScene::addRealTimeBar(const QString& platform, const QDateTime& start, const QDateTime& end)
{
	if (!m_platformStartYHash.keys().contains(platform))
	{
		return nullptr;
	}

	//添加到缓存
	auto pair = qMakePair(start, end);
	m_realTimeBarTemp.insert(platform, pair);


	//绘制时间条图形项
	CanttTimeBarItem* item = new CanttTimeBarItem(start, end, CanttTimeBarItem::RealTime, m_perPixelHMsecs);

	double x = m_firstTimeBarStartX + (start.toMSecsSinceEpoch() - m_startDateTime.toMSecsSinceEpoch()) / m_perPixelHMsecs;
	double y = m_platformStartYHash.value(platform) + canttTimeBarHeight + 6;

	addItem(item);
	item->setPos(x, y);

	m_plaformTimeBarHash.insert(platform, item);

	return item;
}

void CanttChartScene::setStepTimeValue(const QTime& time)
{
	m_stepTimeValue = time;
	m_perPixelHMsecs = m_stepTimeValue.msecsSinceStartOfDay() / (double)horizontalGridWidth;

#if 0

	//时间步长更新后需要更新坐标轴
	if (m_startDateTime.isNull() || m_endDateTime.isNull() || 0 == m_platforms.count())
	{
		return;
	}
	setAxisRange(m_startDateTime, m_endDateTime, m_platforms);
#endif

}

void CanttChartScene::drawGridLines()
{
	const double maxY = this->height();
	const double maxX = m_firstTimeBarStartX + (m_columnCount + 50) * horizontalGridWidth;

	//绘制第一条水平网格线
	QGraphicsLineItem* item = new QGraphicsLineItem(axisStartPoint.x(), axisStartPoint.y(), axisStartPoint.x(), maxY);
	item->setPen(QPen(gridLineColor));
	item->setZValue(std::numeric_limits<int>::min());
	addItem(item);

	//绘制水平网格线
	for (double x = axisStartPoint.x() + firstHorizantalGridWidth; x <= maxX; x += horizontalGridWidth)
	{
		QGraphicsLineItem* item = new QGraphicsLineItem(x, axisStartPoint.y(), x, maxY);
		item->setPen(QPen(gridLineColor));
		item->setZValue(std::numeric_limits<int>::min());
		addItem(item);
	}

	//绘制垂直网格线
	for (double y = axisStartPoint.y(); y <= maxY; y += verticalGridHeight)
	{
		QGraphicsLineItem* item = new QGraphicsLineItem(axisStartPoint.x(), y, maxX, y);
		item->setPen(QPen(gridLineColor));
		item->setZValue(std::numeric_limits<int>::min());
		addItem(item);
	}
}

