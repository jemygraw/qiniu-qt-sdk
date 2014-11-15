#include "QNMainWindow.h"
#include "QNSimpleUploadDataWidget.h"
#include "QNCreateSaveAsTokenWidget.h"
#include "QNCreatePrivateAccessTokenWidget.h"
#include "QNUrlSafeBase64Widget.h"
#include "QNCreateRSManageOperationWidget.h"
#include "QNImageView2Widget.h"
#include "QNRSStatWidget.h"
#include "QNRSDeleteWidget.h"
#include "QNRSCopyWidget.h"
#include "QNRSMoveWidget.h"
#include "QNRSChgmWidget.h"
#include "QNRSBatchWidget.h"
#include <QNetworkAccessManager>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include <QStackedWidget>
#include <QLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QSettings>
#include <QPushButton>

QNMainWindow::QNMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   setWindowTitle(tr("Qiniu Qt SDK & Tools"));
   setUnifiedTitleAndToolBarOnMac(true);
   networkManager=new QNetworkAccessManager(this);
   createGlobalWidgets();
   createMenus();
   createWidgets();
   this->setMinimumWidth(500);
   this->setMinimumHeight(200);

   globalSettings=new QSettings(this);
   QString accessKey=globalSettings->value("AccessKey").toString();
   QString secretKey=globalSettings->value("SecretKey").toString();
   this->accessKeyLineEdit->setText(accessKey);
   this->secretKeyLineEdit->setText(secretKey);
}

void QNMainWindow::createGlobalWidgets()
{
    QGroupBox *docGroupBox=new QGroupBox(this);
    docGroupBox->setTitle(tr("Most Visited Sites:"));
    QLabel *homeSiteLabel=new QLabel(tr("Home:"));
    QLabel *docSiteLabel=new QLabel(tr("Document:"));
    QLabel *qaSiteLabel=new QLabel(tr("Forum:"));
    qiniuHomeSiteLabel=new QLabel("<a href='http://www.qiniu.com/'>http://www.qiniu.com/</a>");
    qiniuDocSiteLabel=new QLabel("<a href='http://developer.qiniu.com/'>http://developer.qiniu.com/</a>");
    qiniuQASiteLabel=new QLabel("<a href='http://segmentfault.com/qiniu'>http://segmentfault.com/qiniu</a>");
    qiniuHomeSiteLabel->setOpenExternalLinks(true);
    qiniuDocSiteLabel->setOpenExternalLinks(true);
    qiniuQASiteLabel->setOpenExternalLinks(true);
    QGridLayout *docGridLayout=new QGridLayout;
    docGridLayout->addWidget(homeSiteLabel,0,0);
    docGridLayout->addWidget(qiniuHomeSiteLabel,0,1);
    docGridLayout->addWidget(docSiteLabel,1,0);
    docGridLayout->addWidget(qiniuDocSiteLabel,1,1);
    docGridLayout->addWidget(qaSiteLabel,2,0);
    docGridLayout->addWidget(qiniuQASiteLabel,2,1);
    docGroupBox->setLayout(docGridLayout);

    QGroupBox *akskGroupBox=new QGroupBox(this);
    QVBoxLayout *akskLayout=new QVBoxLayout;
    akskGroupBox->setTitle(tr("Global Access Key && Secret Key"));
    QLabel *accessKeyLabel=new QLabel(tr("Access Key:"));
    QLabel *secretKeyLabel=new QLabel(tr("Secret Key:"));
    accessKeyLineEdit=new QLineEdit;
    secretKeyLineEdit=new QLineEdit;
    QGridLayout *akskGridLayout=new QGridLayout;
    akskGridLayout->addWidget(accessKeyLabel,0,0);
    akskGridLayout->addWidget(accessKeyLineEdit,0,1);
    akskGridLayout->addWidget(secretKeyLabel,1,0);
    akskGridLayout->addWidget(secretKeyLineEdit,1,1);

    QHBoxLayout *saveBtnLayout=new QHBoxLayout;
    saveGlobalAKSKBtn=new QPushButton(tr("Save"));
    saveBtnLayout->addStretch();
    saveBtnLayout->addWidget(saveGlobalAKSKBtn);

    akskLayout->addLayout(akskGridLayout);
    akskLayout->addLayout(saveBtnLayout);
    akskGroupBox->setLayout(akskLayout);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(docGroupBox);
    mainLayout->addWidget(akskGroupBox);

    QWidget *mainWidget=new QWidget(this);
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);

    connect(saveGlobalAKSKBtn,SIGNAL(clicked()),this,SLOT(saveGlobalSettingsSlot()));
}

void QNMainWindow::createMenus()
{
    //system menu
    quitAction=new QAction(tr("Quit"),this);
    aboutAction=new QAction(tr("About Qiniu Qt SDK"),this);
    aboutQtAction=new QAction(tr("About Qt"),this);

    connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));

    QMenu *sysMenu=menuBar()->addMenu(tr("Qiniu Qt SDK"));
    sysMenu->addAction(aboutAction);
    sysMenu->addAction(aboutQtAction);
    sysMenu->addAction(quitAction);

    //upload menu
    simpleUploadDataAction=new QAction(tr("Simple Upload Data"),this);
    QMenu *uploadMenu=menuBar()->addMenu(tr("Upload"));
    uploadMenu->addAction(simpleUploadDataAction);

    connect(simpleUploadDataAction,SIGNAL(triggered()),this,SLOT(simpleUploadDataSlot()));

    //image menu
    imageView2Action=new QAction(tr("imageView2"),this);
    QMenu *imageMenu=new QMenu(tr("Image"),this);
    imageMenu->addAction(imageView2Action);

    //tool menu
    createSaveAsTokenAction=new QAction(tr("Create SaveAs Token"),this);
    urlsafeBase64Action=new QAction(tr("Urlsafe Base64 Encode/Decode"),this);
    createPrivateAccessTokenAction=new QAction(tr("Create Private Access Token"),this);
    createBatchOperationAction=new QAction(tr("Create RS Manage Operation"),this);
    QMenu *toolMenu=new QMenu(tr("Tools"));
    toolMenu->addAction(urlsafeBase64Action);
    toolMenu->addSeparator();
    toolMenu->addAction(createSaveAsTokenAction);
    toolMenu->addSeparator();
    toolMenu->addAction(createPrivateAccessTokenAction);
    toolMenu->addSeparator();
    toolMenu->addAction(createBatchOperationAction);

    //resource management
    rsStatAction=new QAction(tr("Stat"),this);
    rsCopyAction=new QAction(tr("Copy"),this);
    rsMoveAction=new QAction(tr("Move"),this);
    rsDeleteAction=new QAction(tr("Delete"),this);
    rsBatchAction=new QAction(tr("Batch"),this);
    rsChgmAction=new QAction(tr("Chgm"),this);
    QMenu *rsMenu=new QMenu(tr("Resource"));
    rsMenu->addAction(rsStatAction);
    rsMenu->addSeparator();
    rsMenu->addAction(rsCopyAction);
    rsMenu->addAction(rsMoveAction);
    rsMenu->addAction(rsDeleteAction);
    rsMenu->addSeparator();
    rsMenu->addAction(rsChgmAction);
    rsMenu->addSeparator();
    rsMenu->addAction(rsBatchAction);

    //bind signals with slots
    connect(urlsafeBase64Action,SIGNAL(triggered()),this,SLOT(base64Slot()));
    connect(createSaveAsTokenAction,SIGNAL(triggered()),this,SLOT(createSaveAsTokenSlot()));
    connect(imageView2Action,SIGNAL(triggered()),this,SLOT(imageView2Slot()));
    connect(createPrivateAccessTokenAction,SIGNAL(triggered()),this,SLOT(createPrivateAccessTokenSlot()));
    connect(createBatchOperationAction,SIGNAL(triggered()),this,SLOT(createRSManageOperationSlot()));

    connect(rsStatAction,SIGNAL(triggered()),this,SLOT(rsStatSlot()));
    connect(rsCopyAction,SIGNAL(triggered()),this,SLOT(rsCopySlot()));
    connect(rsMoveAction,SIGNAL(triggered()),this,SLOT(rsMoveSlot()));
    connect(rsDeleteAction,SIGNAL(triggered()),this,SLOT(rsDeleteSlot()));
    connect(rsBatchAction,SIGNAL(triggered()),this,SLOT(rsBatchSlot()));
    connect(rsChgmAction,SIGNAL(triggered()),this,SLOT(rsChgmSlot()));

    menuBar()->addMenu(sysMenu);
    menuBar()->addMenu(uploadMenu);
    menuBar()->addMenu(imageMenu);
    menuBar()->addMenu(toolMenu);
    menuBar()->addMenu(rsMenu);
}

void QNMainWindow::createWidgets()
{
    //init
    simpleUploadDataWidget=0;

    createSaveAsTokenWidget=0;
    urlsafeBase64Widget=0;
    imageView2Widget=0;
    createPrivateAccessTokenWidget=0;
    createRSManageOperationWidget=0;

    rsStatWidget=0;
    rsDeleteWidget=0;
    rsCopyWidget=0;
    rsMoveWidget=0;
    rsChgmWidget=0;
    rsBatchWidget=0;
}

QNMainWindow::~QNMainWindow()
{

}

void QNMainWindow::simpleUploadDataSlot()
{
    if (simpleUploadDataWidget==0)
    {
        simpleUploadDataWidget=new QNSimpleUploadDataWidget(networkManager);
    }
    this->simpleUploadDataWidget->show();
}

void QNMainWindow::createSaveAsTokenSlot()
{
    if(createSaveAsTokenWidget==0)
    {
        createSaveAsTokenWidget=new QNCreateSaveAsTokenWidget();
    }
    this->createSaveAsTokenWidget->show();
}

void QNMainWindow::base64Slot()
{
    if(urlsafeBase64Widget==0)
    {
        urlsafeBase64Widget=new QNUrlSafeBase64Widget();
    }
    this->urlsafeBase64Widget->show();
}

void QNMainWindow::imageView2Slot()
{
    if(imageView2Widget==0)
    {
        imageView2Widget=new QNImageView2Widget();
    }
    this->imageView2Widget->show();
}

void QNMainWindow::createPrivateAccessTokenSlot()
{
    if(createPrivateAccessTokenWidget==0)
    {
        createPrivateAccessTokenWidget=new QNCreatePrivateAccessTokenWidget();
    }
    this->createPrivateAccessTokenWidget->show();
}

void QNMainWindow::createRSManageOperationSlot()
{
    if(createRSManageOperationWidget==0)
    {
        createRSManageOperationWidget=new QNCreateRSManageOperationWidget();
    }
    this->createRSManageOperationWidget->show();
}

void QNMainWindow::rsStatSlot()
{
    if(rsStatWidget==0)
    {
        rsStatWidget=new QNRSStatWidget(*networkManager);
    }
    rsStatWidget->show();
}

void QNMainWindow::rsCopySlot()
{
    if(rsCopyWidget==0)
    {
        rsCopyWidget=new QNRSCopyWidget(*networkManager);
    }
    rsCopyWidget->show();
}

void QNMainWindow::rsMoveSlot()
{
    if(rsMoveWidget==0)
    {
        rsMoveWidget=new QNRSMoveWidget(*networkManager);
    }
    rsMoveWidget->show();
}

void QNMainWindow::rsDeleteSlot()
{
    if(rsDeleteWidget==0)
    {
        rsDeleteWidget=new QNRSDeleteWidget(*networkManager);
    }
    rsDeleteWidget->show();
}

void QNMainWindow::rsBatchSlot()
{
    if(rsBatchWidget==0)
    {
        rsBatchWidget=new QNRSBatchWidget(*networkManager);
    }
    rsBatchWidget->show();
}

void QNMainWindow::rsChgmSlot()
{
    if(rsChgmWidget==0)
    {
        rsChgmWidget=new QNRSChgmWidget(*networkManager);
    }
    rsChgmWidget->show();
}



void QNMainWindow::saveGlobalSettingsSlot()
{
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    globalSettings->setValue("AccessKey",accessKey);
    globalSettings->setValue("SecretKey",secretKey);
}

