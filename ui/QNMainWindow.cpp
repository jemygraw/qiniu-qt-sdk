#include "QNMainWindow.h"
#include "QNSimpleUploadDataWidget.h"
#include "QNCreateSaveAsTokenWidget.h"
#include "QNUrlBase64Widget.h"
#include <QNetworkAccessManager>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include <QStackedWidget>
#include <QLayout>

QNMainWindow::QNMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   setWindowTitle(tr("Qiniu Qt SDK & Tools"));
   setUnifiedTitleAndToolBarOnMac(true);
   networkManager=new QNetworkAccessManager(this);
   createMenus();
   createWidgets();
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

    //tool menu
    createSaveAsTokenAction=new QAction(tr("Create SaveAs Token"),this);
    base64Action=new QAction(tr("Urlsafe Base64 Encode/Decode"),this);
    QMenu *toolMenu=menuBar()->addMenu(tr("Tools"));
    toolMenu->addAction(base64Action);
    toolMenu->addAction(createSaveAsTokenAction);

    connect(base64Action,SIGNAL(triggered()),this,SLOT(base64Slot()));
    connect(createSaveAsTokenAction,SIGNAL(triggered()),this,SLOT(createSaveAsTokenSlot()));


    menuBar()->addMenu(sysMenu);
    menuBar()->addMenu(uploadMenu);
    menuBar()->addMenu(toolMenu);
}

void QNMainWindow::createWidgets()
{
    //init
    simpleUploadDataWidget=0;
    createSaveAsTokenWidget=0;
    urlBase64Widget=0;
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
