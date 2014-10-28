#include "QNPutRet.h"
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

QNPutRet::QNPutRet()
{
    this->hash=NULL;
    this->key=NULL;
}

QNPutRet::~QNPutRet()
{
    if(this->hash!=NULL)
    {
        delete this->hash;
    }
    if(this->key!=NULL)
    {
        delete this->key;
    }
}

void QNPutRet::fromJSON(const QByteArray &jsonData, QNPutRet *putRet)
{
    QJsonDocument doc;
    doc=QJsonDocument::fromJson(jsonData);//check error
    QJsonObject json=doc.object();
    QString *hash=new QString;
    hash->append(json["hash"].toString());
    QString *key=new QString;
    key->append(json["key"].toString());
    putRet->setHash(hash);
    putRet->setKey(key);
    return;
}

QString *QNPutRet::getHash() const
{
    return hash;
}

void QNPutRet::setHash(QString *value)
{
    hash = value;
}

QString *QNPutRet::getKey() const
{
    return key;
}

void QNPutRet::setKey(QString *value)
{
    key = value;
}
