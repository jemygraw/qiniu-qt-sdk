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

//Get the meta info for the file
QNetworkRequest QNRS::statRequest(const QString &bucket, const QString &key,
                                  const QNMac *mac)
{
    QNetworkRequest request;
    QString reqUrl(QNConf::RS_HOST);
    reqUrl.append("/stat/");

    //append encoded entry
    QString entry;
    entry.append(bucket).append(":").append(key);
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

//Copy a file to a new one
QNetworkRequest QNRS::copyRequest(const QString &srcBucket, const QString &srcKey,
                                  const QString &destBucket, const QString &destKey,
                                  const QNMac *mac)
{
    QNetworkRequest request;
    QString reqUrl(QNConf::RS_HOST);
    reqUrl.append("/copy/");

    //append encoded entry
    QString srcEntry;
    srcEntry.append(srcBucket).append(":").append(srcKey);
    QString destEntry;
    destEntry.append(destBucket).append(":").append(destKey);
    QString encodedSrcEntry=QNUtils::urlSafeBase64Encode(srcEntry.toLocal8Bit());
    QString encodedDestEntry=QNUtils::urlSafeBase64Encode(destEntry.toLocal8Bit());
    reqUrl.append(encodedSrcEntry).append("/").append(encodedDestEntry);
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

//Move a file to a new one
QNetworkRequest QNRS::moveRequest(const QString &srcBucket, const QString &srcKey,
                                  const QString &destBucket, const QString &destKey,
                                  const QNMac *mac)
{
    QNetworkRequest request;
    QString reqUrl(QNConf::RS_HOST);
    reqUrl.append("/move/");

    //append encoded entry
    QString srcEntry;
    srcEntry.append(srcBucket).append(":").append(srcKey);
    QString destEntry;
    destEntry.append(destBucket).append(":").append(destKey);
    QString encodedSrcEntry=QNUtils::urlSafeBase64Encode(srcEntry.toLocal8Bit());
    QString encodedDestEntry=QNUtils::urlSafeBase64Encode(destEntry.toLocal8Bit());
    reqUrl.append(encodedSrcEntry).append("/").append(encodedDestEntry);
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

//Delete a file
QNetworkRequest QNRS::deleteRequest(const QString &bucket, const QString &key,
                                  const QNMac *mac)
{
    QNetworkRequest request;
    QString reqUrl(QNConf::RS_HOST);
    reqUrl.append("/delete/");

    //append encoded entry
    QString entry;
    entry.append(bucket).append(":").append(key);
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
