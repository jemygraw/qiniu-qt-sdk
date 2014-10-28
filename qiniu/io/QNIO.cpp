#include "QNIO.h"
#include <QFile>

QNIO::QNIO()
{
}

void QNIO::PutFileSync(const QString &uploadToken, const QFile &localFile,
              const QString *key, const QNPutExtra *putExtra)
{

}

void QNIO::PutDataSync(const QString &uploadToken, const QByteArray &data,
              const QString *key, const QNPutExtra *putExtra)
{

}
