#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QObject>
#include <QThread>
#include <QFileInfo>

class QString;
class QByteArray;

namespace GauGene {
namespace LogPrivate {

class LogWriter;
class Logger : public QObject {

    Q_OBJECT

public:
    static Logger *instance();
    ~Logger();
public:
    void custom(QString logFilePath, const QByteArray &log);

signals:
    void logReady(const QString &key, const QByteArray &log);

private:
    explicit Logger();
    QByteArray generateLogMsg(const QByteArray &log);
    QByteArray newLine();

private:
    LogWriter *m_LogWriter;
    QThread *m_thread;
};

} // namespace LogPrivate
} // namespace GauGene
#endif // LOGGER_HPP
