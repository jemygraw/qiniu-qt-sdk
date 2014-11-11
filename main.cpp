#include <QtTest/QtTest>
#include "test/Base64Test.h"
#include "test/MacDigestTest.h"
#include "qiniu/conf/QNConf.h"
#include "test/QNUrlTest.h"
#include "test/QNETagTest.h"
#include "test/QNPutPolicyTest.h"
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QDateTime>
#include <QNetworkAccessManager>
#include "ui/QNMainWindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QNMainWindow *wnd=new QNMainWindow();
    wnd->show();
    return app.exec();
}
