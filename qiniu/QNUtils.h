#ifndef QNUTILS_H
#define QNUTILS_H

class QString;
class QByteArray;

class QNUtils
{
public:
    QNUtils();
    ~QNUtils();
    static const char KEY_ESCAPE_RESERVE_BYTES[];
    static const char KEY_ESCAPE_UNRESERVE_BYTES[];
    static QString urlSafeBase64Encode(QByteArray data);
    static QByteArray urlSafeBase64Decode(QString data);
    static QByteArray sha1(QByteArray data);
    static QByteArray hmacSha1(QByteArray data, QByteArray secretKey);
    static QString escapeKey(QString key);
};

#endif // QNUTILS_H
