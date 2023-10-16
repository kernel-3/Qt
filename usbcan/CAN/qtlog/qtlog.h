#ifndef QTLOG_HPP
#define QTLOG_HPP
#include <QObject>

namespace GauGene {

/**
 * @brief The QtLog class  日志类 接管Qt的打印信息 将其打印日志保存到文件中
 * @author lrs
 * @note 接管了 qDebug(),qWarning(),qCritical(),qFatal()
 * @note 使用方式：
 *       1.在main()里调用startLogger(logpath)后，
 *       2.其他地方直接使用Qt的日志库如qDebug(),qWarning(),qCritical(),qFatal()
 * @note 不接管 std::cout
 * @note 同时提供了logging()函数 用于将指定日志内容打印到指定文件
 */

class  QtLog {
public:
    /**
     * @brief 启用日志
     * @param logFilePath:[in] 日志文件存放的路径 eg ./dir/fileName.log
     * @note 实际日志文件路径为 ./dir/xxx/fileName_xxx_xxx.log
     */
    static void startLogger(QString logFilePath);

    /**
     * @brief 启动崩溃检测和堆栈打印
     * @note 此函数未测试通过
     * @note TODO 待完善
     */
    static void startCrashStackTrace();

    /**
     * @param logFilePath:[in] 日志文件存放的路径
     * @param log:[in] 日志内容
     */
    static void logging(QString logFilePath, QString log);
    static void logging(QString logFilePath, const char *log);
    static void logging(QString logFilePath, const QByteArray &log);
    //song
    static void songlogging(QString logFilePath, const QByteArray &log);
};

} // namespace GauGene
#endif // QTLOG_HPP
