#include "QNMainWindow.h"
#include "QNSimpleUploadDataWidget.h"
#include "QNCreateSaveAsTokenWidget.h"
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
    QMenu *toolMenu=menuBar()->addMenu(tr("Tools"));
    toolMenu->addAction(createSaveAsTokenAction);

    connect(createSaveAsTokenAction,SIGNAL(triggered()),this,SLOT(createSaveAsTokenSlot()));


    menuBar()->addMenu(sysMenu);
    menuBar()->addMenu(uploadMenu);
    menuBar()->addMenu(toolMenu);
}

void QNMainWindow::createWidgets()
{
    mainStackedWidget=new QStackedWidget;
    setCentralWidget(mainStackedWidget);

    //init
    simpleUploadDataWidget=0;
    createSaveAsTokenWidget=0;
}

QNMainWindow::~QNMainWindow()
{

}

void QNMainWindow::simpleUploadDataSlot()
{
    if (simpleUploadDataWidget==0)
    {
        simpleUploadDataWidget=new QNSimpleUploadDataWidget(networkManager);
        mainStackedWidget->addWidget(simpleUploadDataWidget);
    }
    mainStackedWidget->setCurrentWidget(simpleUploadDataWidget);
    this->adjustSize();
}

void QNMainWindow::createSaveAsTokenSlot()
{
    if(createSaveAsTokenWidget==0)
    {
        createSaveAsTokenWidget=new QNCreateSaveAsTokenWidget();
        mainStackedWidget->addWidget(createSaveAsTokenWidget);
    }
    mainStackedWidget->setCurrentWidget(createSaveAsTokenWidget);
    this->adjustSize();
}
