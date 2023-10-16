#ifndef COMMONTOOL_H
#define COMMONTOOL_H

#include <QObject>

#define commonTool CommonTool::instance()

class CommonTool : public QObject
{
    Q_OBJECT
public:
    static CommonTool *instance();
public:
    enum CharLength
    {
        one=1,
        two=2
    };
public:
    qint32 str2int(QString numStr);
    QString numStrAdd(QString numStr,int num);
    bool checkData(const QString &arg1);
    bool checkValue(const QString &str,CharLength charNum);
    QRegExp unNumberRegExp();
private:
    explicit CommonTool(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COMMONTOOL_H
