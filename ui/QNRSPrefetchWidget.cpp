#include "QNRSPrefetchWidget.h"
#include "qiniu/auth/QNMac.h"
#include "qiniu/rs/QNRS.h"
#include <QNetworkAccessManager>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSettings>

QNRSPrefetchWidget::QNRSPrefetchWidget(QNetworkAccessManager &networkManager, QWidget *parent) :
    QWidget(parent),networkManager(networkManager)
{
    this->setWindowTitle(tr("Prefetch - Prefetch Mirror Resource"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);
}

void QNRSPrefetchWidget::createLayout()
{
    QGridLayout *mainGridLayout=new QGridLayout;
    QLabel *bucketLabel=new QLabel(tr("Bucket:"));
    QLabel *keyLabel=new QLabel(tr("Key:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *prefetchResultHttpCodeLabel=new QLabel(tr("Http Code:"));
    QLabel *prefetchResultLabel=new QLabel(tr("Prefetch Result:"));

    bucketLineEdit=new QLineEdit;
    bucketLineEdit->setPlaceholderText(tr("Required"));
    keyLineEdit=new QLineEdit;
    keyLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    prefetchResultHttpCodeLineEdit=new QLineEdit;
    prefetchResultHttpCodeLineEdit->setReadOnly(true);
    prefetchResultLineEdit=new QLineEdit;
    prefetchResultLineEdit->setReadOnly(true);

    mainGridLayout->addWidget(bucketLabel,1,0);
    mainGridLayout->addWidget(bucketLineEdit,1,1);
    mainGridLayout->addWidget(keyLabel,2,0);
    mainGridLayout->addWidget(keyLineEdit,2,1);
    mainGridLayout->addWidget(accessKeyLabel,3,0);
    mainGridLayout->addWidget(accessKeyLineEdit,3,1);
    mainGridLayout->addWidget(secretKeyLabel,4,0);
    mainGridLayout->addWidget(secretKeyLineEdit,4,1);
    mainGridLayout->addWidget(prefetchResultHttpCodeLabel,5,0);
    mainGridLayout->addWidget(prefetchResultHttpCodeLineEdit,5,1);
    mainGridLayout->addWidget(prefetchResultLabel,6,0);
    mainGridLayout->addWidget(prefetchResultLineEdit,6,1);

    QHBoxLayout *actionLayout=new QHBoxLayout;
    prefetchButton=new QPushButton(tr("Prefetch"));
    actionLayout->addStretch();
    actionLayout->addWidget(prefetchButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);
    this->setMinimumWidth(600);
    this->setMinimumHeight(200);

    connect(prefetchButton,SIGNAL(clicked()),this,SLOT(prefetchSlot()));
}

void QNRSPrefetchWidget::prefetchSlot()
{
    QString accessKey=accessKeyLineEdit->text().trimmed();
    QString secretKey=secretKeyLineEdit->text().trimmed();
    QString bucket=bucketLineEdit->text().trimmed();
    QString key=keyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);

    QNetworkRequest request=QNRS::prefetchRequest(bucket,key,&mac);
    QByteArray postData;
    QNetworkReply *reply=networkManager.post(request,postData);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(handleError(QNetworkReply::NetworkError)));
}

void QNRSPrefetchWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        QByteArray respData=reply->readAll();
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        this->prefetchResultLineEdit->setText(respData);
        this->prefetchResultHttpCodeLineEdit->setText(QString::number(httpStatusCode));
        reply->deleteLater();
    }
}

void QNRSPrefetchWidget::handleError(QNetworkReply::NetworkError)
{

}
