#include "QNUtils.h"
#include <QByteArray>
#include <QString>

QNUtils::QNUtils()
{
}

QString QNUtils::urlSafeBase64Encode(QByteArray data)
{
    QByteArray encodedData = data.toBase64(QByteArray::Base64UrlEncoding);
    return QString(encodedData);
}

QByteArray QNUtils::urlSafeBase64Decode(QString data)
{
    QByteArray bytesToDecode=QByteArray(data.toLocal8Bit());
    return QByteArray::fromBase64(bytesToDecode);
}
