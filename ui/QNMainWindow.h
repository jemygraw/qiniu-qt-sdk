#ifndef QNMAINWINDOW_H
#define QNMAINWINDOW_H

#include <QMainWindow>
class QAction;
class QStackedWidget;
class QNetworkAccessManager;
class QNSimpleUploadDataWidget;
class QNCreateSaveAsTokenWidget;
class QNUrlBase64Widget;
class QNImageView2Widget;

class QNMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //system menu
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *quitAction;

    //tool menu
    QAction *createSaveAsTokenAction;
    QAction *base64Action;

    //upload menu
    QAction *simpleUploadDataAction;
    QAction *simpleUploadNoKeyAction;
    QAction *simpleUploadWithKeyAction;

    //image
    QAction *imageView2Action;

    //methods
    void createMenus();
    void createWidgets();

    //objects
    QNSimpleUploadDataWidget *simpleUploadDataWidget;
    QNCreateSaveAsTokenWidget *createSaveAsTokenWidget;
    QNUrlBase64Widget *urlBase64Widget;
    QNImageView2Widget *imageView2Widget;

public:
    QNetworkAccessManager *networkManager;

    QNMainWindow(QWidget *parent = 0);

    ~QNMainWindow();

public slots:
    void simpleUploadDataSlot();
    void createSaveAsTokenSlot();
    void base64Slot();
    void imageView2Slot();
};

#endif // QNMAINWINDOW_H
