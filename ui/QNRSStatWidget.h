#ifndef QNRSSTATWIDGET_H
#define QNRSSTATWIDGET_H

#include <QWidget>
#include <QNetworkReply>

class QLineEdit;
class QPushButton;
class QSettings;
class QTextEdit;
class QNetworkAccessManager;

class QNRSStatWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *bucketLineEdit;
    QLineEdit *keyLineEdit;
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;
    QLineEdit *statResultHttpCodeLineEdit;
    QTextEdit *statResultTextEdit;
    QPushButton *statButton;

    QSettings *globalSettings;

    void createLayout();
    QNetworkAccessManager &networkManager;
public:
    QNRSStatWidget(QNetworkAccessManager &networkManager, QWidget *parent=0);

private slots:
    void statSlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);

};

#endif // QNRSSTATWIDGET_H
