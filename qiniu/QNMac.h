#ifndef QNMAC_H
#define QNMAC_H

class QString;
class QByteArray;
class QNetworkRequest;

class QNMac
{
private:
    QString *accessKey;
    QByteArray *secretKey;

public:
    QNMac(QString *accessKey, QByteArray *secretKey);
    ~QNMac();
    QString sign(const QByteArray *data);
    QString signWithData(const QByteArray *data);
    QString signRequest(const QNetworkRequest *request, const QByteArray *bodyData);
};

#endif // QNMAC_H
