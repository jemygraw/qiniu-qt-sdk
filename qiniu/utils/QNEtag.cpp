#include "QNETag.h"
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
#include "QNUtils.h"
QNETag::QNETag()
{
}
QNETag::~QNETag()
{
}

// Calculate the qiniu etag for the specified file
// The file must exists and readable

// 1. If the file size is smaller than or equal to 4M, the etag is the
// signed result of the whole file content using sha1. Prepend byte 0x16
// to the signed data and return the url safe base64 encoded string
// of the signed data.

// 2. If the file size is larger than 4M, you need to divide the file
// content bytes into a serial of data chunks by 4M (the last data chunk
// may be smaller than or equal to 4M). Sign each data chunk using sha1 and
// join them together to get a large data chunk and then sign it using sha1.
// Prepend 0x96 to the signed data and return the url safe base64 encoded string
// of the signed data.
QString QNETag::calcETag(const QString &fileName) const
{
    QString etag = "";
    QFileInfo fi(fileName);
    if(fi.exists() && fi.permission(QFile::ReadUser))
    {
        QFile fh(fileName);
        bool opened = fh.open(QIODevice::ReadOnly);
        if (opened){
            qint64 fileLen = fh.size();
            if(fileLen <= CHUNK_SIZE)
            {
                QByteArray fileData = fh.readAll();
                QByteArray sha1Data = QNUtils::sha1(fileData);
                QByteArray hashData = sha1Data;
                hashData.prepend(0x16);
                etag = QNUtils::urlSafeBase64Encode(hashData);
            }
            else
            {
                int chunkCount = fileLen / CHUNK_SIZE;
                if(fileLen % CHUNK_SIZE != 0)
                {
                    chunkCount += 1;
                }
                QByteArray sha1AllData;
                for(int i=0; i<chunkCount; i++)
                {
                    qint64 chunkSize = CHUNK_SIZE;
                    if(i == chunkCount-1)
                    {
                        chunkSize = fileLen-(chunkCount-1)*CHUNK_SIZE;
                    }
                    QByteArray buf=fh.read(chunkSize);
                    QByteArray sha1Data = QNUtils::sha1(buf);
                    sha1AllData.append(sha1Data);
                }
                QByteArray hashData = QNUtils::sha1(sha1AllData);
                hashData.prepend(0x96);
                etag = QNUtils::urlSafeBase64Encode(hashData);
            }
            fh.close();
        }
    }
    return etag;
}
