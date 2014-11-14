#ifndef QNRSDELETEWIDGET_H
#define QNRSDELETEWIDGET_H

#include <QWidget>
#include <QNetworkReply>

class QLineEdit;
class QPushButton;
class QSettings;
class QTextEdit;
class QNetworkAccessManager;

class QNRSDeleteWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *bucketLineEdit;
    QLineEdit *keyLineEdit;
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;
    QLineEdit *deleteResultHttpCodeLineEdit;
    QTextEdit *deleteResultTextEdit;
    QPushButton *deleteButton;

    QSettings *globalSettings;

    void createLayout();
    QNetworkAccessManager &networkManager;
public:
    QNRSDeleteWidget(QNetworkAccessManager &networkManager, QWidget *parent=0);

private slots:
    void deleteSlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);

};

#endif // QNRSDELETEWIDGET_H
