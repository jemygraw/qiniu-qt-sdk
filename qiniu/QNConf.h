#ifndef QNCONF_H
#define QNCONF_H

class QString;
class QByteArray;

class QNConf
{
public:
    static QString UPLOAD_HOST;
    static QString RS_HOST;
    static QString RSF_HOST;
    static QString IOVIP_HOST;

    static QString ACCESS_KEY;
    static QByteArray SECRET_KEY;

    static QString DEFAULT_STYLE_DELIMITER;

    static QString VERSION;

    QNConf();
};

#endif // QNCONF_H
