#include "QNRSBatchWidget.h"
#include "qiniu/auth/QNMac.h"
#include "qiniu/rs/QNRS.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSettings>
#include <QVBoxLayout>
#include <QLineEdit>

QNRSBatchWidget::QNRSBatchWidget(QNetworkAccessManager &networkManager, QWidget *parent) :
    QWidget(parent),networkManager(networkManager)
{
    this->setWindowTitle(tr("Batch - Batch Manage Resources"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);
}

void QNRSBatchWidget::createLayout()
{
    QGridLayout *mainGridLayout=new QGridLayout;
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *batchOperationsLabel=new QLabel(tr("Batch Operations:"));
    QLabel *batchResultHttpCodeLabel=new QLabel(tr("Http Code:"));
    QLabel *batchResultLabel=new QLabel(tr("Batch Result:"));

    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    batchOperationsTextEdit=new QTextEdit;
    batchOperationsTextEdit->setPlaceholderText(tr("Required"));
    batchOperationsTextEdit->setAcceptRichText(false);
    batchResultHttpCodeLineEdit=new QLineEdit;
    batchResultHttpCodeLineEdit->setReadOnly(true);
    batchResultTextEdit=new QTextEdit;
    batchResultTextEdit->setReadOnly(true);
    batchResultTextEdit->setAcceptRichText(false);

    mainGridLayout->addWidget(accessKeyLabel,0,0);
    mainGridLayout->addWidget(accessKeyLineEdit,0,1);
    mainGridLayout->addWidget(secretKeyLabel,1,0);
    mainGridLayout->addWidget(secretKeyLineEdit,1,1);
    mainGridLayout->addWidget(batchOperationsLabel,2,0);
    mainGridLayout->addWidget(batchOperationsTextEdit,2,1);
    mainGridLayout->addWidget(batchResultHttpCodeLabel,3,0);
    mainGridLayout->addWidget(batchResultHttpCodeLineEdit);
    mainGridLayout->addWidget(batchResultLabel,4,0);
    mainGridLayout->addWidget(batchResultTextEdit,4,1);

    QHBoxLayout *actionLayout=new QHBoxLayout;
    batchButton=new QPushButton(tr("Batch"));
    actionLayout->addStretch();
    actionLayout->addWidget(batchButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);
    this->setMinimumWidth(600);
    this->setMinimumHeight(400);

    connect(batchButton,SIGNAL(clicked()),this,SLOT(batchSlot()));

}

void QNRSBatchWidget::batchSlot()
{
    QString batchOperations=batchOperationsTextEdit->document()->toPlainText().trimmed();
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);
    QNetworkRequest request=QNRS::batchRequest(batchOperations,&mac);
    QByteArray postData=batchOperations.toLocal8Bit();
    QNetworkReply *reply=networkManager.post(request,postData);
    connect(reply,SIGNAL(finished()),this,SLOT(recvData()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
            this,SLOT(handleError(QNetworkReply::NetworkError)));
}

void QNRSBatchWidget::recvData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply) {
        QByteArray respData=reply->readAll();
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        this->batchResultTextEdit->setText(respData);
        this->batchResultHttpCodeLineEdit->setText(QString::number(httpStatusCode));
        reply->deleteLater();
    }
}

void QNRSBatchWidget::handleError(QNetworkReply::NetworkError)
{

}
