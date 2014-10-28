#ifndef QNIO_H
#define QNIO_H
#include "qiniu/rs/QNPutExtra.h"

class QString;
class QFile;
class QByteArray;

class QNIO
{
public:
    QNIO();

    void PutDataSync(const QString &uploadToken, const QByteArray &data,
                 const QString *key=NULL, const QNPutExtra *putExtra=NULL);
    void PutFileSync(const QString &uploadToken, const QFile &localFile,
                 const QString *key=NULL, const QNPutExtra *putExtra=NULL);

    void PutDataAsync(const QString &uploadToken, const QByteArray &data,
                     const QString *key=NULL, const QNPutExtra *putExtra=NULL);
    void PutFileAsync(const QString &uploadToken, const QFile &localFile,
                 const QString *key=NULL, const QNPutExtra *putExtra=NULL);
};

#endif // QNIO_H
