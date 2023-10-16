#ifndef LOGFILE_HPP
#define LOGFILE_HPP

#include <QHash>
#include <QObject>

class QFile;

namespace GauGene {
namespace LogPrivate {

class LogWriter : public QObject {

    Q_OBJECT
public:
    LogWriter();
    ~LogWriter();
public:
    /**
     * @brief
     * 设置单个文件最大字节数，默认10M,超过限定的文件最大字节数,会重新创建新的日志文件继续写入
     * @param size:[in] 单个文件最大字节数
     */
    void setMaxFileSize(quint64 size = 10 * 1024 * 1024);

public slots:
    void write(QString logFilePath, const QByteArray &data);

private:
    /**
     * @brief generateFileName 生成日志文件名 如果已经存在同名，则在名字后面加数字区别 eg ./dir/filename_xxx_xxxx_1.log
     * @param logFilePath
     * @return
     */
    QString generateFileName(QString logFilePath);

private:
    quint64 m_MaxSize;
    QHash<QString, QFile *> m_LogFiles;
};

} // namespace LogPrivate
} // namespace GauGene

#endif // LOGFILE_HPP
