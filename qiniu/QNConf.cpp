#include "QNConf.h"
#include <QString>

// Upload & Resource Management Host
const QString QNConf::UPLOAD_HOST = QString("http://upload.qiniu.com");
const QString QNConf::RS_HOST = QString("http://rs.qbox.me");
const QString QNConf::RSF_HOST = QString("http://rsf.qbox.me");
const QString QNConf::IOVIP_HOST = QString("http://iovip.qbox.me");

//  Access Key & Secret Key
const QString QNConf::ACCESS_KEY = QString("<Your Access Key>");
const QByteArray QNConf::SECRET_KEY = QByteArray("<Your Secret Key>");

// Style Delimiter
const QString QNConf::DEFAULT_STYLE_DELIMITER = QString("-");

// Version
const QString QNConf::VERSION = QString("1.0.0");

QNConf::QNConf()
{
}

//std::cout<< QNConf::UPLOAD_HOST.toStdString()<<std::endl;
//std::cout<< QNConf::RS_HOST.toStdString()<<std::endl;
//std::cout<< QNConf::RSF_HOST.toStdString()<<std::endl;
//std::cout<< QNConf::IOVIP_HOST.toStdString()<<std::endl;
