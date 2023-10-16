#include "mainwindow.h"
#include "qtlog/qtlog.h"
#include <QApplication>

#include "thirdParty/thirdInclude/exchndl.h"
struct Node{
    char value;
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    ExcHndlInit();
    /***********测试异常函数 start*******************/
    //Node *ptr=nullptr;
   // qDebug()<<ptr->value;
    /***********测试异常函数 end*******************/
    //在relese版本中 将qDebug的信息都打印到日志文本中  日志文本位置程序目录的log文件夹里
  //  QString logDir = QApplication::applicationDirPath() + "/log/can.log";
   // GauGene::QtLog::startLogger(logDir);

    MainWindow w;
    w.show();

    return a.exec();
}
