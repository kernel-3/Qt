#ifndef COMMANDFILTERFORM_H
#define COMMANDFILTERFORM_H

#include <QWidget>
#include <QLineEdit>
namespace Ui {
class CommandFilterForm;
}

class CommandFilterForm : public QWidget
{
    Q_OBJECT

public:
    explicit CommandFilterForm(QWidget *parent = nullptr);
    ~CommandFilterForm();
    //返回ID lineedit
    QLineEdit *mGetIDLineEidt();
    //设置所有组件不可用,可用
    void mSetAllNotEnable(bool enableFlag);

public:
signals:
    //id 过滤
    void currentIDChanged(const QString &IdChanged);
    //指令过滤
    void orderChanged(const QString &orderChanged);
    //指令序号
    void orderNumberChanged(const QString &orderNumberChanged);
    //数据
    void dataChanged(const QString &dataChanged);
private:
    Ui::CommandFilterForm *ui;
};

#endif // COMMANDFILTERFORM_H
