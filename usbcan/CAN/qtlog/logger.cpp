#include "logger.h"
#include "logwriter.h"
#include <QDateTime>
#include <QDir>
#include <iostream>

namespace GauGene
{
namespace LogPrivate
{

    Logger *Logger::instance()
    {
        static Logger self;
        return &self;
    }

    Logger::Logger()
    {
        m_thread=new QThread();
        m_LogWriter = new LogWriter;
        m_LogWriter->moveToThread(m_thread);
        QObject::connect(this, SIGNAL(logReady(QString, QByteArray)), m_LogWriter, SLOT(write(QString, QByteArray)));
        m_thread->start();
    }

    Logger::~Logger()
    {
        m_LogWriter->deleteLater();
        m_LogWriter=0;
        m_thread->quit();
    }

    void Logger::custom(QString logFilePath, const QByteArray &log) {
        if(!m_LogWriter)
            return;
        //将日志传到线程中写文件
        emit logReady(logFilePath, log);
    }

    QByteArray Logger::generateLogMsg(const QByteArray &log)
    {
        QByteArray msg;
        msg.append("[DateTime] ");
        msg.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        msg.append(newLine());
        msg.append(log);
        msg.append(newLine());
        msg.append(newLine());
        return msg;
    }


    QByteArray Logger::newLine()
    {
        QByteArray newline;
#if defined(Q_OS_WIN)
        newline.append('\r');
        newline.append('\n');
#elif defined(Q_OS_UNIX)
        newline.append('\n');
#endif
        return newline;
    }

}  // namespace LogPrivate
}  // namespace GauGene
