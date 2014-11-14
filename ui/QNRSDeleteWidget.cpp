#include "QNRSDeleteWidget.h"
#include "qiniu/auth/QNMac.h"
#include "qiniu/rs/QNRS.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

QNRSDeleteWidget::QNRSDeleteWidget(QNetworkAccessManager &networkManager, QWidget *parent)
    :QWidget(parent),networkManager(networkManager)
{
    this->setWindowTitle(tr("Delete - Delete Resource"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);

}

void QNRSDeleteWidget::createLayout()
{
    QGridLayout *mainGridLayout=new QGridLayout;

    QLabel *bucketLabel=new QLabel(tr("Bucket:"));
    QLabel *keyLabel=new QLabel(tr("Key:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *rsDeleteResultHttpCodeLabel=new QLabel(tr("Http Code:"));
    QLabel *rsDeleteResultLabel=new QLabel(tr("Delete Result:"));

    bucketLineEdit=new QLineEdit;
    bucketLineEdit->setPlaceholderText(tr("Required"));
    keyLineEdit=new QLineEdit;
    keyLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    deleteResultHttpCodeLineEdit=new QLineEdit;
    deleteResultHttpCodeLineEdit->setReadOnly(true);
    deleteResultTextEdit=new QTextEdit;
    deleteResultTextEdit->setReadOnly(true);

    mainGridLayout->addWidget(bucketLabel,0,0);
    mainGridLayout->addWidget(bucketLineEdit,0,1);
    mainGridLayout->addWidget(keyLabel,1,0);
    mainGridLayout->addWidget(keyLineEdit,1,1);
    mainGridLayout->addWidget(accessKeyLabel,2,0);
    mainGridLayout->addWidget(accessKeyLineEdit,2,1);
    mainGridLayout->addWidget(secretKeyLabel,3,0);
    mainGridLayout->addWidget(secretKeyLineEdit,3,1);
    mainGridLayout->addWidget(rsDeleteResultHttpCodeLabel,4,0);
    mainGridLayout->addWidget(deleteResultHttpCodeLineEdit,4,1);
    mainGridLayout->addWidget(rsDeleteResultLabel,5,0);
    mainGridLayout->addWidget(deleteResultTextEdit,5,1);

    deleteButton=new QPushButton(tr("Delete"));
    QHBoxLayout *actionLayout=new QHBoxLayout;
    actionLayout->addStretch();
    actionLayout->addWidget(deleteButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);

    this->setMinimumWidth(500);
    this->setMinimumHeight(400);

    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteSlot()));
}

void QNRSDeleteWidget::deleteSlot()
{
    QString bucket=this->bucketLineEdit->text().trimmed();
    QString key=this->keyLineEdit->text().trimmed();
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);
    QNetworkRequest request=QNRS::deleteRequest(bucket,key,&mac);
    QNetworkReply *reply=networkManager.get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(handleError(QNetworkReply::NetworkError)));
}

void QNRSDeleteWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        QByteArray respData=reply->readAll();
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        this->deleteResultTextEdit->setText(respData);
        this->deleteResultHttpCodeLineEdit->setText(QString::number(httpStatusCode));
        reply->deleteLater();
    }
}

void QNRSDeleteWidget::handleError(QNetworkReply::NetworkError)
{

}
