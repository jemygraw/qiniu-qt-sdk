#include "QNCreatePrivateAccessTokenWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QSettings>
#include <QString>
#include <QGridLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QUrl>
#include "qiniu/auth/QNMac.h"

QNCreatePrivateAccessTokenWidget::QNCreatePrivateAccessTokenWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle(tr("Create Private Access Token"));
    createLayout();
    globalSettings=new QSettings(this);
    QString accessKey=globalSettings->value("AccessKey").toString();
    QString secretKey=globalSettings->value("SecretKey").toString();
    this->accessKeyLineEdit->setText(accessKey);
    this->secretKeyLineEdit->setText(secretKey);

    this->setMinimumWidth(500);
    this->setMinimumHeight(200);
}

void QNCreatePrivateAccessTokenWidget::createLayout()
{
    QVBoxLayout *mainLayout=new QVBoxLayout;

    //grid layout
    QGridLayout *mainGridLayout=new QGridLayout;

    QLabel *srcUrlLabel=new QLabel(tr("Src Url:"));
    QLabel *expireLabel=new QLabel(tr("Expire:"));
    QLabel *expireTimestampLabel=new QLabel(tr("Timestamp:"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    QLabel *newUrlLabel=new QLabel(tr("New Url:"));

    srcUrlLineEdit=new QLineEdit;
    srcUrlLineEdit->setPlaceholderText(tr("Required"));
    expireDateTimeEdit=new QDateTimeEdit;
    QDateTime now=QDateTime::currentDateTime();
    now.setOffsetFromUtc(3600*8);
    now=now.addSecs(3600);
    expireDateTimeEdit->setDateTime(now);
    expireTimestampLineEdit=new QLineEdit;
    expireTimestampLineEdit->setReadOnly(true);
    expireTimestampLineEdit->setText(QString::number(now.toTime_t()));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    newUrlLineEdit=new QLineEdit;
    newUrlLineEdit->setReadOnly(true);


    //layout
    mainGridLayout->addWidget(srcUrlLabel,0,0);
    mainGridLayout->addWidget(srcUrlLineEdit,0,1);
    mainGridLayout->addWidget(accessKeyLabel,1,0);
    mainGridLayout->addWidget(accessKeyLineEdit,1,1);
    mainGridLayout->addWidget(secretKeyLabel,2,0);
    mainGridLayout->addWidget(secretKeyLineEdit,2,1);
    mainGridLayout->addWidget(expireLabel,3,0);
    mainGridLayout->addWidget(expireDateTimeEdit,3,1);
    mainGridLayout->addWidget(expireTimestampLabel,4,0);
    mainGridLayout->addWidget(expireTimestampLineEdit,4,1);
    mainGridLayout->addWidget(newUrlLabel,5,0);
    mainGridLayout->addWidget(newUrlLineEdit,5,1);

    //action layout
    QHBoxLayout *actionLayout=new QHBoxLayout;
    createTokenButton=new QPushButton(tr("Create"));
    actionLayout->addStretch();
    actionLayout->addWidget(createTokenButton);

    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);

    connect(expireDateTimeEdit,SIGNAL(dateTimeChanged(const QDateTime&)),
            this,SLOT(updateExpireTimestamp(const QDateTime&)));
    connect(createTokenButton,SIGNAL(clicked()),this,SLOT(createPrivateAccessToken()));
}


void QNCreatePrivateAccessTokenWidget::createPrivateAccessToken()
{
    QString srcUrl=this->srcUrlLineEdit->text().trimmed();
    QUrl srcUri(srcUrl);
    QString expireTimestamp=this->expireTimestampLineEdit->text().trimmed();
    if(srcUri.hasQuery())
    {
        srcUrl.append("&e=").append(expireTimestamp);
    }
    else
    {
        srcUrl.append("?e=").append(expireTimestamp);
    }
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    QByteArray secretKeyBytes=secretKey.toLocal8Bit();
    QNMac mac(accessKey,secretKeyBytes);
    QByteArray srcUrlData=srcUrl.toLocal8Bit();
    QString accessToken=mac.sign(srcUrlData);
    QString newUrl=QString(srcUrl);
    newUrl.append("&token=").append(accessToken);

    this->newUrlLineEdit->setText(newUrl);
}

void QNCreatePrivateAccessTokenWidget::updateExpireTimestamp(const QDateTime &dateTime)
{
    expireTimestampLineEdit->setText(QString::number(dateTime.toTime_t()));
}

