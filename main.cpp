#include <QtTest/QtTest>
#include "test/Base64Test.h"
#include "test/MacDigestTest.h"
#include "qiniu/conf/QNConf.h"
#include "test/QNUrlTest.h"
#include "test/QNETagTest.h"
#include "test/QNPutPolicyTest.h"
#include <iostream>
#include <QDateTime>
int main(int argc, char *argv[])
{

    QNPutPolicyTest t;
    QTest::qExec(&t);
    return 0;
}
