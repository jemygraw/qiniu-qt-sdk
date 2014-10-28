#ifndef QNURLTEST_H
#define QNURLTEST_H

#include <QObject>

class QNUrlTest : public QObject
{
    Q_OBJECT

private slots:
    void publicUrlTest();
    void privateUrlTest();
    void privateUrlTest2();
};

#endif // QNURLTEST_H
