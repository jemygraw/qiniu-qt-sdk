#ifndef QNMAINWINDOW_H
#define QNMAINWINDOW_H

#include <QMainWindow>
class QAction;
class QStackedWidget;
class QNetworkAccessManager;
class QNSimpleUploadDataWidget;
class QNCreateSaveAsTokenWidget;

class QNMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //system menu
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *quitAction;
    QAction *createSaveAsTokenAction;

    //upload menu
    QAction *simpleUploadDataAction;

    QAction *simpleUploadNoKeyAction;
    QAction *simpleUploadWithKeyAction;

    //methods
    void createMenus();
    void createWidgets();

    //objects
    QNSimpleUploadDataWidget *simpleUploadDataWidget;
    QNCreateSaveAsTokenWidget *createSaveAsTokenWidget;

    //
    QStackedWidget *mainStackedWidget;
public:
    QNetworkAccessManager *networkManager;

    QNMainWindow(QWidget *parent = 0);

    ~QNMainWindow();

public slots:
    void simpleUploadDataSlot();
    void createSaveAsTokenSlot();
};

#endif // QNMAINWINDOW_H
