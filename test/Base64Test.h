#ifndef BASE64TEST_H
#define BASE64TEST_H

#include <QtTest/QtTest>

class Base64Test : public QObject
{
    Q_OBJECT
private slots:
    void base64EncodeTest();
};

#endif
