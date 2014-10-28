#ifndef QNETAG_H
#define QNETAG_H
class QString;
class QByteArray;

class QNETag
{
private:
    const static int CHUNK_SIZE = 1<<22; //4M
public:
    QNETag();
    ~QNETag();
    QString calcETag(QString *fileName);
};

#endif // QNETAG_H
