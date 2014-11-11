#include "QNPutExtra.h"
#include <QString>
#include <QMap>

QNPutExtra::QNPutExtra()
{
    this->params=new QMap<QString,QString>();
    this->mimeType=0;
    this->crc32=-1;
    this->checkCrc32=-1;
}

void QNPutExtra::addExtraParam(const QString &key, const QString &value)
{
    this->params->insert(key,value);
}

QString QNPutExtra::removeExtraParam(const QString &key) const
{
    QString value=QString::null;
    if(this->params->contains(key))
    {
        value=this->params->value(key);
        this->params->remove(key);
    }
    return value;
}

QNPutExtra::~QNPutExtra()
{
    if(this->params!=0)
    {
        delete this->params;
    }
}

QString *QNPutExtra::getMimeType() const
{
    return mimeType;
}

void QNPutExtra::setMimeType(QString *value)
{
    mimeType = value;
}

qint32 QNPutExtra::getCrc32() const
{
    return crc32;
}

void QNPutExtra::setCrc32(const qint32 &value)
{
    crc32 = value;
}

qint32 QNPutExtra::getCheckCrc32() const
{
    return checkCrc32;
}

void QNPutExtra::setCheckCrc32(const qint32 &value)
{
    checkCrc32 = value;
}
