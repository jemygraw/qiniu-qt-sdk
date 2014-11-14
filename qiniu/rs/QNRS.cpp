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
    QString contentTypeHeader("Content-Type");
    QString contentTypeHeaderBody("application/x-www-form-urlencoded");
    request.setRawHeader(authHeader.toLocal8Bit(),authHeaderBody.toLocal8Bit());
    request.setRawHeader(contentTypeHeader.toLocal8Bit(),contentTypeHeaderBody.toLocal8Bit());
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
    QString contentTypeHeader("Content-Type");
    QString contentTypeHeaderBody("application/x-www-form-urlencoded");
    request.setRawHeader(authHeader.toLocal8Bit(),authHeaderBody.toLocal8Bit());
    request.setRawHeader(contentTypeHeader.toLocal8Bit(),contentTypeHeaderBody.toLocal8Bit());
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
    QString contentTypeHeader("Content-Type");
    QString contentTypeHeaderBody("application/x-www-form-urlencoded");
    request.setRawHeader(authHeader.toLocal8Bit(),authHeaderBody.toLocal8Bit());
    request.setRawHeader(contentTypeHeader.toLocal8Bit(),contentTypeHeaderBody.toLocal8Bit());
    return request;
}

//Change file mimetype
QNetworkRequest QNRS::chgmRequest(const QString &bucket, const QString &key,
                                  const QString &newMimeType,
                                  const QNMac *mac)
{
    QNetworkRequest request;
    QString reqUrl(QNConf::RS_HOST);
    reqUrl.append("/chgm/");

    //append encoded entry
    QString entry;
    entry.append(bucket).append(":").append(key);
    QString encodedEntry=QNUtils::urlSafeBase64Encode(entry.toLocal8Bit());
    reqUrl.append(encodedEntry);
    QString encodedMimeType=QNUtils::urlSafeBase64Encode(newMimeType.toLocal8Bit());
    reqUrl.append("/mime/").append(encodedMimeType);
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
    QString contentTypeHeader("Content-Type");
    QString contentTypeHeaderBody("application/x-www-form-urlencoded");
    request.setRawHeader(authHeader.toLocal8Bit(),authHeaderBody.toLocal8Bit());
    request.setRawHeader(contentTypeHeader.toLocal8Bit(),contentTypeHeaderBody.toLocal8Bit());
    return request;
}


//Batch operations
QNetworkRequest QNRS::batchRequest(const QString &requestBody, const QNMac *mac)
{
    QNetworkRequest request;
    QString reqUrl(QNConf::RS_HOST);
    reqUrl.append("/batch");
    request.setUrl(reqUrl);

    //set authorization header
    QString authHeader("Authorization");
    QString authHeaderBody("QBox ");
    QString accessToken;
    QByteArray requestBodyBytes=requestBody.toLocal8Bit();
    if(mac!=0)
    {
        accessToken=mac->signRequest(request,&requestBodyBytes);
    }
    else
    {
        QNMac macx=QNMac(QNConf::ACCESS_KEY,QNConf::SECRET_KEY);
        accessToken=macx.signRequest(request,&requestBodyBytes);
    }
    authHeaderBody.append(accessToken);
    QString contentTypeHeader("Content-Type");
    QString contentTypeHeaderBody("application/x-www-form-urlencoded");
    request.setRawHeader(authHeader.toLocal8Bit(),authHeaderBody.toLocal8Bit());
    request.setRawHeader(contentTypeHeader.toLocal8Bit(),contentTypeHeaderBody.toLocal8Bit());
    return request;
}
