#include "reagentdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReagentDialog w;
    w.show();
    return a.exec();
}
