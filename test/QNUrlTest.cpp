#include "QNUrlTest.h"
#include "qiniu/utils/QNUrl.h"
#include <iostream>
#include "qiniu/auth/QNMac.h"

void QNUrlTest::publicUrlTest()
{
    QNUrl url=QNUrl();
    QString domain="http://jemydemob.qiniudn.com";
    QString key="/image@jemy.png";
    QString fop="small";
    bool isAlias=true;
    QString req=url.makePublicSimpleUrl(domain,key,&fop,isAlias);
    std::cout<<req.toStdString()<<std::endl;
}

void QNUrlTest::privateUrlTest()
{
    QString delimiter="$";
    QNUrl url=QNUrl(delimiter);
    QString domain="http://jxx-private.qiniudn.com";
    QString key="haha.jpg";
    QString fop="s100";
    bool isAlias=true;
    QString accessKey="pObK-5uirmOAtYGM705oxIco1m9xlqwONnYyLOoI";
    QString secretKey="wXIqwPbClstEew5vibPkUJPv-bJojiVe4aapNmYJ";
    QByteArray secretBytes=secretKey.toLocal8Bit();
    QNMac mac=QNMac(accessKey,secretBytes);
    QString req=url.makePrivateSimpleUrl(domain,key,&fop,isAlias);
    std::cout<<req.toStdString()<<std::endl;
}

void QNUrlTest::privateUrlTest2()
{
    QNUrl url=QNUrl();
    QString domain="http://jxx-private.qiniudn.com";
    QString key="haha.jpg";
    QString fop="imageView2/2/w/100/h/200";
    bool isAlias=false;
    QString accessKey="pObK-5uirmOAtYGM705oxIco1m9xlqwONnYyLOoI";
    QString secretKey="wXIqwPbClstEew5vibPkUJPv-bJojiVe4aapNmYJ";
    QByteArray secretBytes=secretKey.toLocal8Bit();
    QNMac mac=QNMac(accessKey,secretBytes);
    QString req=url.makePrivateSimpleUrl(domain,key,&fop,isAlias,NULL,&mac);
    std::cout<<req.toStdString()<<std::endl;
}

//QNUrlTest t;
//QTest::qExec(&t);
