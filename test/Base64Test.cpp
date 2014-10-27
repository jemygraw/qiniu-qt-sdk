#include "test/Base64Test.h"
#include "qiniu/QNUtils.h"
#include <QByteArray>

void Base64Test::base64EncodeTest()
{
    QByteArray data("hello");
    QString encoded = QNUtils::urlSafeBase64Encode(data);
    QVERIFY(encoded == "aGVsbG8=");
    QByteArray decoded = QNUtils::urlSafeBase64Decode(encoded);
    QVERIFY(decoded == data);
}

//Base64Test t;
//QTest::qExec(&t);

