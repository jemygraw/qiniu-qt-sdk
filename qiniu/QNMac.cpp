#include "QNMac.h"
#include "QNUtils.h"
#include <QString>
#include <QByteArray>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QUrl>
#include <QtCore/QVariant>
#include <QtGlobal>

// Use access key and secret key from https://portal.qiniu.com
QNMac::QNMac(QString &accesKey, QByteArray &secretKey)
    :accessKey(accesKey),secretKey(secretKey)
{
}

QNMac::~QNMac()
{

}

bool QNMac::isNull() const
{
    bool isnull=false;
    if(this->accessKey.isEmpty() || this->secretKey.isNull())
    {
        isnull=true;
    }
    return isnull;
}

// Sign data
// Mainly used to create the private bucket download token

// 1. Use hmac sha1 algorithm to sign data with secret key
// 2. Use url safe base64 encoding to encode the result data from step1
// 3. Join access key and the result string from step2 with ':'
QString QNMac::sign(const QByteArray &data) const
{
    QByteArray signedData=QNUtils::hmacSha1(data,this->secretKey);
    QString retStr=QString(this->accessKey);
    retStr.append(":");
    retStr.append(QNUtils::urlSafeBase64Encode(signedData));
    return retStr;
}

// Encode data and sign it
// Mainly used to create the encoded and signed put policy token

// 1. First encode the data with url safe base64
// 2. Use hmac sha1 algorithm to sign the result data from step1 with secret key
// 3. Use url safe base64 encoding to encode the result data from step2
// 4. Join access key and the result string from step3 and the result string from
// step1 with ':'
QString QNMac::signWithData(const QByteArray &data) const
{
    QString encodedData=QNUtils::urlSafeBase64Encode(data);
    QByteArray signedData=QNUtils::hmacSha1(encodedData.toLocal8Bit(),this->secretKey);
    QString encodedSignedData=QNUtils::urlSafeBase64Encode(signedData);
    QString retStr=QString(this->accessKey);
    retStr.append(":").append(encodedSignedData);
    retStr.append(":").append(encodedData);
    return retStr;
}

// Sign http request and body
// Mainly used to create the resource management auth token

// 1. Create url to sign, format is <path>\n or <path>?<query>\n or <path>?<query>\nbody
// 2. Use hmac sha1 algorithm to sign the url in step1
// 3. Use url safe base64 encoding to encode the result data from step2
// 4. Join access key and the result string from step3 with ':'
QString QNMac::signRequest(const QNetworkRequest &request,const QByteArray *bodyData) const
{
    QUrl uri=request.url();
    QString path=uri.path();
    QString query=uri.query();
    QByteArray dataToSign=path.toUtf8();
    // check query whether empty
    if(!query.isEmpty()){
        dataToSign.append("?").append(query);
    }
    dataToSign.append("\n");
    // check whether with body
    if (bodyData!=NULL && !bodyData->isEmpty())
    {
        dataToSign.append(*bodyData);
    }
    QByteArray signedData=QNUtils::hmacSha1(dataToSign,this->secretKey);
    QString encodedSignedData=QNUtils::urlSafeBase64Encode(signedData);
    QString retStr=QString(this->accessKey);
    retStr.append(":").append(encodedSignedData);
    return retStr;
}
