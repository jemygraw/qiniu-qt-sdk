#ifndef QNIMAGEVIEW2WIDGET_H
#define QNIMAGEVIEW2WIDGET_H

#include <QWidget>
class QComboBox;
class QLabel;
class QPushButton;
class QSpinBox;
class QLineEdit;

class QNImageView2Widget : public QWidget
{
    Q_OBJECT
private:
    QLabel *docLabel;

    QLabel *widthLabel;
    QLabel *heightLabel;

    QLineEdit *srcImageUrlLineEdit;

    QComboBox *modeComboBox;
    QLineEdit *widthLineEdit;
    QLineEdit *heightLineEdit;
    QSpinBox  *qualitySpinBox;
    QComboBox *formatComboBox;
    QComboBox *interlaceComboBox;

    QPushButton *generateViewUrlButton;
    QLabel *generatedViewUrlLabel;

    void createLayout();
    void setWidgetData();
public:
    explicit QNImageView2Widget(QWidget *parent = 0);

signals:

public slots:
    void generateViewUrlSlot();
    void updateWidthHeightLabel(int newIndex);
};

#endif // QNIMAGEVIEW2WIDGET_H
