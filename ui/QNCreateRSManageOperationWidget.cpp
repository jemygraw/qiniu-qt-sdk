#include "QNCreateRSManageOperationWidget.h"
#include "qiniu/utils/QNUtils.h"
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTextEdit>

QNCreateRSManageOperationWidget::QNCreateRSManageOperationWidget(QWidget *parent) :
    QWidget(parent),STAT_INDEX(0),COPY_INDEX(1),MOVE_INDEX(2),DELETE_INDEX(3),CHGM_INDEX(4)
{
    this->setWindowTitle(tr("Create RS Operation stat/copy/move/delete/chgm"));
    createLayout();
}

void QNCreateRSManageOperationWidget::createLayout()
{
    QVBoxLayout *mainLayout=new QVBoxLayout;

    //operation type
    QHBoxLayout *operationTypeLayout=new QHBoxLayout;

    QLabel *operationTypeLabel=new QLabel(tr("Operation Type:"));
    operationTypeComboBox=new QComboBox;
    QString statOperation("Stat");
    QString copyOperation("Copy");
    QString moveOperation("Move");
    QString deleteOperation("Delete");
    QString chgmOperation("Chgm");

    operationTypeComboBox->addItem(statOperation);
    operationTypeComboBox->addItem(copyOperation);
    operationTypeComboBox->addItem(moveOperation);
    operationTypeComboBox->addItem(deleteOperation);
    operationTypeComboBox->addItem(chgmOperation);

    operationTypeLayout->addWidget(operationTypeLabel);
    operationTypeLayout->addWidget(operationTypeComboBox);

    //bucket, key ,new mime type
    gridBKMWidget=new QWidget;
    QGridLayout *gridLayoutBKM=new QGridLayout;
    gridBKMWidget->setLayout(gridLayoutBKM);
    QLabel *bucketLabel=new QLabel(tr("Bucket:"));
    QLabel *keyLabel=new QLabel(tr("Key:"));
    newMimeTypeLabel=new QLabel(tr("New MimeType:"));

    bucketLineEdit=new QLineEdit;
    bucketLineEdit->setPlaceholderText(tr("Required"));
    keyLineEdit=new QLineEdit;
    keyLineEdit->setPlaceholderText(tr("Required"));
    newMimeTypeLineEdit=new QLineEdit;
    newMimeTypeLineEdit->setPlaceholderText(tr("Required"));

    gridLayoutBKM->addWidget(bucketLabel,0,0);
    gridLayoutBKM->addWidget(bucketLineEdit,0,1);
    gridLayoutBKM->addWidget(keyLabel,1,0);
    gridLayoutBKM->addWidget(keyLineEdit,1,1);
    gridLayoutBKM->addWidget(newMimeTypeLabel,2,0);
    gridLayoutBKM->addWidget(newMimeTypeLineEdit,2,1);

    //src bucket, src key, dest bucket, dest key
    gridCMWidget=new QWidget;
    QGridLayout *gridLayoutCM=new QGridLayout;
    gridCMWidget->setLayout(gridLayoutCM);

    QLabel *srcBucketLabel=new QLabel(tr("Src Bucket:"));
    QLabel *srcKeyLabel=new QLabel(tr("Src Key:"));
    QLabel *destBucketLabel=new QLabel(tr("Dest Bucket:"));
    QLabel *destKeyLabel=new QLabel(tr("Dest Key:"));

    srcBucketLineEdit=new QLineEdit;
    srcBucketLineEdit->setPlaceholderText(tr("Required"));
    srcKeyLineEdit=new QLineEdit;
    srcKeyLineEdit->setPlaceholderText(tr("Required"));
    destBucketLineEdit=new QLineEdit;
    destBucketLineEdit->setPlaceholderText(tr("Required"));
    destKeyLineEdit=new QLineEdit;
    destKeyLineEdit->setPlaceholderText(tr("Required"));

    gridLayoutCM->addWidget(srcBucketLabel,0,0);
    gridLayoutCM->addWidget(srcBucketLineEdit,0,1);
    gridLayoutCM->addWidget(srcKeyLabel,1,0);
    gridLayoutCM->addWidget(srcKeyLineEdit,1,1);
    gridLayoutCM->addWidget(destBucketLabel,2,0);
    gridLayoutCM->addWidget(destBucketLineEdit,2,1);
    gridLayoutCM->addWidget(destKeyLabel,3,0);
    gridLayoutCM->addWidget(destKeyLineEdit,3,1);

    //operation result layout
    QVBoxLayout *operationResultLayout=new QVBoxLayout;
    QLabel *operationResultLabel=new QLabel(tr("Operation:"));
    operationTextEdit=new QTextEdit;
    operationTextEdit->setAcceptRichText(false);
    operationTextEdit->setReadOnly(true);
    operationResultLayout->addWidget(operationResultLabel);
    operationResultLayout->addWidget(operationTextEdit);
    //action layout
    QHBoxLayout *actionLayout=new QHBoxLayout;
    createOperationButton=new QPushButton(tr("Create Operation"));
    actionLayout->addStretch();
    actionLayout->addWidget(createOperationButton);

    //main layout

    mainLayout->addLayout(operationTypeLayout);
    mainLayout->addWidget(gridBKMWidget);
    mainLayout->addWidget(gridCMWidget);
    mainLayout->addLayout(operationResultLayout);
    mainLayout->addLayout(actionLayout);

    newMimeTypeLabel->hide();
    newMimeTypeLineEdit->hide();
    gridCMWidget->hide();
    this->setLayout(mainLayout);

    this->setMinimumWidth(500);

    connect(operationTypeComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(updateLayoutAccordingToOperationTypeSlot(int)));
    connect(createOperationButton,SIGNAL(clicked()),this,SLOT(createOperationSlot()));
}

void QNCreateRSManageOperationWidget::createOperationSlot()
{
    int currentIndex=this->operationTypeComboBox->currentIndex();
    QString operationResult;
    if(currentIndex==STAT_INDEX || currentIndex==DELETE_INDEX || currentIndex==CHGM_INDEX)
    {
        QString bucket=this->bucketLineEdit->text().trimmed();
        QString key=this->keyLineEdit->text().trimmed();
        QByteArray entry=bucket.append(":").append(key).toLocal8Bit();
        QString encodedEntry=QNUtils::urlSafeBase64Encode(entry);
        if(currentIndex==STAT_INDEX)
        {
            operationResult.append("/stat/").append(encodedEntry);
        }
        else if(currentIndex==DELETE_INDEX)
        {
            operationResult.append("/delete/").append(encodedEntry);
        }
        else if(currentIndex==CHGM_INDEX)
        {
            QString newMimeType=this->newMimeTypeLineEdit->text().trimmed();
            QString encodedMimeType=QNUtils::urlSafeBase64Encode(newMimeType.toLocal8Bit());
            operationResult.append("/chgm/").append(encodedEntry)
                    .append("/mime/").append(encodedMimeType);
        }
    }
    else if(currentIndex==COPY_INDEX || currentIndex==MOVE_INDEX)
    {
        QString srcBucket=this->srcBucketLineEdit->text().trimmed();
        QString srcKey=this->srcKeyLineEdit->text().trimmed();
        QString destBucket=this->destBucketLineEdit->text().trimmed();
        QString destKey=this->destKeyLineEdit->text().trimmed();
        QByteArray srcEntry=srcBucket.append(":").append(srcKey).toLocal8Bit();
        QByteArray destEntry=destBucket.append(":").append(destKey).toLocal8Bit();
        QString encodedSrcEntry=QNUtils::urlSafeBase64Encode(srcEntry);
        QString encodedDestEntry=QNUtils::urlSafeBase64Encode(destEntry);
        if(currentIndex==COPY_INDEX)
        {
            operationResult.append("/copy/").append(encodedSrcEntry)
                    .append("/").append(encodedDestEntry);
        }
        else if(currentIndex==MOVE_INDEX)
        {
            operationResult.append("/move/").append(encodedSrcEntry)
                    .append("/").append(encodedDestEntry);
        }
    }
    this->operationTextEdit->setText(operationResult);
}

void QNCreateRSManageOperationWidget::updateLayoutAccordingToOperationTypeSlot(
        int currentIndex)
{
    if(currentIndex==STAT_INDEX || currentIndex==DELETE_INDEX || currentIndex==CHGM_INDEX)
    {
        gridCMWidget->hide();
        gridBKMWidget->show();
        if(currentIndex==4)
        {
            this->newMimeTypeLabel->show();
            this->newMimeTypeLineEdit->show();
        }
        else
        {
            this->newMimeTypeLabel->hide();
            this->newMimeTypeLineEdit->hide();
        }
    }
    else if(currentIndex==COPY_INDEX || currentIndex==MOVE_INDEX)
    {
        gridBKMWidget->hide();
        gridCMWidget->show();
    }
    this->operationTextEdit->clear();
    this->resize(sizeHint());
}
