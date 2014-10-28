#ifndef QNPUTPOLICYTEST_H
#define QNPUTPOLICYTEST_H

#include <QObject>
class QNPutPolicyTest : public QObject
{
    Q_OBJECT
private slots:
    void putPolicyTest1();
    void putRetTest1();
    void makeUploadTokenTest();
};

#endif // QNPUTPOLICYTEST_H
