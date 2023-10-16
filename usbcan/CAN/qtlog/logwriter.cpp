#include "logwriter.h"

#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QStringLiteral>
namespace GauGene
{
namespace LogPrivate
{
    LogWriter::LogWriter() : m_MaxSize(10 * 1024 * 1024) {}

    LogWriter::~LogWriter()
    {
        //将日志文件关闭掉
        QHash< QString, QFile * >::iterator it = m_LogFiles.begin();
        while (it != m_LogFiles.end())
        {
            it.value()->close();
            it.value()->deleteLater();
            ++it;
        }
    }

    /**
 * @brief
 * 设置单个文件最大字节数，默认10M,超过限定的文件最大字节数,会重新创建新的日志文件继续写入
 * @param size:[in] 单个文件最大字节数
 */
    void LogWriter::setMaxFileSize(quint64 size) { m_MaxSize = size; }

    void LogWriter::write(QString logFilePath, const QByteArray &data)
    {
        QFile *f = 0;
        if (m_LogFiles.contains(logFilePath))
        {
            f = m_LogFiles[logFilePath];
            //有可能在运行中文件被删除
            QFileInfo fi(f->fileName());
            if (!fi.exists())
                QDir().mkpath(fi.absolutePath());
        }
        else
        {
            f = new QFile;
            f->setFileName(generateFileName(logFilePath));
            m_LogFiles.insert(logFilePath, f);
        }
        if (f->open(QFile::WriteOnly | QFile::Append | QFile::Text))
        {
            f->write(data);


            quint64 pos = f->pos();
            f->close();

            if (pos > m_MaxSize)
            {
                f->setFileName(generateFileName(logFilePath));
            }
        }
    }

    /**
     * @brief generateFileName 生成日志文件名 如果已经存在同名，则在名字后面加数字区别 eg ./dir/filename_xxx_xxxx_1.log
     * @param logFilePath
     * @return
     */
    QString LogWriter::generateFileName(QString logFilePath)
    {
        static QHash< QString, int > numMap;
        QFileInfo logFileInfo(logFilePath);
        QString filePath = QString("%1/%2_%3.%4").arg(logFileInfo.path(), logFileInfo.baseName(), QDateTime::currentDateTime().toString("yyyy_MM_dd"), logFileInfo.suffix());
        if (numMap.contains(logFilePath))
            filePath = QString("%1/%2_%3__%5.%4")
                           .arg(logFileInfo.path(), logFileInfo.baseName(), QDateTime::currentDateTime().toString("yyyy_MM_dd"), logFileInfo.suffix(), QString::number(numMap.value(logFilePath)));
        QFileInfo fi(filePath);
        if (!fi.exists())
            QDir().mkpath(fi.absolutePath());
        numMap.insert(logFilePath, numMap.value(logFilePath, 0) + 1);
        return fi.absoluteFilePath();
    }

}  // namespace LogPrivate
}  // namespace GauGene
