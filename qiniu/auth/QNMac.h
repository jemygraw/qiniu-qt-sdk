#ifndef QNMAC_H
#define QNMAC_H
#include <QObject>

class QString;
class QByteArray;
class QNetworkRequest;

class QNMac : public QObject
{
    Q_OBJECT

private:
    QString *accessKey;
    QByteArray *secretKey;

public:
    QNMac(QString *accessKey, QByteArray *secretKey, QObject *parent=0);
    ~QNMac();
    QString sign(const QByteArray &data) const;
    QString signWithData(const QByteArray &data) const;
    QString signRequest(const QNetworkRequest &request, const QByteArray *bodyData=0) const;
};

#endif // QNMAC_H
