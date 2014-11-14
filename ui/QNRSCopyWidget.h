#ifndef QNRSCOPYWIDGET_H
#define QNRSCOPYWIDGET_H
#include <QWidget>
#include <QNetworkReply>

class QLineEdit;
class QPushButton;
class QSettings;
class QNetworkAcessManager;

class QNRSCopyWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *srcBucketLineEdit;
    QLineEdit *srcKeyLineEdit;
    QLineEdit *destBucketLineEdit;
    QLineEdit *destKeyLineEdit;

    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;

    QLineEdit *copyResultHttpCodeLineEdit;
    QLineEdit *copyResultLineEdit;

    QPushButton *copyButton;

    QSettings *globalSettings;

    void createLayout();
    QNetworkAccessManager &networkManager;
public:
    QNRSCopyWidget(QNetworkAccessManager &networkManager, QWidget *parent=0);
private slots:
    void copySlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);
};

#endif // QNRSCOPYWIDGET_H
