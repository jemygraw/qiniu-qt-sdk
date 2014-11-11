#ifndef QNUTILS_H
#define QNUTILS_H
#include <QtGlobal>

class QString;
class QByteArray;

class QNUtils
{
public:
    QNUtils();
    ~QNUtils();
    static const char KEY_ESCAPE_RESERVE_BYTES[];
    static const char KEY_ESCAPE_UNRESERVE_BYTES[];
    static QString urlSafeBase64Encode(const QByteArray &data);
    static QByteArray urlSafeBase64Decode(const QString &data);
    static QByteArray sha1(const QByteArray &data);
    static QByteArray hmacSha1(const QByteArray &data, const QByteArray &secretKey);
    static QString escapeKey(const QString &key);
    static bool isParamValid(const QString *param);
    static uint expireInSeconds(const uint seconds);
    static uint crc32(const QByteArray &data);
    static QString randomFileName();
};

#endif // QNUTILS_H
