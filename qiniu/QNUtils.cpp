#include "QNUtils.h"
#include <QByteArray>
#include <QString>
#include <QCryptographicHash>
#include <QUrl>


const char QNUtils::KEY_ESCAPE_UNRESERVE_BYTES[] = {'!', '*', '\'', '(', ')', ';', ':', '@',
                                                    '&', '=', '+', '$', ',', '/', '#', '[', ']' };

const char QNUtils::KEY_ESCAPE_RESERVE_BYTES[] = {'?'};

QNUtils::QNUtils()
{
}

QNUtils::~QNUtils()
{

}

// Url safe base64 encode
QString QNUtils::urlSafeBase64Encode(const QByteArray &data)
{
    QByteArray encodedData = data.toBase64(QByteArray::Base64UrlEncoding);
    return QString(encodedData);
}

// Url safe base64 decode
QByteArray QNUtils::urlSafeBase64Decode(const QString &data)
{
    QByteArray bytesToDecode=QByteArray(data.toLocal8Bit());
    return QByteArray::fromBase64(bytesToDecode);
}

// Sha1 hash
QByteArray QNUtils::sha1(const QByteArray &data)
{
    QCryptographicHash sha1Hash(QCryptographicHash::Sha1);
    sha1Hash.addData(data);
    return sha1Hash.result();
}

// Hmac sha1 hash using secret key
QByteArray QNUtils::hmacSha1(const QByteArray &data, const QByteArray &secretKey)
{
    int blockSize = 64;
    QByteArray newSecretKey=QByteArray(secretKey);
    if (newSecretKey.length() > blockSize) {
        newSecretKey = QCryptographicHash::hash(newSecretKey, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36));
    QByteArray outerPadding(blockSize, char(0x5c));

    for (int i = 0; i < secretKey.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ secretKey.at(i);
        outerPadding[i] = outerPadding[i] ^ secretKey.at(i);
    }

    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(data);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    return hashed;
}

// Url escaped key
// @see http://kb.qiniu.com/52slk76w
// @see http://en.wikipedia.org/wiki/Percent-encoding
QString QNUtils::escapeKey(const QString &key)
{
    return QUrl::toPercentEncoding(key,QNUtils::KEY_ESCAPE_UNRESERVE_BYTES,QNUtils::KEY_ESCAPE_RESERVE_BYTES);
}
