#include "QNPutRet.h"
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

QNPutRet::QNPutRet()
{
    this->hash=0;
    this->key=0;
}

QNPutRet::~QNPutRet()
{
    if(this->hash!=0)
    {
        delete this->hash;
    }
    if(this->key!=0)
    {
        delete this->key;
    }
}

QNPutRet* QNPutRet::fromJSON(const QByteArray &jsonData)
{
    QNPutRet *putRet=new QNPutRet;
    QJsonDocument doc;
    doc=QJsonDocument::fromJson(jsonData);//check error
    QJsonObject json=doc.object();
    QString *hash=new QString;
    hash->append(json["hash"].toString());
    QString *key=new QString;
    key->append(json["key"].toString());
    putRet->setHash(hash);
    putRet->setKey(key);
    return putRet;
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
