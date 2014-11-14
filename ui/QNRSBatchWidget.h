#ifndef QNRSBATCHWIDGET_H
#define QNRSBATCHWIDGET_H

#include <QWidget>
#include <QNetworkReply>

class QLineEdit;
class QPushButton;
class QTextEdit;
class QSettings;
class QNetworkAccessManager;

class QNRSBatchWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;
    QTextEdit *batchOperationsTextEdit;
    QLineEdit *batchResultHttpCodeLineEdit;
    QTextEdit *batchResultTextEdit;
    QPushButton *batchButton;

    QSettings *globalSettings;
    QNetworkAccessManager &networkManager;

    void createLayout();
public:
    explicit QNRSBatchWidget(QNetworkAccessManager &networkManager, QWidget *parent = 0);

signals:

private slots:
    void batchSlot();
    void recvData();
    void handleError(QNetworkReply::NetworkError);
};

#endif // QNRSBATCHWIDGET_H
