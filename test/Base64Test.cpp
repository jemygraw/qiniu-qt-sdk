#include "test/Base64Test.h"
#include "qiniu/QNUtils.h"
#include <QByteArray>
void Base64Test::base64EncodeTest()
{
    QByteArray data("hello");
    QString encoded = QNUtils::urlSafeBase64Encode(data);
    QVERIFY(encoded == "aGVsbG8=");
}

QTEST_MAIN(Base64Test)

