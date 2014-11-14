#include "QNRS.h"
#include "qiniu/utils/QNUtils.h"
#include "qiniu/conf/QNConf.h"
#include "qiniu/auth/QNMac.h"
#include <QString>
#include <QStringList>
#include <QNetworkRequest>
#include <QUrl>

QNRS::QNRS()
{
}

QNetworkRequest QNRS::statRequest(const QString &bucket, const QString &key, const QNMac *mac)
{
    QNetworkRequest request;
    QString reqUrl(QNConf::RS_HOST);
    reqUrl.append("/stat/");

    //append encoded entry
    QString entry;
    entry.append(bucket);
    entry.append(":");
    entry.append(key);
    QString encodedEntry=QNUtils::urlSafeBase64Encode(entry.toLocal8Bit());
    reqUrl.append(encodedEntry);
    request.setUrl(reqUrl);

    //set authorization header
    QString authHeader("Authorization");
    QString authHeaderBody("QBox ");
    QString accessToken;
    if(mac!=0)
    {
        accessToken=mac->signRequest(request);
    }
    else
    {
        QNMac macx=QNMac(QNConf::ACCESS_KEY,QNConf::SECRET_KEY);
        accessToken=macx.signRequest(request);
    }
    authHeaderBody.append(accessToken);
    request.setRawHeader(authHeader.toLocal8Bit(),authHeaderBody.toLocal8Bit());
    return request;
}
