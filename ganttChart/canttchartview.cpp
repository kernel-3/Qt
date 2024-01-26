#include "canttchartview.h"
#include "canttchartscene.h"

#include <QWheelEvent>

CanttChartView::CanttChartView(QWidget *parent) : QGraphicsView(parent)
{
    m_pScene = new CanttChartScene(this);
    setScene(m_pScene);

    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    centerOn(0, 0);
}

void CanttChartView::setAxisRange(const QDateTime &start, const QDateTime &end, const QStringList &platforms)
{
    m_pScene->setAxisRange(start, end, platforms);
}

CanttTimeBarItem *CanttChartView::addPlanTimeBar(const QString &platform, const QDateTime &start, const QDateTime &end)
{
    return m_pScene->addPlanTimeBar(platform, start, end);
}

CanttTimeBarItem *CanttChartView::addRealTimeBar(const QString &platform, const QDateTime &start, const QDateTime &end)
{
    return m_pScene->addRealTimeBar(platform, start, end);
}

void CanttChartView::setStepTimeValue(const QTime &time)
{
    m_pScene->setStepTimeValue(time);
}

void CanttChartView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
    {
        zoomOut();
    }
    else
    {
        zoomIn();
    };
}

void CanttChartView::zoomIn()
{
    scaleBy(1.1);
}

void CanttChartView::zoomOut()
{
    scaleBy(1.0 / 1.1);
}

void CanttChartView::scaleBy(double factor)
{
    scale(factor, factor);
}
