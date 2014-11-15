#ifndef QNCREATERSMANAGEOPERATIONWIDGET_H
#define QNCREATERSMANAGEOPERATIONWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QComboBox;
class QTextEdit;
class QLabel;

class QNCreateRSManageOperationWidget : public QWidget
{
    Q_OBJECT

private:
    const int STAT_INDEX;
    const int COPY_INDEX;
    const int MOVE_INDEX;
    const int DELETE_INDEX;
    const int CHGM_INDEX;

    QComboBox *operationTypeComboBox;
    //for stat, delete, chgm
    QLineEdit *bucketLineEdit;
    QLineEdit *keyLineEdit;

    //for copy and move
    QLineEdit *srcBucketLineEdit;
    QLineEdit *srcKeyLineEdit;
    QLineEdit *destBucketLineEdit;
    QLineEdit *destKeyLineEdit;

    //for chgm
    QLabel *newMimeTypeLabel;
    QLineEdit *newMimeTypeLineEdit;
    QTextEdit *operationTextEdit;
    QPushButton *createOperationButton;

    //reusuable widgets
    QWidget *gridBKMWidget;
    QWidget *gridCMWidget;

    void createLayout();

public:
    explicit QNCreateRSManageOperationWidget(QWidget *parent = 0);

signals:

public slots:
    void createOperationSlot();
    void updateLayoutAccordingToOperationTypeSlot(int currentIndex);
};

#endif // QNCREATERSMANAGEOPERATIONWIDGET_H
