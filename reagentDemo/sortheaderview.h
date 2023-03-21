#ifndef SORTHEADERVIEW_H
#define SORTHEADERVIEW_H

#include <QHeaderView>

class SortHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    enum SortOrder
    {
        NoOrder = 0 
        , DescOrder 
        , AscOrder  
    };
public:
    explicit SortHeaderView(Qt::Orientation orientation = Qt::Horizontal,
                            QWidget *parent = nullptr);

    QList<int> getUnsortIndexs() const;
    void setUnsortIndexs(const QList<int> &rowOrColumns);
    void appendUnsortIndex(int rowOrColumn);

protected:
    void showEvent(QShowEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    SortOrder getNextOrder(SortOrder order) const;

signals:
    void sortOrderChanged(int index, SortOrder order);

private:
    // 不进行排序的行列
    QList<int> unsortIndexs;
    //鼠标按下时对应原model index
    int pressLogicIndex = -1;
    //鼠标按下时对应显示的index，可能是交换了位置的
    int pressVisualIndex = -1;
    //上一次点击对应的logic index
    int previousLogicIndex = -1;
    //当前排序状态
    SortOrder sortOrder = NoOrder;
};

#endif // SORTHEADERVIEW_H
