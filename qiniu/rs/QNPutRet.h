#ifndef QNPUTRET_H
#define QNPUTRET_H

class QByteArray;
class QString;

class QNPutRet
{
private:
    QString *hash;
    QString *key;
public:
    QNPutRet();
    ~QNPutRet();
    static void fromJSON(const QByteArray &json, QNPutRet *putRet);

    QString *getHash() const;
    void setHash(QString *value);

    QString *getKey() const;
    void setKey(QString *value);
};

#endif // QNPUTRET_H
