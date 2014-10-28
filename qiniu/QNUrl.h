#ifndef QNURL_H
#define QNURL_H

class QString;
class QDateTime;
class QNMac;

class QNUrl
{
private:
    QString *styleDelimiter;

public:
    QNUrl(QString *styleDelimiter);
    ~QNUrl();
    QString makePublicSimpleUrl(QString *domain, QString *key, QString *fop, bool isAlias);
    QString makePrivateSimpleUrl(QString *domain, QString *key, QNMac *mac, QDateTime *deadline, QString *fop, bool isAlias);
};

#endif // QNURL_H
