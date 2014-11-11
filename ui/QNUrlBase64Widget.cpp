#include "QNUrlBase64Widget.h"
#include "qiniu/utils/QNUtils.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>

QNUrlBase64Widget::QNUrlBase64Widget(QWidget *parent): QWidget(parent)
{
    this->setWindowTitle(tr("Urlsafe Base64 Encode/Decode"));
    createWidgets();
}

void QNUrlBase64Widget::createWidgets()
{
    QGroupBox *toEncodeGBox=new QGroupBox(this);
    toEncodeGBox->setTitle(tr("Urlsafe Base64 Encode"));
    QVBoxLayout *toEncodeLayout=new QVBoxLayout;
    QLabel *toEncodeSrcLabel=new QLabel(tr("Src Data:"));
    QLabel *toEncodeDestLabel=new QLabel(tr("Encoded Data:"));
    toEncodeSrcTextEdit=new QTextEdit(this);
    toEncodeDestTextEdit=new QTextEdit(this);
    toEncodeSrcTextEdit->setAcceptRichText(false);
    toEncodeDestTextEdit->setReadOnly(true);
    encodeButton=new QPushButton(tr("Encode"));
    toEncodeLayout->addWidget(toEncodeSrcLabel);
    toEncodeLayout->addWidget(toEncodeSrcTextEdit);
    toEncodeLayout->addWidget(toEncodeDestLabel);
    toEncodeLayout->addWidget(toEncodeDestTextEdit);
    toEncodeLayout->addWidget(encodeButton);
    toEncodeGBox->setLayout(toEncodeLayout);

    QGroupBox *toDecodeGBox=new QGroupBox(this);
    toDecodeGBox->setTitle(tr("Urlsafe Base64 Decode"));
    QVBoxLayout *toDecodeLayout=new QVBoxLayout;
    QLabel *toDecodeSrcLabel=new QLabel(tr("Src Data:"));
    QLabel *toDecodeDestLabel=new QLabel(tr("Decoded Data:"));
    toDecodeSrcTextEdit=new QTextEdit(this);
    toDecodeDestTextEdit=new QTextEdit(this);
    toDecodeSrcTextEdit->setAcceptRichText(false);
    toDecodeDestTextEdit->setReadOnly(true);
    decodeButton=new QPushButton(tr("Decode"));
    toDecodeLayout->addWidget(toDecodeSrcLabel);
    toDecodeLayout->addWidget(toDecodeSrcTextEdit);
    toDecodeLayout->addWidget(toDecodeDestLabel);
    toDecodeLayout->addWidget(toDecodeDestTextEdit);
    toDecodeLayout->addWidget(decodeButton);
    toDecodeGBox->setLayout(toDecodeLayout);

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->addWidget(toEncodeGBox);
    mainLayout->addWidget(toDecodeGBox);

    connect(encodeButton,SIGNAL(clicked()),this,SLOT(encodeData()));
    connect(decodeButton,SIGNAL(clicked()),this,SLOT(decodeData()));

    this->setLayout(mainLayout);
    this->setMinimumWidth(500);
    this->setMinimumHeight(400);

}

void QNUrlBase64Widget::encodeData()
{
    QString toEncodeData=this->toEncodeSrcTextEdit->document()->toPlainText().trimmed();
    QString encodeData=QNUtils::urlSafeBase64Encode(toEncodeData.toLocal8Bit());
    this->toEncodeDestTextEdit->setText(encodeData);
}

void QNUrlBase64Widget::decodeData()
{
    QString toDecodeData=this->toDecodeSrcTextEdit->document()->toPlainText().trimmed();
    QString decodeData=QNUtils::urlSafeBase64Decode(toDecodeData.toLocal8Bit());
    this->toDecodeDestTextEdit->setText(decodeData);
}
