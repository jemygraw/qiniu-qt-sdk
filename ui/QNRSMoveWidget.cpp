#include "QNRSMoveWidget.h"
#include "qiniu/auth/QNMac.h"
#include "qiniu/rs/QNRS.h"
#include <QWidget>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QByteArray>
#include <QSettings>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

QNRSMoveWidget::QNRSMoveWidget(QNetworkAccessManager &networkManager, QWidget *parent)
    :QWidget(parent),networkManager(networkManager)
{
    this->setWindowTitle(tr("Move - Move Resource"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);
}

void QNRSMoveWidget::createLayout()
{
    QGridLayout *mainGridLayout=new QGridLayout;

    QLabel *srcBucketLabel=new QLabel(tr("Src Bucket:"));
    QLabel *srcKeyLabel=new QLabel(tr("Src Key:"));
    QLabel *destBucketLabel=new QLabel(tr("Dest Bucket:"));
    QLabel *destKeyLabel=new QLabel(tr("Dest Key:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *moveResultHttpCodeLabel=new QLabel(tr("Http Code:"));
    QLabel *moveResultLabel=new QLabel(tr("Move Result:"));

    srcBucketLineEdit=new QLineEdit;
    srcBucketLineEdit->setPlaceholderText(tr("Required"));
    srcKeyLineEdit=new QLineEdit;
    srcKeyLineEdit->setPlaceholderText(tr("Required"));
    destBucketLineEdit=new QLineEdit;
    destBucketLineEdit->setPlaceholderText(tr("Required"));
    destKeyLineEdit=new QLineEdit;
    destKeyLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;

    moveResultHttpCodeLineEdit=new QLineEdit;
    moveResultHttpCodeLineEdit->setReadOnly(true);
    moveResultLineEdit=new QLineEdit;
    moveResultLineEdit->setReadOnly(true);

    mainGridLayout->addWidget(srcBucketLabel,0,0);
    mainGridLayout->addWidget(srcBucketLineEdit,0,1);
    mainGridLayout->addWidget(srcKeyLabel,1,0);
    mainGridLayout->addWidget(srcKeyLineEdit,1,1);
    mainGridLayout->addWidget(destBucketLabel,2,0);
    mainGridLayout->addWidget(destBucketLineEdit,2,1);
    mainGridLayout->addWidget(destKeyLabel,3,0);
    mainGridLayout->addWidget(destKeyLineEdit,3,1);
    mainGridLayout->addWidget(accessKeyLabel,4,0);
    mainGridLayout->addWidget(accessKeyLineEdit,4,1);
    mainGridLayout->addWidget(secretKeyLabel,5,0);
    mainGridLayout->addWidget(secretKeyLineEdit,5,1);
    mainGridLayout->addWidget(moveResultHttpCodeLabel,6,0);
    mainGridLayout->addWidget(moveResultHttpCodeLineEdit,6,1);
    mainGridLayout->addWidget(moveResultLabel,7,0);
    mainGridLayout->addWidget(moveResultLineEdit,7,1);

    QHBoxLayout *actionLayout=new QHBoxLayout;
    moveButton=new QPushButton(tr("Move"));
    actionLayout->addStretch();
    actionLayout->addWidget(moveButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);

    this->setMinimumWidth(500);
    this->setMinimumHeight(300);

    connect(moveButton,SIGNAL(clicked()),this,SLOT(moveSlot()));
}

void QNRSMoveWidget::moveSlot()
{
    QString srcBucket=srcBucketLineEdit->text().trimmed();
    QString srcKey=srcKeyLineEdit->text().trimmed();
    QString destBucket=destBucketLineEdit->text().trimmed();
    QString destKey=destKeyLineEdit->text().trimmed();
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);
    QNetworkRequest request=QNRS::moveRequest(srcBucket,srcKey,destBucket,destKey,&mac);
    QByteArray postData;
    QNetworkReply *reply=networkManager.post(request,postData);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(handleError(QNetworkReply::NetworkError)));
}

void QNRSMoveWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        QByteArray respData=reply->readAll();
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        this->moveResultLineEdit->setText(respData);
        this->moveResultHttpCodeLineEdit->setText(QString::number(httpStatusCode));
        reply->deleteLater();
    }
}

void QNRSMoveWidget::handleError(QNetworkReply::NetworkError)
{

}
