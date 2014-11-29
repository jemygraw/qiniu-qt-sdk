#include "QNRSFetchWidget.h"
#include "qiniu/rs/QNRS.h"
#include "qiniu/auth/QNMac.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QSettings>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

QNRSFetchWidget::QNRSFetchWidget(QNetworkAccessManager &networkManager, QWidget *parent) :
    QWidget(parent),networkManager(networkManager)
{
    this->setWindowTitle(tr("Fetch - Fetch Remote Resource"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);
}

void QNRSFetchWidget::createLayout()
{
    QGridLayout *mainGridLayout=new QGridLayout;
    QLabel *fetchUrlLabel=new QLabel(tr("Remote Url:"));
    QLabel *saveBucketLabel=new QLabel(tr("Save Bucket:"));
    QLabel *saveKeyLabel=new QLabel(tr("Save Key:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *fetchResultHttpCodeLabel=new QLabel(tr("Http Code:"));
    QLabel *fetchResultLabel=new QLabel(tr("Fetch Result:"));

    fetchUrlTextEdit=new QTextEdit;
    fetchUrlTextEdit->setAcceptRichText(false);
    fetchUrlTextEdit->setPlaceholderText(tr("Required"));
    saveBucketLineEdit=new QLineEdit;
    saveBucketLineEdit->setPlaceholderText(tr("Required"));
    saveKeyLineEdit=new QLineEdit;
    saveKeyLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    fetchResultHttpCodeLineEdit=new QLineEdit;
    fetchResultHttpCodeLineEdit->setReadOnly(true);
    fetchResultLineEdit=new QLineEdit;
    fetchResultLineEdit->setReadOnly(true);

    mainGridLayout->addWidget(fetchUrlLabel,0,0,1,2);
    mainGridLayout->addWidget(fetchUrlTextEdit,1,0,1,2);
    mainGridLayout->addWidget(saveBucketLabel,2,0);
    mainGridLayout->addWidget(saveBucketLineEdit,2,1);
    mainGridLayout->addWidget(saveKeyLabel,3,0);
    mainGridLayout->addWidget(saveKeyLineEdit,3,1);
    mainGridLayout->addWidget(accessKeyLabel,4,0);
    mainGridLayout->addWidget(accessKeyLineEdit,4,1);
    mainGridLayout->addWidget(secretKeyLabel,5,0);
    mainGridLayout->addWidget(secretKeyLineEdit,5,1);
    mainGridLayout->addWidget(fetchResultHttpCodeLabel,6,0);
    mainGridLayout->addWidget(fetchResultHttpCodeLineEdit,6,1);
    mainGridLayout->addWidget(fetchResultLabel,7,0);
    mainGridLayout->addWidget(fetchResultLineEdit,7,1);

    QHBoxLayout *actionLayout=new QHBoxLayout;
    fetchButton=new QPushButton(tr("Fetch"));
    actionLayout->addStretch();
    actionLayout->addWidget(fetchButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);
    this->setMinimumWidth(600);
    this->setMinimumHeight(400);

    connect(fetchButton,SIGNAL(clicked()),this,SLOT(fetchSlot()));
}

void QNRSFetchWidget::fetchSlot()
{
    QString accessKey=accessKeyLineEdit->text().trimmed();
    QString secretKey=secretKeyLineEdit->text().trimmed();
    QString fetchUrl=fetchUrlTextEdit->document()->toPlainText().trimmed();
    QString saveBucket=saveBucketLineEdit->text().trimmed();
    QString saveKey=saveKeyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);

    QNetworkRequest request=QNRS::fetchRequest(fetchUrl,saveBucket,saveKey,&mac);
    QByteArray postData;
    QNetworkReply *reply=networkManager.post(request,postData);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(handleError(QNetworkReply::NetworkError)));
}

void QNRSFetchWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        QByteArray respData=reply->readAll();
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        this->fetchResultLineEdit->setText(respData);
        this->fetchResultHttpCodeLineEdit->setText(QString::number(httpStatusCode));
        reply->deleteLater();
    }
}

void QNRSFetchWidget::handleError(QNetworkReply::NetworkError)
{

}
