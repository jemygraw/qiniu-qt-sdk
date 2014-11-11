#ifndef QNURLBASE64WIDGET_H
#define QNURLBASE64WIDGET_H
#include <QWidget>

class QPushButton;
class QTextEdit;
class QNUrlBase64Widget : public QWidget
{
    Q_OBJECT

private:
    QPushButton *encodeButton;
    QPushButton *decodeButton;

    QTextEdit *toEncodeSrcTextEdit;
    QTextEdit *toEncodeDestTextEdit;

    QTextEdit *toDecodeSrcTextEdit;
    QTextEdit *toDecodeDestTextEdit;

    void createWidgets();

public slots:
    void encodeData();
    void decodeData();

public:
    QNUrlBase64Widget(QWidget *parent=0);

};

#endif // QNURLBASE64WIDGET_H
