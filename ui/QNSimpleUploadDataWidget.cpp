#include "QNSimpleUploadDataWidget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QNetworkReply>
#include "qiniu/conf/QNConf.h"
#include "qiniu/io/QNIOHelper.h"
#include "qiniu/rs/QNPutPolicy.h"
#include "qiniu/auth/QNMac.h"
#include "ui/QNMainWindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include "qiniu/rs/QNPutRet.h"
#include <QSettings>

QNSimpleUploadDataWidget::QNSimpleUploadDataWidget(QNetworkAccessManager *networkManager,
                                                   QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("Simple Upload Data"));
    this->networkManager=networkManager;
    this->createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);
}

void QNSimpleUploadDataWidget::createLayout()
{
    int labelMinWidth=80;
    int editMinWidth=500;

    putDataTextEdit=new QTextEdit(this);
    putDataTextEdit->setPlaceholderText(tr("Optional"));
    putDataTextEdit->setAcceptRichText(false);
    putDataTextEdit->setMinimumWidth(editMinWidth);
    accessKeyLineEdit=new QLineEdit(this);
    accessKeyLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit->setMinimumWidth(editMinWidth);
    secretKeyLineEdit=new QLineEdit(this);
    secretKeyLineEdit->setPlaceholderText(tr("Required"));
    secretKeyLineEdit->setMinimumWidth(editMinWidth);
    bucketLineEdit=new QLineEdit(this);
    bucketLineEdit->setPlaceholderText(tr("Required"));
    bucketLineEdit->setMinimumWidth(editMinWidth);
    keyLineEdit=new QLineEdit(this);
    keyLineEdit->setPlaceholderText(tr("Optional"));
    keyLineEdit->setMinimumWidth(editMinWidth);
    fileNameLineEdit=new QLineEdit(this);
    fileNameLineEdit->setPlaceholderText(tr("Optional"));
    fileNameLineEdit->setMinimumWidth(editMinWidth);
    uploadButton=new QPushButton(tr("Upload Data"));

    QLabel *putDataLabel=new QLabel(tr("Data:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    accessKeyLabel->setMinimumWidth(labelMinWidth);
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    secretKeyLabel->setMinimumWidth(labelMinWidth);
    QLabel *bucketLabel=new QLabel(tr("Bucket:"));
    bucketLabel->setMinimumWidth(labelMinWidth);
    QLabel *keyLabel=new QLabel(tr("Key:"));
    keyLabel->setMinimumWidth(labelMinWidth);
    QLabel *fileNameLabel=new QLabel(tr("File Name:"));
    fileNameLabel->setMinimumWidth(labelMinWidth);

    QVBoxLayout *putDataLayout=new QVBoxLayout;
    putDataLayout->addWidget(putDataLabel);
    putDataLayout->addWidget(putDataTextEdit);

    QHBoxLayout *accessKeyLayout=new QHBoxLayout;
    accessKeyLayout->addWidget(accessKeyLabel);
    accessKeyLayout->addWidget(accessKeyLineEdit);

    QHBoxLayout *secretKeyLayout=new QHBoxLayout;
    secretKeyLayout->addWidget(secretKeyLabel);
    secretKeyLayout->addWidget(secretKeyLineEdit);

    QHBoxLayout *bucketLayout=new QHBoxLayout;
    bucketLayout->addWidget(bucketLabel);
    bucketLayout->addWidget(bucketLineEdit);

    QHBoxLayout *keyLayout=new QHBoxLayout;
    keyLayout->addWidget(keyLabel);
    keyLayout->addWidget(keyLineEdit);

    QHBoxLayout *fileNameLayout=new QHBoxLayout;
    fileNameLayout->addWidget(fileNameLabel);
    fileNameLayout->addWidget(fileNameLineEdit);

    QHBoxLayout *uploadButtonLayout=new QHBoxLayout;
    uploadButtonLayout->addStretch();
    uploadButtonLayout->addWidget(uploadButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(putDataLayout);
    mainLayout->addLayout(accessKeyLayout);
    mainLayout->addLayout(secretKeyLayout);
    mainLayout->addLayout(bucketLayout);
    mainLayout->addLayout(keyLayout);
    mainLayout->addLayout(fileNameLayout);
    mainLayout->addLayout(uploadButtonLayout);

    this->setLayout(mainLayout);

    connect(uploadButton, SIGNAL(clicked()),this,SLOT(uploadData()));
    this->setMinimumWidth(500);
    this->setMinimumHeight(400);
}

void QNSimpleUploadDataWidget::uploadData()
{

    QString data=putDataTextEdit->document()->toPlainText().trimmed();
    QString accessKey=accessKeyLineEdit->text().trimmed();
    QString secretKey=secretKeyLineEdit->text().trimmed();
    QString bucket=bucketLineEdit->text().trimmed();
    QString key=keyLineEdit->text().trimmed();
    QString fileName=fileNameLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey, secretKeyBytes);
    QNPutPolicy policy(bucket);
    QString uploadToken=policy.makeUploadToken(&mac);
    QHttpMultiPart *multiPart=QNIOHelper::createPutDataMultiPart(uploadToken,
                                                                 data.toLocal8Bit(),&key,&fileName,0);
    QNetworkRequest request;
    request.setUrl(QUrl(QNConf::UPLOAD_HOST));
    QNetworkReply *reply=this->networkManager->post(request,multiPart);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(handleError(QNetworkReply::NetworkError)));

}

void QNSimpleUploadDataWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray respData=reply->readAll();
            QNPutRet *putRet=QNPutRet::fromJSON(respData);
            delete putRet;
        } else {
            //get http status code
            int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            //do some error management
        }
        reply->deleteLater();
    }
}

void QNSimpleUploadDataWidget::handleError(QNetworkReply::NetworkError)
{


}
