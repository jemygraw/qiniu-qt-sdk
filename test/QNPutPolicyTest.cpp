#include "QNPutPolicyTest.h"
#include "QNPutPolicy.h"
#include "QNUtils.h"
#include <QString>
#include <iostream>

void QNPutPolicyTest::putPolicyTest1()
{
    QString scope=QString("jemydemob");
    QString saveKey=QString("hello.jpeg");
    QNPutPolicy policy=QNPutPolicy(scope);
    policy.setDeadline(QNUtils::expireInSeconds(3600));
    policy.setSaveKey(&saveKey);
    QString json= policy.toJSON();
    std::cout<<json.toStdString()<<std::endl;
}
