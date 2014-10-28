#include "QNPutPolicyTest.h"
#include "QNPutPolicy.h"
#include "QNPutRet.h"
#include "QNUtils.h"
#include "QNMac.h"
#include <QString>
#include <iostream>

void QNPutPolicyTest::putPolicyTest1()
{
    QString scope=QString("jemydemob");
    QString saveKey=QString("hello.jpeg");
    QNPutPolicy policy=QNPutPolicy(scope);
    policy.setDeadline(QNUtils::expireInSeconds(3600));
    policy.setSaveKey(&saveKey);
    QByteArray json= policy.toJSON();
    std::cout<<QString(json).toStdString()<<std::endl;
    std::cout<<std::endl<<std::endl;
}

void QNPutPolicyTest::putRetTest1()
{
    QByteArray jsonData=QByteArray("{\"hash\":\"Hash data\",\"key\":\"Key data\"}");
    std::cout<<QString(jsonData).toStdString()<<std::endl;
    QNPutRet putRet;
    QNPutRet::fromJSON(jsonData, &putRet);
    std::cout<<putRet.getHash()->toStdString()<<std::endl;
    std::cout<<putRet.getKey()->toStdString()<<std::endl;
    std::cout<<std::endl<<std::endl;
}

void QNPutPolicyTest::makeUploadTokenTest()
{
    QString scope=QString("jemydemob:hello.jpeg");
    QString saveKey=QString("hello.jpeg");
    QNPutPolicy policy=QNPutPolicy(scope);
    policy.setDeadline(QNUtils::expireInSeconds(3600));
    policy.setInsertOnly(0);
    policy.setSaveKey(&saveKey);
    QByteArray json= policy.toJSON();
    std::cout<<QString(json).toStdString()<<std::endl;
    QString accessKey="pObK-5uirmOAtYGM705oxIco1m9xlqwONnYyLOoI";
    QString secretKey="wXIqwPbClstEew5vibPkUJPv-bJojiVe4aapNmYJ";
    QByteArray secretBytes=secretKey.toLocal8Bit();
    QNMac mac=QNMac(accessKey,secretBytes);
    QString uploadToken=policy.makeUploadToken(&mac);
    std::cout<<uploadToken.toStdString()<<std::endl;
    std::cout<<std::endl<<std::endl;
}
