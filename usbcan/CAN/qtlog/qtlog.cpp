#include "qtlog.h"
#include "logger.h"
#include <QByteArray>
#include <QDateTime>
#include <QString>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#if QT_VERSION > 0x050200
#include <QLoggingCategory>
#endif

/***********************************堆栈打印************************************************
#ifdef _WIN32
#include <Dbghelp.h>
#include <QApplication>
#include <Windows.h>
#include <tchar.h>
#include <time.h>

void create_minidump(struct _EXCEPTION_POINTERS *apExceptionInfo);
LONG WINAPI unhandled_handler(struct _EXCEPTION_POINTERS *apExceptionInfo);
#endif

#if defined(__linux__) || defined(__linux)
#ifdef __GNUC__
#include "stacktrace.h"
#include <cxxabi.h>
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_signal(int sig);
#endif
#endif
***********************************堆栈打印************************************************/

namespace GauGene
{

static QString gLogFilePath;

static void msgHandlerV2(QtMsgType type, const QMessageLogContext & /*context*/, const QString &msg);
static void msgHandler(QtMsgType type, const char *msg);
static QString generateLogMsg(const QString &log, const QMessageLogContext &context);
static QByteArray generateLogMsg(const QByteArray &log);
static QByteArray newLine();
//song
static QByteArray generateLogSongMsg(const QByteArray &log);
/**
 * @brief 启用日志
 * @param logFilePath:[in] 日志文件存放的路径 eg ./dir/fileName.log
 * @note 实际日志文件路径为 ./dir/xxx/fileName_xxx_xxx.log
 */
void QtLog::startLogger(QString logFilePath)
{
    if (!gLogFilePath.isEmpty())
        return;
    gLogFilePath = logFilePath;

#if QT_DEPRECATED_SINCE(5, 0)  // deprecated. Use qInstallMessageHandler instead!
    qInstallMsgHandler(msgHandler);
#else
    //默认将所有的日志都启用
    QLoggingCategory *defaultCate = QLoggingCategory::defaultCategory();
    defaultCate->setEnabled(QtDebugMsg, true);
    defaultCate->setEnabled(QtWarningMsg, true);
    defaultCate->setEnabled(QtCriticalMsg, true);
    defaultCate->setEnabled(QtFatalMsg, true);
    defaultCate->setEnabled(QtInfoMsg, true);
    qInstallMessageHandler(msgHandlerV2);
#endif

    qDebug() << "\n\n\n*****************************************************************************************************************************************\n"
                "qtlog start once again, maybe application start or restarted"
                "\n*****************************************************************************************************************************************";
}

/**
 * @brief 启动崩溃检测和堆栈打印
 */
void QtLog::startCrashStackTrace()
{
    /******************
#ifdef _WIN32
#ifdef _MSC_VER
    SetUnhandledExceptionFilter(unhandled_handler);
#endif
#endif

#if defined(__linux__) || defined(__linux)
    signal(SIGSEGV, handle_signal);
    signal(SIGABRT, handle_signal);
    signal(SIGFPE, handle_signal);
    signal(SIGILL, handle_signal);
    signal(SIGINT, handle_signal);
#endif
*********************************/
}

void QtLog::logging(QString logFilePath, QString log)
{
    logging(logFilePath, log.toUtf8());
}

void QtLog::logging(QString logFilePath, const char *log)
{
    logging(logFilePath, QByteArray(log));
}
void QtLog::songlogging(QString logFilePath, const QByteArray &log)
{
    LogPrivate::Logger::instance()->custom(logFilePath, generateLogSongMsg(log));
}
void QtLog::logging(QString logFilePath, const QByteArray &log)
{
    LogPrivate::Logger::instance()->custom(logFilePath, generateLogMsg(log));
}

/***********************************控制台消息接管************************************************/
void msgHandlerV2(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFileInfo fileInfo(gLogFilePath);
    QString typeStr;
    switch (type)
    {
    case QtInfoMsg:
    case QtDebugMsg:
        typeStr = "Debug";
        break;
    case QtWarningMsg:
        typeStr = "Warning";
        break;
    case QtCriticalMsg:
        typeStr = "Critical";
        break;
    case QtFatalMsg:
        typeStr = "Fatal";
        break;
    default:
        typeStr = "Debug";
        break;
    }
    QString logFilePath = QString("%1/%2/%3").arg(fileInfo.path(), typeStr, fileInfo.fileName());
    QByteArray log=generateLogMsg(msg,context).toUtf8();
    LogPrivate::Logger::instance()->custom(logFilePath, log);
}
void msgHandler(QtMsgType type, const char *msg)
{
    QFileInfo fileInfo(gLogFilePath);
    QString typeStr;
    switch (type)
    {
    case QtInfoMsg:
    case QtDebugMsg:
        typeStr = "Debug";
        break;
    case QtWarningMsg:
        typeStr = "Warning";
        break;
    case QtCriticalMsg:
        typeStr = "Critical";
        break;
    case QtFatalMsg:
        typeStr = "Fatal";
        break;
    default:
        typeStr = "Debug";
        break;
    }
    QString logFilePath = QString("%1/%2/%3").arg(fileInfo.path(), typeStr, fileInfo.fileName());
    QtLog::logging(logFilePath, msg);
}

QString generateLogMsg(const QString &log, const QMessageLogContext &context)
{
    QString msg = QString("[time:%1] [file:%2] [fun:%3] [logLine:%4] %5%6%7%8")
                      .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
                      .arg(context.file)
                      .arg(context.function)
                      .arg(context.line)
                      .arg(newLine().data())
                      .arg(log)
                      .arg(newLine().data())
                      .arg(newLine().data());
    return msg;
}

//song
QByteArray generateLogSongMsg(const QByteArray &log)
{
    QByteArray msg;
    //msg.append("[DateTime] ");
    //msg.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
    msg.append(newLine());
    msg.append(log);
   // msg.append(newLine());
   // msg.append(newLine());
    return msg;
}
QByteArray generateLogMsg(const QByteArray &log)
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

QByteArray newLine()
{
    QByteArray newline;
#if defined(Q_OS_WIN)
    //使用notepad++ 看文本
    //newline.append('\r');
    newline.append('\n');
#elif defined(Q_OS_UNIX)
    newline.append('\n');
#endif
    return newline;
}

/***********************************控制台消息接管************************************************/

}  // namespace GauGene

/***********************************堆栈打印************************************************
static void writeCrashLog(const char *log)
{
    QString logFilePath = QString("%1/crash/crash.log").arg(QApplication::applicationDirPath());
    if (!GauGene::gLogFilePath.isEmpty())
    {
        QFileInfo fileInfo(GauGene::gLogFilePath);
        logFilePath = QString("%1/crash/%2").arg(fileInfo.path(), fileInfo.fileName());
    }
    GauGene::QtLog::logging(logFilePath, log);
}

#ifdef _WIN32
typedef BOOL(WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess,
                                        DWORD dwPid,
                                        HANDLE hFile,
                                        MINIDUMP_TYPE DumpType,
                                        CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                        CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                        CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

void create_minidump(struct _EXCEPTION_POINTERS *apExceptionInfo)
{

    time_t tm;
    time(&tm);

    TCHAR file[128];
    wsprintf(file, TEXT("core.%d.dmp"), tm);

    HMODULE mhLib = ::LoadLibrary(TEXT("dbghelp.dll"));
    MINIDUMPWRITEDUMP pDump = (MINIDUMPWRITEDUMP)::GetProcAddress(mhLib, "MiniDumpWriteDump");

    HANDLE hFile = ::CreateFile(file, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    _MINIDUMP_EXCEPTION_INFORMATION ExInfo;
    ExInfo.ThreadId = ::GetCurrentThreadId();
    ExInfo.ExceptionPointers = apExceptionInfo;
    ExInfo.ClientPointers = FALSE;

    pDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL);
    ::CloseHandle(hFile);
}

LONG WINAPI unhandled_handler(struct _EXCEPTION_POINTERS *apExceptionInfo)
{

    // TODO:调用堆栈打印
    StackTrace st;
    writeCrashLog(st.toCstring());

    create_minidump(apExceptionInfo);
    return EXCEPTION_CONTINUE_SEARCH;
}
#endif
#if defined(__linux__) || defined(__linux)
void handle_signal(int sig)
{
    writeCrashLog(QString("error:signal %1:\n").arg(sig).toUtf8().data());
    StackTrace st;
    writeCrashLog(st.toCstring());
}
#endif
#endif

***********************************************************************************/
