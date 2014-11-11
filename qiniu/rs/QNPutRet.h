#ifndef QNPUTRET_H
#define QNPUTRET_H

class QByteArray;
class QString;

class QNPutRet
{
private:
    QString *hash;
    QString *key;
    QString *error;
    int code;
public:
    QNPutRet();
    ~QNPutRet();
    static QNPutRet* fromJSON(const QByteArray &json);

    QString *getHash() const;
    void setHash(QString *value);

    QString *getKey() const;
    void setKey(QString *value);
};

#endif // QNPUTRET_H
