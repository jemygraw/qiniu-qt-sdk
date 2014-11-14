#ifndef QNMAINWINDOW_H
#define QNMAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLineEdit;
class QPushButton;
class QLabel;
class QSettings;
class QNetworkAccessManager;
class QNSimpleUploadDataWidget;
class QNCreateSaveAsTokenWidget;
class QNCreatePrivateAccessTokenWidget;
class QNRSStatWidget;
class QNRSDeleteWidget;
class QNRSCopyWidget;
class QNRSMoveWidget;
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
    QAction *createPrivateAccessTokenAction;

    //upload menu
    QAction *simpleUploadDataAction;
    QAction *simpleUploadNoKeyAction;
    QAction *simpleUploadWithKeyAction;

    //resource management
    QAction *rsStatAction;
    QAction *rsCopyAction;
    QAction *rsMoveAction;
    QAction *rsDeleteAction;
    QAction *rsBatchAction;
    QAction *rsChgmAction;

    //image
    QAction *imageView2Action;

    //methods
    void createGlobalWidgets();
    void createMenus();
    void createWidgets();

    //objects
    QNSimpleUploadDataWidget *simpleUploadDataWidget;
    QNCreateSaveAsTokenWidget *createSaveAsTokenWidget;
    QNUrlBase64Widget *urlBase64Widget;
    QNImageView2Widget *imageView2Widget;
    QNCreatePrivateAccessTokenWidget *createPrivateAccessTokenWidget;

    QNRSStatWidget *rsStatWidget;
    QNRSDeleteWidget *rsDeleteWidget;
    QNRSCopyWidget *rsCopyWidget;
    QNRSMoveWidget *rsMoveWidget;

    //widgets
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;

    //public info
    QLabel *qiniuHomeSiteLabel;
    QLabel *qiniuDocSiteLabel;
    QLabel *qiniuQASiteLabel;

    QLineEdit *globalAccessKeyLineEdit;
    QLineEdit *globalSecretLineEdit;
    QPushButton *saveGlobalAKSKBtn;

    //settings
    QSettings *globalSettings;
public:
    QNetworkAccessManager *networkManager;

    QNMainWindow(QWidget *parent = 0);

    ~QNMainWindow();

public slots:
    void simpleUploadDataSlot();
    void createSaveAsTokenSlot();
    void base64Slot();
    void imageView2Slot();
    void saveGlobalSettingsSlot();
    void createPrivateAccessTokenSlot();

    void rsStatSlot();
    void rsCopySlot();
    void rsMoveSlot();
    void rsDeleteSlot();
    void rsBatchSlot();
    void rsChgmSlot();
};

#endif // QNMAINWINDOW_H
