#ifndef QNIOHELPER_H
#define QNIOHELPER_H
#include "qiniu/rs/QNPutExtra.h"
#include <QObject>
#include <QHttpMultiPart>

class QString;
class QFile;
class QByteArray;

class QNetworkAccessManager;

class QNIOHelper
{

public:
    static QHttpMultiPart* createPutDataMultiPart(const QString &uploadToken, const QByteArray &data,
                     const QString *key=0, const QString *fileName=0,
                     const QNPutExtra *putExtra=0);

    static QHttpMultiPart* createPutFileMultiPart(const QString &uploadToken, const QFile &localFile,
                const QString *key=0, const QNPutExtra *putExtra=0);
};

#endif // QNIO_H
