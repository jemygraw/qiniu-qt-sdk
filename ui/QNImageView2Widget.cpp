#include "QNImageView2Widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include <QString>
#include <QStringList>
#include "qiniu/fop/QNImageView2.h"

QNImageView2Widget::QNImageView2Widget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle(tr("ImageView2"));
    this->createLayout();
    this->setWidgetData();
}

void QNImageView2Widget::createLayout()
{
    QGridLayout *mainLayout=new QGridLayout(this);
    docLabel=new QLabel("<a href='http://developer.qiniu.com/docs/v6/api/reference/fop/image/imageview2.html'>"+tr("Document")+"</a>");
    docLabel->setOpenExternalLinks(true);
    QLabel *srcUrlLabel=new QLabel(tr("Src Image Url:"));
    srcImageUrlLineEdit=new QLineEdit(this);
    QLabel *modeLabel=new QLabel(tr("Mode:"));
    modeComboBox=new QComboBox(this);
    widthLabel=new QLabel(tr("Width:"));
    widthLineEdit=new QLineEdit(this);
    heightLabel=new QLabel(tr("Height:"));
    heightLineEdit=new QLineEdit(this);
    QLabel *qualityLabel=new QLabel(tr("Quality:"));
    qualitySpinBox=new QSpinBox(this);
    QLabel *formatLabel=new QLabel(tr("Format:"));
    formatComboBox=new QComboBox(this);
    formatComboBox->setEditable(true);
    QLabel *interlaceLabel=new QLabel(tr("Interlace:"));
    interlaceComboBox=new QComboBox(this);
    generateViewUrlButton=new QPushButton(tr("Generate"));
    generatedViewUrlLabel=new QLabel("");
    generatedViewUrlLabel->setOpenExternalLinks(true);

    //row 1
    mainLayout->addWidget(docLabel,0,0,1,4);
    //row 2
    mainLayout->addWidget(srcUrlLabel,1,0);
    mainLayout->addWidget(srcImageUrlLineEdit,1,1,1,3);
    //row 3
    mainLayout->addWidget(modeLabel,2,0);
    mainLayout->addWidget(modeComboBox,2,1);
    mainLayout->addWidget(qualityLabel,2,2);
    mainLayout->addWidget(qualitySpinBox,2,3);
    //row 4
    mainLayout->addWidget(widthLabel,3,0);
    mainLayout->addWidget(widthLineEdit,3,1);
    mainLayout->addWidget(formatLabel,3,2);
    mainLayout->addWidget(formatComboBox,3,3);
    //row 5
    mainLayout->addWidget(heightLabel,4,0);
    mainLayout->addWidget(heightLineEdit,4,1);
    mainLayout->addWidget(interlaceLabel,4,2);
    mainLayout->addWidget(interlaceComboBox,4,3);
    //row 6
    mainLayout->addWidget(generateViewUrlButton,5,3);
    //row 7
    mainLayout->addWidget(generatedViewUrlLabel,6,0,1,4);
    this->setLayout(mainLayout);

    connect(generateViewUrlButton,SIGNAL(clicked()),this,SLOT(generateViewUrlSlot()));
    connect(modeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateWidthHeightLabel(int)));
}

void QNImageView2Widget::setWidgetData()
{
    //mode
    QStringList modeDataList;
    modeDataList.append("Mode 0");
    modeDataList.append("Mode 1");
    modeDataList.append("Mode 2");
    modeDataList.append("Mode 3");
    modeDataList.append("Mode 4");
    modeDataList.append("Mode 5");
    modeComboBox->addItems(modeDataList);
    //quality
    qualitySpinBox->setMaximum(100);
    qualitySpinBox->setMinimum(1);
    qualitySpinBox->setValue(85);
    //format
    QStringList formatDataList;
    formatDataList.append(tr("Default"));
    formatDataList.append("jpg");
    formatDataList.append("gif");
    formatDataList.append("png");
    formatDataList.append("webp");
    formatComboBox->addItems(formatDataList);

    QStringList interlaceDataList;
    interlaceDataList.append(tr("Default"));
    interlaceDataList.append("YES");
    interlaceDataList.append("NO");
    interlaceComboBox->addItems(interlaceDataList);
}

void QNImageView2Widget::generateViewUrlSlot()
{
    QString srcImageUrl=srcImageUrlLineEdit->text().trimmed();
    int mode=modeComboBox->currentIndex();
    int width=widthLineEdit->text().trimmed().toInt();
    int height=heightLineEdit->text().trimmed().toInt();
    int quality=qualitySpinBox->value();
    QString format=formatComboBox->currentText().trimmed();
    int interlace=interlaceComboBox->currentIndex()-1;
    //check value valid

    //
    QNImageView2 *imageView=new QNImageView2(srcImageUrl);
    imageView->setMode(mode);
    imageView->setWidth(width);
    imageView->setHeight(height);
    imageView->setQuality(quality);
    if(format.compare("Default",Qt::CaseInsensitive)!=0)
    {
        imageView->setFormat(&format);
    }
    imageView->setInterlace(interlace);
    QString newImageUrl=imageView->makeImageViewUrl();
    this->generatedViewUrlLabel->setText("<a href='"+newImageUrl+"'>"+newImageUrl+"</a>");
    delete imageView;
}

void QNImageView2Widget::updateWidthHeightLabel(int newIndex)
{
    int mode=newIndex;
    switch(mode)
    {
    case 0:
    case 4:
    case 5:
        widthLabel->setText(tr("LongEdge:"));
        heightLabel->setText(tr("ShortEdge:"));
        break;
    default:
        widthLabel->setText(tr("Width:"));
        heightLabel->setText(tr("Height:"));
        break;
    }
}
