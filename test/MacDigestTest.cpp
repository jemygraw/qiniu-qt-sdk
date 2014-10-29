#include "MacDigestTest.h"
#include <QString>
#include <QByteArray>
#include "qiniu/auth/QNMac.h"
#include <iostream>

void MacDigestTest::macDigestTest()
{
    QString accessKey="pObK-5uirmOAtYGM705oxIco1m9xlqwONnYyLOoI";
    QString secretKey="wXIqwPbClstEew5vibPkUJPv-bJojiVe4aapNmYJ";
    QByteArray secretBytes=secretKey.toLocal8Bit();
    QNMac *mac=new QNMac(&accessKey,&secretBytes);
    //test method sign
    QByteArray url=QByteArray("http://my-bucket.qiniudn.com/sunflower.jpg?e=1451491200");
    std::cout<< mac->sign(url).toStdString()<<std::endl;

    //test method signWithData
    QByteArray data=QByteArray("hello world");
    std::cout<<mac->signWithData(data).toStdString()<<std::endl;
}

// MacDigestTest t;
// QTest::qExec(&t);
