#include "QNRSStatWidget.h"
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

QNRSStatWidget::QNRSStatWidget(QNetworkAccessManager &networkManager, QWidget *parent)
    :QWidget(parent),networkManager(networkManager)
{
    this->setWindowTitle(tr("Stat - Get Resource Meta Info"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);

}

void QNRSStatWidget::createLayout()
{
    QGridLayout *mainGridLayout=new QGridLayout;

    QLabel *bucketLabel=new QLabel(tr("Bucket:"));
    QLabel *keyLabel=new QLabel(tr("Key:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *rsStatResultHttpCodeLabel=new QLabel(tr("Http Code:"));
    QLabel *rsStatResultLabel=new QLabel(tr("Stat Result:"));

    bucketLineEdit=new QLineEdit;
    bucketLineEdit->setPlaceholderText(tr("Required"));
    keyLineEdit=new QLineEdit;
    keyLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    statResultHttpCodeLineEdit=new QLineEdit;
    statResultHttpCodeLineEdit->setReadOnly(true);
    statResultTextEdit=new QTextEdit;
    statResultTextEdit->setReadOnly(true);

    mainGridLayout->addWidget(bucketLabel,0,0);
    mainGridLayout->addWidget(bucketLineEdit,0,1);
    mainGridLayout->addWidget(keyLabel,1,0);
    mainGridLayout->addWidget(keyLineEdit,1,1);
    mainGridLayout->addWidget(accessKeyLabel,2,0);
    mainGridLayout->addWidget(accessKeyLineEdit,2,1);
    mainGridLayout->addWidget(secretKeyLabel,3,0);
    mainGridLayout->addWidget(secretKeyLineEdit,3,1);
    mainGridLayout->addWidget(rsStatResultHttpCodeLabel,4,0);
    mainGridLayout->addWidget(statResultHttpCodeLineEdit,4,1);
    mainGridLayout->addWidget(rsStatResultLabel,5,0);
    mainGridLayout->addWidget(statResultTextEdit,5,1);

    statButton=new QPushButton(tr("Stat"));
    QHBoxLayout *actionLayout=new QHBoxLayout;
    actionLayout->addStretch();
    actionLayout->addWidget(statButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);

    this->setMinimumWidth(500);
    this->setMinimumHeight(400);

    connect(statButton,SIGNAL(clicked()),this,SLOT(statSlot()));
}

void QNRSStatWidget::statSlot()
{
    QString bucket=this->bucketLineEdit->text().trimmed();
    QString key=this->keyLineEdit->text().trimmed();
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);
    QNetworkRequest request=QNRS::statRequest(bucket,key,&mac);
    QNetworkReply *reply=networkManager.get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(handleError(QNetworkReply::NetworkError)));
}

void QNRSStatWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        QByteArray respData=reply->readAll();
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        this->statResultTextEdit->setText(respData);
        this->statResultHttpCodeLineEdit->setText(QString::number(httpStatusCode));
        reply->deleteLater();
    }
}

void QNRSStatWidget::handleError(QNetworkReply::NetworkError)
{

}
