#include "QNIOHelper.h"
#include "qiniu/conf/QNConf.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <iostream>
#include "qiniu/utils/QNUtils.h"

QHttpMultiPart* QNIOHelper::createPutDataMultiPart(const QString &uploadToken, const QByteArray &data,
                   const QString *key, const QString *fileName, const QNPutExtra *putExtra)
{
    QHttpMultiPart *multiPart=new QHttpMultiPart(QHttpMultiPart::FormDataType);
    //token
    QHttpPart tokenPart;
    tokenPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"token\""));
    tokenPart.setBody(uploadToken.toUtf8());
    //key
    QHttpPart *keyPart=0;
    if(key!=0 && !(*key).isEmpty())
    {
        keyPart=new QHttpPart;
        keyPart->setHeader(QNetworkRequest::ContentDispositionHeader,
                          QVariant("form-data; name=\"key\""));
        keyPart->setBody((*key).toLocal8Bit());
    }
    //file
    QHttpPart filePart;
    QString filePartHeader=QString("form-data; name=\"file\"");
    QString newFileName;
    if(fileName==0 || (*fileName).isEmpty())
    {
       if(key!=0 && !(*key).isEmpty())
       {
           newFileName=QString(*key);
       }
       else
       {
           newFileName=QString(QNUtils::randomFileName());
       }
    }
    else
    {
        newFileName=QString(*fileName);
    }
    filePartHeader.append("; filename=\"").append(newFileName).append("\"");
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant(filePartHeader));
    filePart.setBody(data);
    //set mime type if specified
    if(putExtra!=0){
        QString *mimeType=putExtra->getMimeType();
        if(!(*mimeType).isEmpty())
        {
            filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                               QVariant(*mimeType));
        }
    }
    //crc32

    //pack multi part
    multiPart->append(tokenPart);
    if(keyPart!=0)
    {
        multiPart->append(*keyPart);
    }
    multiPart->append(filePart);
    return multiPart;
}
