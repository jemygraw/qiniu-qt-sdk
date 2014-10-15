#include "ui/QNMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNMainWindow w;
    w.show();

    return a.exec();
}
