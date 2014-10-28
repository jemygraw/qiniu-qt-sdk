#include "QNUrl.h"
#include "QNUtils.h"
#include "QNConf.h"
#include "QNMac.h"
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <iostream>

QNUrl::QNUrl(QString *styleDelimiter)
{
    if (styleDelimiter!=NULL)
    {
        this->styleDelimiter = styleDelimiter;
    }
    else
    {
        this->styleDelimiter = new QString(QNConf::DEFAULT_STYLE_DELIMITER);
    }
}

QNUrl::~QNUrl()
{
    if (this->styleDelimiter!=NULL)
    {
        delete this->styleDelimiter;
    }
}


QString QNUrl::makePublicSimpleUrl(QString *domain, QString *key,
                                   QString *fop=NULL, bool isAlias=false)
{
    QString finalUrl=QString(*domain);
    finalUrl.append("/");
    finalUrl.append(QNUtils::escapeKey(*key));

    if (fop!=NULL){
        if (isAlias){
            finalUrl.append(*(this->styleDelimiter)).append(*fop);
        }else{
            finalUrl.append("?").append(*fop);
        }
    }
    return finalUrl;
}

QString QNUrl::makePrivateSimpleUrl(QString *domain, QString *key, QNMac *mac=NULL, QDateTime *deadline=NULL,
                                    QString *fop=NULL, bool isAlias=false)
{
    QString finalUrl=QString(*domain);
    finalUrl.append("/");
    finalUrl.append(QNUtils::escapeKey(*key));
    if (fop!=NULL){
        if (isAlias){
            finalUrl.append(*(this->styleDelimiter)).append(*fop);
        }else{
            finalUrl.append("?").append(*fop);
        }
    }

    QDateTime now=QDateTime::currentDateTime();
    now.setOffsetFromUtc(3600*8);
    //default time span is one hour
    std::cout<<now.toString().toStdString()<<std::endl;
    now=now.addSecs(3600);
    std::cout<<now.toString().toStdString()<<std::endl;

    uint expireTimestamp=now.toTime_t();
    if(deadline!=NULL)
    {
        expireTimestamp=(*deadline).toTime_t()/1000;
    }
    if(finalUrl.contains("?"))
    {
        finalUrl.append("&e=").append(QString::number(expireTimestamp));
    }
    else
    {
        finalUrl.append("?e=").append(QString::number(expireTimestamp));
    }

    if(mac==NULL)
    {
        QString accessKey=QNConf::ACCESS_KEY;
        QByteArray secretKey=QNConf::SECRET_KEY;
        QNMac mac1=QNMac(&accessKey,&secretKey);
        mac=&mac1;
    }
    QByteArray finalUrlData=finalUrl.toLocal8Bit();
    QString token=mac->sign(&finalUrlData);
    finalUrl.append("&token=").append(token);
    return finalUrl;
}

