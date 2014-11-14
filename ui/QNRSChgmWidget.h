#ifndef QNRSCHGMWIDGET_H
#define QNRSCHGMWIDGET_H

#include <QWidget>
#include <QNetworkReply>
class QLineEdit;
class QPushButton;
class QSettings;
class QNetworkAccessManager;

class QNRSChgmWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *bucketLineEdit;
    QLineEdit *keyLineEdit;
    QLineEdit *newMimeTypeLineEdit;
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;
    QLineEdit *chgmResultHttpCodeLineEdit;
    QLineEdit *chgmResultTextEdit;
    QPushButton *chgmButton;

    QSettings *globalSettings;

    void createLayout();
    QNetworkAccessManager &networkManager;
public:
    QNRSChgmWidget(QNetworkAccessManager &networkManager, QWidget *parent=0);

private slots:
    void chgmSlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);
};

#endif // QNRSCHGMWIDGET_H
