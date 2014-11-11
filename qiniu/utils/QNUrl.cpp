#include "QNUrl.h"
#include "QNUtils.h"
#include "qiniu/conf/QNConf.h"
#include "qiniu/auth/QNMac.h"
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

    if (fop!=0 &&fop->isEmpty()){
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
    if (fop!=0 && !fop->isEmpty()){
        if (isAlias){
            finalUrl.append(this->styleDelimiter).append(*fop);
        }else{
            finalUrl.append("?").append(*fop);
        }
    }
    uint expireTimestamp=QNUtils::expireInSeconds(3600);
    if(deadline!=0 && !deadline->isNull())
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
    if (mac!=0)
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

