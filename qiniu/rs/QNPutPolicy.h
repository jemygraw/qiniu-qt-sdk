#ifndef QNPUTPOLICY_H
#define QNPUTPOLICY_H

#include <QtGlobal>

class QString;
class QNMac;

//@see http://developer.qiniu.com/docs/v6/api/reference/security/put-policy.html
class QNPutPolicy
{
private:
    QString &scope;
    qint32 deadline;

    qint16 insertOnly; //optional, default 0
    QString *saveKey;   //optional
    QString *endUser;   //optional

    qint64 fSizeLimit;  //optional

    //let qiniu server dectect file mime type
    //1. check file name extension
    //2. check key extension
    //3. check file content
    //default is 0, auto use the specified mimetype
    //or check by step 1,2,3
    //if the server cannot figure out the mimetype,
    //use application/octet-stream
    qint16 detectMime; //optional, default 0
    QString *mimeLimit; //optional

    QString *callbackUrl;   //optional
    QString *callbackHost;  //optional
    QString *callbackBody;  //optional
    qint16 callbackFetchKey; //optional

    QString *returnUrl;     //optional
    QString *returnBody;    //optional

    QString *persistentOps;         //optional
    QString *persistentNotifyUrl;   //optional
    QString *persistentPipeline;    //optional


public:
    QNPutPolicy(QString &scope);
    QByteArray toJSON(bool compact=true);
    QString makeUploadToken(const QNMac *mac=0);

    //getters & setters
    QString getScope() const;
    void setScope(const QString &value);

    qint32 getDeadline() const;
    void setDeadline(const qint32 &value);


    quint16 getInsertOnly() const;
    void setInsertOnly(const quint16 &value);

    QString *getSaveKey() const;
    void setSaveKey(QString *value);

    QString *getEndUser() const;
    void setEndUser(QString *value);

    qint64 getFSizeLimit() const;
    void setFSizeLimit(const qint64 &value);

    qint16 getDetectMime() const;
    void setDetectMime(const qint16 &value);

    QString *getMimeLimit() const;
    void setMimeLimit(QString *value);

    QString *getCallbackUrl() const;
    void setCallbackUrl(QString *value);

    QString *getCallbackHost() const;
    void setCallbackHost(QString *value);

    QString *getCallbackBody() const;
    void setCallbackBody(QString *value);

    qint16 getCallbackFetchKey() const;
    void setCallbackFetchKey(const qint16 &value);

    QString *getReturnUrl() const;
    void setReturnUrl(QString *value);

    QString *getReturnBody() const;
    void setReturnBody(QString *value);

    QString *getPersistentOps() const;
    void setPersistentOps(QString *value);

    QString *getPersistentNotifyUrl() const;
    void setPersistentNotifyUrl(QString *value);

    QString *getPersistentPipeline() const;
    void setPersistentPipeline(QString *value);

};

#endif // QNPUTPOLICY_H
