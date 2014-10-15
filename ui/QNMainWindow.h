#ifndef QNMAINWINDOW_H
#define QNMAINWINDOW_H

#include <QMainWindow>

class QNMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QNMainWindow(QWidget *parent = 0);
    ~QNMainWindow();
};

#endif // QNMAINWINDOW_H
