#include "QNMainWindow.h"
#include "QNSimpleUploadDataWidget.h"
#include "QNCreateSaveAsTokenWidget.h"
#include "QNCreatePrivateAccessTokenWidget.h"
#include "QNUrlBase64Widget.h"
#include "QNImageView2Widget.h"
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
    base64Action=new QAction(tr("Urlsafe Base64 Encode/Decode"),this);
    createPrivateAccessTokenAction=new QAction(tr("Create Private Access Token"),this);
    QMenu *toolMenu=menuBar()->addMenu(tr("Tools"));
    toolMenu->addAction(base64Action);
    toolMenu->addAction(createSaveAsTokenAction);
    toolMenu->addAction(createPrivateAccessTokenAction);


    connect(base64Action,SIGNAL(triggered()),this,SLOT(base64Slot()));
    connect(createSaveAsTokenAction,SIGNAL(triggered()),this,SLOT(createSaveAsTokenSlot()));
    connect(imageView2Action,SIGNAL(triggered()),this,SLOT(imageView2Slot()));
    connect(createPrivateAccessTokenAction,SIGNAL(triggered()),this,SLOT(createPrivateAccessTokenSlot()));

    menuBar()->addMenu(sysMenu);
    menuBar()->addMenu(uploadMenu);
    menuBar()->addMenu(imageMenu);
    menuBar()->addMenu(toolMenu);
}

void QNMainWindow::createWidgets()
{
    //init
    simpleUploadDataWidget=0;
    createSaveAsTokenWidget=0;
    urlBase64Widget=0;
    imageView2Widget=0;
    createPrivateAccessTokenWidget=0;
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
    if(urlBase64Widget==0)
    {
        urlBase64Widget=new QNUrlBase64Widget();
    }
    this->urlBase64Widget->show();
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

void QNMainWindow::saveGlobalSettingsSlot()
{
    QString accessKey=this->accessKeyLineEdit->text().trimmed();
    QString secretKey=this->secretKeyLineEdit->text().trimmed();
    globalSettings->setValue("AccessKey",accessKey);
    globalSettings->setValue("SecretKey",secretKey);
}

