#ifndef DATACHOSSEFORM_H
#define DATACHOSSEFORM_H

#include <QWidget>

namespace Ui {
class DataChosseForm;
}

class QListWidgetItem;
class DataChosseForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataChosseForm(QWidget *parent = nullptr);
    ~DataChosseForm();
public:
    void setDataJson(QJsonObject jsonobj);
signals:
    void paramChossed(QString param);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::DataChosseForm *ui;
};

#endif // DATACHOSSEFORM_H
