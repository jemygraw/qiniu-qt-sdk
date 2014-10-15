#ifndef QNUTILS_H
#define QNUTILS_H

class QString;
class QByteArray;

class QNUtils
{
public:
    QNUtils();
    static QString urlSafeBase64Encode(QByteArray data);
    static QByteArray urlSafeBase64Decode(QString data);
};

#endif // QNUTILS_H
