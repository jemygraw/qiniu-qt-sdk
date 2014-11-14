#ifndef QNRSMOVEWIDGET_H
#define QNRSMOVEWIDGET_H
#include <QWidget>
#include <QNetworkReply>

class QLineEdit;
class QPushButton;
class QSettings;
class QNetworkAcessManager;

class QNRSMoveWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *srcBucketLineEdit;
    QLineEdit *srcKeyLineEdit;
    QLineEdit *destBucketLineEdit;
    QLineEdit *destKeyLineEdit;

    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;

    QLineEdit *moveResultHttpCodeLineEdit;
    QLineEdit *moveResultLineEdit;

    QPushButton *moveButton;

    QSettings *globalSettings;

    void createLayout();
    QNetworkAccessManager &networkManager;
public:
    QNRSMoveWidget(QNetworkAccessManager &networkManager, QWidget *parent=0);
private slots:
    void moveSlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);
};

#endif // QNRSMOVEWIDGET_H
