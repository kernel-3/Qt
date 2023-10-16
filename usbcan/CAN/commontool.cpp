#include "commontool.h"
#include <QMessageBox>

CommonTool *CommonTool::instance()
{
    static CommonTool self;
    return &self;
}

CommonTool::CommonTool(QObject *parent) : QObject(parent)
{
}

qint32 CommonTool::str2int(QString numStr)
{
    if (numStr.contains("0x", Qt::CaseInsensitive))
    {
        return numStr.remove("0x", Qt::CaseInsensitive).toInt(0, 16);
    }
    else
        return numStr.toInt(0, 10);
}

QString CommonTool::numStrAdd(QString numStr, int num)
{
    quint32 value = str2int(numStr) + num;
    if (numStr.startsWith("0x", Qt::CaseInsensitive))
    {
        return QString("0x%1").arg(QString::number(value, 16));
    }
    else
        return QString::number(value, 10);
}

bool CommonTool::checkData(const QString &arg1)
{
    QVector< QString > dataSplit = arg1.split(commonTool->unNumberRegExp()).toVector();
    bool isvalid = true;
    QString info;
    switch (dataSplit.count())
    {
    case 1:
        break;
    case 2:
        foreach (QString str, dataSplit)
        {
            qint32 value = commonTool->str2int(str);
            if (value > 0xffff || value < -32768)
            {
                if (value < -32768)
                    info = "指令中存在小-32768/0x8000的值";
                else
                    info = "指令中存在大于65535/0xffff的值";
                isvalid = false;
                break;
            }
        }
        break;
    case 3:
        break;
    case 4:
        foreach (QString str, dataSplit)
        {
           qint32 value = commonTool->str2int(str);
            if (value > 0xff || value < -128)
            {
                if (value < -128)
                    info = "指令中存在小-128/0x80的值";
                else
                    info = "指令中存在大于255/0xff的值";
                isvalid = false;
                break;
            }
        }
        break;
    default:
        QMessageBox::information(0, "提示", "指令错误");
        return false;
    }
    if (!isvalid)
        QMessageBox::information(0, "提示", info);
    return isvalid;
}

bool CommonTool::checkValue(const QString &str, CommonTool::CharLength charNum)
{
    bool isvalid = true;
    QString info;
    switch (charNum)
    {
    case two:
    {
        info = "值大于65535/0xffff";
        quint32 value = commonTool->str2int(str);
        if (value > 0xffff)
        {
            isvalid = false;
        }
    }
    break;
    case one:
    {
        info = "值大于255/0xff";
        quint32 value = commonTool->str2int(str);
        if (value > 0xff)
        {
            isvalid = false;
        }
    }
    break;
    default:
        QMessageBox::information(0, "提示", "指令错误");
        return false;
    }
    if (!isvalid)
        QMessageBox::information(0, "提示", info);
    return isvalid;
}

QRegExp CommonTool::unNumberRegExp()
{
    return QRegExp("[^xX0-9a-fA-F\-]");
}
