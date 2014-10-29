#include "QNPutPolicy.h"
#include "qiniu/utils/QNUtils.h"
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include "qiniu/auth/QNMac.h"
#include "qiniu/conf/QNConf.h"

QNPutPolicy::QNPutPolicy(QString &scope):scope(scope)
{
    //default is 1970/1/1, timestamp is 0
    deadline=0;

    detectMime=-1;
    fSizeLimit=-1;
    insertOnly=-1;

    this->saveKey=NULL;
    this->endUser=NULL;
    this->mimeLimit=NULL;
    this->callbackUrl=NULL;
    this->callbackHost=NULL;
    this->callbackBody=NULL;
    this->returnUrl=NULL;
    this->returnBody=NULL;
    this->persistentOps=NULL;
    this->persistentNotifyUrl=NULL;
    this->persistentPipeline=NULL;
}

QByteArray QNPutPolicy::toJSON(bool compact)
{
    QJsonObject json=QJsonObject();
    json["scope"]=scope;
    json["deadline"]=deadline;

    if(insertOnly!=-1)
    {
        json["insertOnly"]=insertOnly;
    }
    if(fSizeLimit!=-1)
    {
        json["fSizeLimit"]=fSizeLimit;
    }
    if(detectMime!=-1)
    {
        json["detectMime"]=detectMime;
    }
    if(QNUtils::isParamValid(saveKey))
    {
        json["saveKey"]=*saveKey;
    }
    if(QNUtils::isParamValid(endUser))
    {
        json["endUser"]=*endUser;
    }
    if(QNUtils::isParamValid(mimeLimit))
    {
        json["mimeLimit"]=*mimeLimit;
    }
    if(QNUtils::isParamValid(callbackUrl))
    {
        json["callbackUrl"]=*callbackUrl;
    }
    if(QNUtils::isParamValid(callbackHost))
    {
        json["callbackHost"]=*callbackHost;
    }
    if(QNUtils::isParamValid(callbackBody))
    {
        json["callbackBody"]=*callbackBody;
    }
    if(QNUtils::isParamValid(returnUrl))
    {
        json["returnUrl"]=*returnUrl;
    }
    if(QNUtils::isParamValid(returnBody))
    {
        json["returnBody"]=*returnBody;
    }
    if(QNUtils::isParamValid(persistentOps))
    {
        json["persistentOps"]=*persistentOps;
    }
    if(QNUtils::isParamValid(persistentNotifyUrl))
    {
        json["persistentNotifyUrl"]=*persistentNotifyUrl;
    }
    if(QNUtils::isParamValid(persistentPipeline))
    {
        json["persistentPipeline"]=*persistentPipeline;
    }

    QJsonDocument doc=QJsonDocument(json);
    QJsonDocument::JsonFormat f;
    if(compact)
    {
        f=QJsonDocument::Compact;
    }
    else
    {
        f=QJsonDocument::Indented;
    }
    QByteArray data=doc.toJson(f);
    return data;
}

QString QNPutPolicy::makeUploadToken(const QNMac *mac)
{
    // check whether deadline set, otherwise default is one hour
    if(this->deadline==0)
    {
        this->deadline=QNUtils::expireInSeconds(3600);
    }
    QByteArray putPolicyJson=this->toJSON();
    QString uploadToken;
    if(mac!=NULL)
    {
        uploadToken=mac->signWithData(putPolicyJson);
    }
    else
    {
        QNMac *macx= new QNMac(&QNConf::ACCESS_KEY,&QNConf::SECRET_KEY);
        uploadToken=macx->signWithData(putPolicyJson);
    }
    return uploadToken;
}

qint32 QNPutPolicy::getDeadline() const
{
    return deadline;
}

void QNPutPolicy::setDeadline(const qint32 &value)
{
    deadline = value;
}

QString QNPutPolicy::getScope() const
{
    return scope;
}

void QNPutPolicy::setScope(const QString &value)
{
    scope = value;
}

quint16 QNPutPolicy::getInsertOnly() const
{
    return insertOnly;
}

void QNPutPolicy::setInsertOnly(const quint16 &value)
{
    insertOnly = value;
}

QString *QNPutPolicy::getSaveKey() const
{
    return saveKey;
}

void QNPutPolicy::setSaveKey(QString *value)
{
    saveKey = value;
}

QString *QNPutPolicy::getEndUser() const
{
    return endUser;
}

void QNPutPolicy::setEndUser(QString *value)
{
    endUser = value;
}

qint64 QNPutPolicy::getFSizeLimit() const
{
    return fSizeLimit;
}

void QNPutPolicy::setFSizeLimit(const qint64 &value)
{
    fSizeLimit = value;
}

qint16 QNPutPolicy::getDetectMime() const
{
    return detectMime;
}

void QNPutPolicy::setDetectMime(const qint16 &value)
{
    detectMime = value;
}

QString *QNPutPolicy::getMimeLimit() const
{
    return mimeLimit;
}

void QNPutPolicy::setMimeLimit(QString *value)
{
    mimeLimit = value;
}

QString *QNPutPolicy::getCallbackUrl() const
{
    return callbackUrl;
}

void QNPutPolicy::setCallbackUrl(QString *value)
{
    callbackUrl = value;
}

QString *QNPutPolicy::getCallbackHost() const
{
    return callbackHost;
}

void QNPutPolicy::setCallbackHost(QString *value)
{
    callbackHost = value;
}

QString *QNPutPolicy::getCallbackBody() const
{
    return callbackBody;
}

void QNPutPolicy::setCallbackBody(QString *value)
{
    callbackBody = value;
}

QString *QNPutPolicy::getReturnUrl() const
{
    return returnUrl;
}

void QNPutPolicy::setReturnUrl(QString *value)
{
    returnUrl = value;
}

QString *QNPutPolicy::getReturnBody() const
{
    return returnBody;
}

void QNPutPolicy::setReturnBody(QString *value)
{
    returnBody = value;
}

QString *QNPutPolicy::getPersistentOps() const
{
    return persistentOps;
}

void QNPutPolicy::setPersistentOps(QString *value)
{
    persistentOps = value;
}

QString *QNPutPolicy::getPersistentNotifyUrl() const
{
    return persistentNotifyUrl;
}

void QNPutPolicy::setPersistentNotifyUrl(QString *value)
{
    persistentNotifyUrl = value;
}

QString *QNPutPolicy::getPersistentPipeline() const
{
    return persistentPipeline;
}

void QNPutPolicy::setPersistentPipeline(QString *value)
{
    persistentPipeline = value;
}
