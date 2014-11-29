#ifndef QNRSPREFETCHWIDGET_H
#define QNRSPREFETCHWIDGET_H

#include <QWidget>
#include <QNetworkReply>

class QLineEdit;
class QPushButton;
class QSettings;
class QNetworkAccessManager;

class QNRSPrefetchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QNRSPrefetchWidget(QWidget *parent = 0);

    QLineEdit *bucketLineEdit;
    QLineEdit *keyLineEdit;

    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;

    QLineEdit *prefetchResultHttpCodeLineEdit;
    QLineEdit *prefetchResultLineEdit;

    QPushButton *prefetchButton;
    QSettings *globalSettings;
    QNetworkAccessManager &networkManager;

    void createLayout();
public:
    explicit QNRSPrefetchWidget(QNetworkAccessManager &networkManager, QWidget *parent = 0);

signals:

private slots:
    void prefetchSlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);

};

#endif // QNRSPREFETCHWIDGET_H
