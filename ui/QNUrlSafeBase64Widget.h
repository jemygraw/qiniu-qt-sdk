#ifndef QNURLSAFEBASE64WIDGET_H
#define QNURLSAFEBASE64WIDGET_H
#include <QWidget>

class QPushButton;
class QTextEdit;
class QNUrlSafeBase64Widget : public QWidget
{
    Q_OBJECT

private:
    QPushButton *encodeButton;
    QPushButton *decodeButton;

    QTextEdit *toEncodeSrcTextEdit;
    QTextEdit *toEncodeDestTextEdit;

    QTextEdit *toDecodeSrcTextEdit;
    QTextEdit *toDecodeDestTextEdit;

    void createLayout();

public slots:
    void encodeData();
    void decodeData();

public:
    QNUrlSafeBase64Widget(QWidget *parent=0);

};

#endif // QNURLSAFEBASE64WIDGET_H
