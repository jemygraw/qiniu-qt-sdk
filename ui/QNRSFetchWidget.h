#ifndef QNRSFETCHWIDGET_H
#define QNRSFETCHWIDGET_H

#include <QWidget>
#include <QNetworkReply>

class QNetworkAccessManager;
class QSettings;
class QLineEdit;
class QTextEdit;
class QPushButton;

class QNRSFetchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QNRSFetchWidget(QWidget *parent = 0);

    QTextEdit *fetchUrlTextEdit;
    QLineEdit *saveBucketLineEdit;
    QLineEdit *saveKeyLineEdit;

    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;

    QLineEdit *fetchResultHttpCodeLineEdit;
    QLineEdit *fetchResultLineEdit;

    QPushButton *fetchButton;
    QSettings *globalSettings;
    QNetworkAccessManager &networkManager;

    void createLayout();
public:
    explicit QNRSFetchWidget(QNetworkAccessManager &networkManager, QWidget *parent = 0);

signals:

private slots:
    void fetchSlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);
};
#endif // QNRSFETCHWIDGET_H
