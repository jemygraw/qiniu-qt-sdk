#ifndef QNPUTEXTRA_H
#define QNPUTEXTRA_H
#include <QtGlobal>
#include <QMap>

class QString;

class QNPutExtra
{
private:
    QMap<QString, QString> *params;
    QString *mimeType;
    qint32 crc32;
    qint32 checkCrc32;
public:
    static const int NO_CRC32 = 0;
    static const int AUTO_CRC32 = 1;
    static const int WITH_CRC32 = 2;

    QNPutExtra();
    ~QNPutExtra();

    void addExtraParam(const QString &key, const QString &value);
    QString removeExtraParam(const QString &key) const;

    QString *getMimeType() const;
    void setMimeType(QString *value);

    qint32 getCrc32() const;
    void setCrc32(const qint32 &value);


    qint32 getCheckCrc32() const;
    void setCheckCrc32(const qint32 &value);
};

#endif // QNPUTEXTRA_H
