#include "QNUrl.h"
#include "QNUtils.h"
#include "QNConf.h"
#include "QNMac.h"
#include <QString>
#include <QDateTime>

QNUrl::QNUrl():styleDelimiter(QNConf::DEFAULT_STYLE_DELIMITER)
{

}

QNUrl::QNUrl(QString &styleDelimiter):styleDelimiter(styleDelimiter)
{
}

QNUrl::~QNUrl()
{
}


QString QNUrl::makePublicSimpleUrl(const QString &domain, const QString &key,
                                   const QString *fop, const bool isAlias)
{
    QString finalUrl=QString(domain);
    finalUrl.append("/");
    finalUrl.append(QNUtils::escapeKey(key));

    if (fop!=NULL &&fop->isEmpty()){
        if (isAlias){
            finalUrl.append(this->styleDelimiter).append(*fop);
        }else{
            finalUrl.append("?").append(*fop);
        }
    }
    return finalUrl;
}

QString QNUrl::makePrivateSimpleUrl(const QString &domain, const QString &key,
                                    const QString *fop, const bool isAlias,
                                    const QDateTime *deadline, const QNMac *mac)
{
    QString finalUrl=QString(domain);
    finalUrl.append("/");
    finalUrl.append(QNUtils::escapeKey(key));
    if (fop!=NULL && !fop->isEmpty()){
        if (isAlias){
            finalUrl.append(this->styleDelimiter).append(*fop);
        }else{
            finalUrl.append("?").append(*fop);
        }
    }

    QDateTime now=QDateTime::currentDateTime();
    //qiniu server timezone is utc+8
    now.setOffsetFromUtc(3600*8);
    //default time span is one hour
    now=now.addSecs(3600);

    uint expireTimestamp=now.toTime_t();
    if(deadline!=NULL && !deadline->isNull())
    {
        expireTimestamp=(*deadline).toTime_t();
    }
    if(finalUrl.contains("?"))
    {
        finalUrl.append("&e=").append(QString::number(expireTimestamp));
    }
    else
    {
        finalUrl.append("?e=").append(QString::number(expireTimestamp));
    }
    QByteArray finalUrlData=finalUrl.toLocal8Bit();
    QString token;
    if (mac!=NULL)
    {
        token=mac->sign(finalUrlData);
    }
    else
    {
        QNMac macx=QNMac(QNConf::ACCESS_KEY,QNConf::SECRET_KEY);
        token=macx.sign(finalUrlData);
    }

    finalUrl.append("&token=").append(token);
    return finalUrl;
}

