#ifndef QNCREATESAVEASTOKENWIDGET_H
#define QNCREATESAVEASTOKENWIDGET_H
#include <QWidget>

class QGridLayout;
class QLineEdit;
class QPushButton;
class QLabel;

class QNCreateSaveAsTokenWidget : public QWidget
{
    Q_OBJECT

public:
    QNCreateSaveAsTokenWidget(QWidget *parent = 0);
    void createLayout();

public slots:
    void createSaveAsToken();

private:
    QLabel *docLabel;
    QLineEdit *srcUrlLineEdit;
    QLineEdit *accessKeyLineEdit;
    QLineEdit *secretKeyLineEdit;
    QLineEdit *signedTokenLineEdit;
    QLineEdit *newUrlLineEdit;
    QPushButton *createTokenButton;

};

#endif // QNCREATESAVEASTOKENWIDGET_H
