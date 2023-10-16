#ifndef ONECOMMANDFORM_H
#define ONECOMMANDFORM_H

#include <QWidget>

namespace Ui {
class OneCommandForm;
}

class OneCommandForm : public QWidget
{
    Q_OBJECT

public:
    explicit OneCommandForm(QWidget *parent = nullptr);
    ~OneCommandForm();
public:
    QStringList commandString();
    bool isChecked();
    void setTitleVisible(bool visible);
    void restoreData(QStringList strs);
signals:
    void sendCommand();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_data_textChanged(const QString &arg1);

    void on_lineEdit_commandSyn_textChanged(const QString &arg1);

    void on_lineEdit_command_textChanged(const QString &arg1);

private:
    Ui::OneCommandForm *ui;
};

#endif // ONECOMMANDFORM_H
