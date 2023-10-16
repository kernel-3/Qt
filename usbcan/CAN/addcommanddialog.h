#ifndef ADDCOMMANDDIALOG_H
#define ADDCOMMANDDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMap>

namespace Ui {
class AddCommandDialog;
}

class FocusEventFilter;
class AddCommandDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddCommandDialog(QWidget *parent = nullptr);
    ~AddCommandDialog();
public:
    void setCommandJson(QByteArray jsonStr);
    void setCommandValue(QList<QStringList> strsList);
    QList<QStringList> commandStrings();
signals:
    void commandTest();
    void finished(bool accept);
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_lineEdit_data_textChanged(const QString &arg1);

    void on_lineEdit_commandSyn_textChanged(const QString &arg1);

    void on_lineEdit_command_textChanged(const QString &arg1);

    void on_pushButton_send_clicked();

private:
    bool checkInput();
    void changeParam(QString param,int index);
private:
    int mType;
    int mCurrentRow;

private:
    Ui::AddCommandDialog *ui;
    FocusEventFilter *mEventFilter;
};

class FocusEventFilter :public QObject
{
    Q_OBJECT
public:
    FocusEventFilter(QObject *parent=0);
    bool eventFilter(QObject *watched, QEvent *event);
    void setWatchRow(QObject *watched,int row);
signals:
    void focusIn(int row);
private:
    QMap<QObject *,int > mWatchedMap;
};

#endif // ADDCOMMANDDIALOG_H
