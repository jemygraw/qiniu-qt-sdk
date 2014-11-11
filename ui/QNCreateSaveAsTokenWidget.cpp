#include "QNCreateSaveAsTokenWidget.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "qiniu/utils/QNUtils.h"
#include <iostream>
#include <QUrl>

QNCreateSaveAsTokenWidget::QNCreateSaveAsTokenWidget(QWidget *parent): QWidget(parent)
{
    createLayout();
}

void QNCreateSaveAsTokenWidget::createLayout()
{
    QGridLayout  *mainGridLayout=new QGridLayout;

    QLabel *srcUrlLabel=new QLabel(tr("Src Url:"),this);
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"),this);
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"),this);
    QLabel *tokenLabel=new QLabel(tr("Token:"),this);
    QLabel *newUrlLabel=new QLabel(tr("New Url:"),this);

    int editMinWidth=500;
    docLabel=new QLabel("<a href='http://developer.qiniu.com/docs/v6/api/reference/fop/saveas.html'>"+tr("Document")+"</a>");
    docLabel->setOpenExternalLinks(true);
    srcUrlLineEdit=new QLineEdit;
    srcUrlLineEdit->setPlaceholderText(tr("Required"));
    srcUrlLineEdit->setMinimumWidth(editMinWidth);
    accessKeyLineEdit=new QLineEdit;
    accessKeyLineEdit->setPlaceholderText(tr("Required"));
    accessKeyLineEdit->setMinimumWidth(editMinWidth);
    secretKeyLineEdit=new QLineEdit;
    secretKeyLineEdit->setPlaceholderText(tr("Required"));
    secretKeyLineEdit->setMinimumWidth(editMinWidth);
    signedTokenLineEdit=new QLineEdit;
    newUrlLineEdit=new QLineEdit;
    newUrlLineEdit->setMinimumWidth(editMinWidth);
    signedTokenLineEdit->setReadOnly(true);
    newUrlLineEdit->setReadOnly(true);

    createTokenButton=new QPushButton(tr("Create Token"));

    mainGridLayout->addWidget(docLabel,0,0,1,2);
    mainGridLayout->addWidget(srcUrlLabel,1,0);
    mainGridLayout->addWidget(srcUrlLineEdit,1,1);
    mainGridLayout->addWidget(accessKeyLabel,2,0);
    mainGridLayout->addWidget(accessKeyLineEdit,2,1);
    mainGridLayout->addWidget(secretKeyLabel,3,0);
    mainGridLayout->addWidget(secretKeyLineEdit,3,1);
    mainGridLayout->addWidget(tokenLabel,4,0);
    mainGridLayout->addWidget(signedTokenLineEdit,4,1);
    mainGridLayout->addWidget(newUrlLabel,5,0);
    mainGridLayout->addWidget(newUrlLineEdit,5,1);

    QHBoxLayout *actionLayout=new QHBoxLayout;
    actionLayout->addStretch();
    actionLayout->addWidget(createTokenButton);

    connect(createTokenButton,SIGNAL(clicked()),this,SLOT(createSaveAsToken()));

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(mainGridLayout);
    mainLayout->addLayout(actionLayout);

    this->setLayout(mainLayout);
    this->setMinimumWidth(500);
    this->setMinimumHeight(200);
}


void QNCreateSaveAsTokenWidget::createSaveAsToken()
{
    QString srcUrl=srcUrlLineEdit->text().trimmed();
    QString trimmedUrl=srcUrl;
    if(srcUrl.startsWith("http://") || srcUrl.startsWith("https://"))
    {
        int index=srcUrl.indexOf("://");
        trimmedUrl=srcUrl.mid(index+3);
    }
    QString secretKey=secretKeyLineEdit->text().trimmed();
    QString accessKey=accessKeyLineEdit->text().trimmed();

    QByteArray signedUrl=QNUtils::hmacSha1(trimmedUrl.toLocal8Bit(),secretKey.toLocal8Bit());
    QString encodedToken=QNUtils::urlSafeBase64Encode(signedUrl);
    this->signedTokenLineEdit->setText(encodedToken);
    QString newUrl=QString(srcUrl);
    newUrl.append("/sign/");
    newUrl.append(accessKey);
    newUrl.append(":");
    newUrl.append(encodedToken);
    this->newUrlLineEdit->setText(newUrl);
}
