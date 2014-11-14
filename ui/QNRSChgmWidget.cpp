#include "QNRSChgmWidget.h"

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

QNRSChgmWidget::QNRSChgmWidget(QNetworkAccessManager &networkManager, QWidget *parent)
    :QWidget(parent),networkManager(networkManager)
{
    this->setWindowTitle(tr("Chgm - Change Resource MimeType"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);

}

void QNRSChgmWidget::createLayout()
{
    QGridLayout *mainGridLayout=new QGridLayout;

    QLabel *bucketLabel=new QLabel(tr("Bucket:"));
    QLabel *keyLabel=new QLabel(tr("Key:"));
    QLabel *newMimeTypeLabel=new QLabel(tr("New MimeType:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *rschgmResultHttpCodeLabel=new QLabel(tr("Http Code:"));
    QLabel *rschgmResultLabel=new QLabel(tr("Chgm Result:"));

    bucketLineEdit=new QLineEdit;
    bucketLineEdit->setPlaceholderText(tr("Required"));
    keyLineEdit=new QLineEdit;
    keyLineEdit->setPlaceholderText(tr("Required"));
    newMimeTypeLineEdit=new QLineEdit;
    newMimeTypeLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    chgmResultHttpCodeLineEdit=new QLineEdit;
    chgmResultHttpCodeLineEdit->setReadOnly(true);
    chgmResultTextEdit=new QLineEdit;
    chgmResultTextEdit->setReadOnly(true);

    mainGridLayout->addWidget(bucketLabel,0,0);
    mainGridLayout->addWidget(bucketLineEdit,0,1);
    mainGridLayout->addWidget(keyLabel,1,0);
    mainGridLayout->addWidget(keyLineEdit,1,1);
    mainGridLayout->addWidget(newMimeTypeLabel,2,0);
    mainGridLayout->addWidget(newMimeTypeLineEdit,2,1);
    mainGridLayout->addWidget(accessKeyLabel,3,0);
    mainGridLayout->addWidget(accessKeyLineEdit,3,1);
    mainGridLayout->addWidget(secretKeyLabel,4,0);
    mainGridLayout->addWidget(secretKeyLineEdit,4,1);
    mainGridLayout->addWidget(rschgmResultHttpCodeLabel,5,0);
    mainGridLayout->addWidget(chgmResultHttpCodeLineEdit,5,1);
    mainGridLayout->addWidget(rschgmResultLabel,6,0);
    mainGridLayout->addWidget(chgmResultTextEdit,6,1);

    chgmButton=new QPushButton(tr("Change MimeType"));
    QHBoxLayout *actionLayout=new QHBoxLayout;
    actionLayout->addStretch();
    actionLayout->addWidget(chgmButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);

    this->setMinimumWidth(500);
    this->setMinimumHeight(300);

    connect(chgmButton,SIGNAL(clicked()),this,SLOT(chgmSlot()));
}

void QNRSChgmWidget::chgmSlot()
{
    QString bucket=this->bucketLineEdit->text().trimmed();
    QString key=this->keyLineEdit->text().trimmed();
    QString newMimeType=this->newMimeTypeLineEdit->text().trimmed();
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);
    QNetworkRequest request=QNRS::chgmRequest(bucket,key,newMimeType,&mac);
    QByteArray postData;
    QNetworkReply *reply=networkManager.post(request,postData);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(handleError(QNetworkReply::NetworkError)));
}

void QNRSChgmWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        QByteArray respData=reply->readAll();
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        this->chgmResultTextEdit->setText(respData);
        this->chgmResultHttpCodeLineEdit->setText(QString::number(httpStatusCode));
        reply->deleteLater();
    }
}

void QNRSChgmWidget::handleError(QNetworkReply::NetworkError)
{

}
