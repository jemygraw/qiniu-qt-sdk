#ifndef QNSIMPLEUPLOADDATAWIDGET_H
#define QNSIMPLEUPLOADDATAWIDGET_H

#include <QWidget>

class QTextEdit;
class QPushButton;
class QLineEdit;
class QNetworkAccessManager;

class QNSimpleUploadDataWidget : public QWidget
{
    Q_OBJECT

private:
    QNetworkAccessManager *networkManager;
    QTextEdit *putDataTextEdit;
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;
    QLineEdit *bucketLineEdit;
    QLineEdit *keyLineEdit;
    QLineEdit *fileNameLineEdit;
    QPushButton *uploadButton;
    void createLayout();
public:
    explicit QNSimpleUploadDataWidget(QNetworkAccessManager *networkManager,
                                      QWidget *parent = 0);

signals:

public slots:
    void uploadData();
    void recvData();
    void handleError();
};

#endif // QNSIMPLEUPLOADDATAWIDGET_H
