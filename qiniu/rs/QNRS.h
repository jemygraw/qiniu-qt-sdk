#ifndef QNRS_H
#define QNRS_H

class QString;
class QStringList;
class QNetworkRequest;
class QNMac;
class QNRS
{
public:
    QNRS();
    static QNetworkRequest statRequest(const QString &bucket, const QString &key,
                                       const QNMac *mac=0);

    static QNetworkRequest copyRequest(const QString &srcBucket, const QString &srcKey,
                                       const QString &destBucket, const QString &destKey,
                                       const QNMac *mac=0);

    static QNetworkRequest moveRequest(const QString &srcBucket, const QString &srcKey,
                                       const QString &destBucket, const QString &destKey,
                                       const QNMac *mac=0);

    static QNetworkRequest batchRequest(const QStringList &operations,
                                        const QNMac *mac=0);

    static QNetworkRequest chgmRequest(const QString &bucket, const QString &key,
                                       const QString &newMimeType,
                                       const QNMac *mac=0);
};

#endif // QNRS_H
