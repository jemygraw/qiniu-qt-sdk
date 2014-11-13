#ifndef QNCREATEPRIVATEACCESSTOKENWIDGET_H
#define QNCREATEPRIVATEACCESSTOKENWIDGET_H

#include <QWidget>

class QDateTimeEdit;
class QLineEdit;
class QPushButton;
class QSettings;
class QDate;
class QTime;

class QNCreatePrivateAccessTokenWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *srcUrlLineEdit;
    QDateTimeEdit *expireDateTimeEdit;
    QLineEdit *expireTimestampLineEdit;
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;
    QLineEdit *newUrlLineEdit;

    QSettings *globalSettings;

    QPushButton *createTokenButton;
    void createLayout();
public:
    explicit QNCreatePrivateAccessTokenWidget(QWidget *parent = 0);

public slots:
    void createPrivateAccessToken();
    void updateExpireTimestamp(const QDateTime &dateTime);

};

#endif // CREATEPRIVATEACCESSTOKENWIDGET_H
