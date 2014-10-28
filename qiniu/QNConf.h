#ifndef QNCONF_H
#define QNCONF_H

class QString;
class QByteArray;

class QNConf
{
public:
    static const QString UPLOAD_HOST;
    static const QString RS_HOST;
    static const QString RSF_HOST;
    static const QString IOVIP_HOST;

    static const QString ACCESS_KEY;
    static const QByteArray SECRET_KEY;

    static const QString DEFAULT_STYLE_DELIMITER;

    static const QString VERSION;

    QNConf();
};

#endif // QNCONF_H
