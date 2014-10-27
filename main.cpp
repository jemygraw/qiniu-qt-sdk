#include "ui/QNMainWindow.h"
#include <QApplication>
#include <QtTest/QtTest>
#include "test/Base64Test.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNMainWindow w;
    w.show();
    return a.exec();
}
