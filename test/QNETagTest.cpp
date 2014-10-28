#include "QNETagTest.h"
#include "QNETag.h"
#include <iostream>

void QNETagTest::fileETagTest()
{
    QNETag x;
    QString fileName="/Users/jemy/QiniuCloud/Projects/qt-qiniu-demo/go_sign.go";
    QString etag=x.calcETag(&fileName);
    std::cout<<etag.toStdString()<<std::endl;

    fileName="/Users/jemy/Movies/肖申克的救赎.rmvb";
    etag=x.calcETag(&fileName);
    std::cout<<etag.toStdString()<<std::endl;
}


//QNETagTest t;
//QTest::qExec(&t);
