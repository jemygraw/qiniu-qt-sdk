#ifndef QNIMAGEWATERMARK_H
#define QNIMAGEWATERMARK_H
class QString;

class QNImageWatermark
{
private:
    int mode;
    //picture watermark
    QString *watermarkImageUrl;
    //text watermark
    QString *watermarkText;
    QString *fontName;
    int fontSize;
    QString *fontFillColor;
    //shared attributes
    int dissolve;
    QString *gravity;
    int distanceX;
    int distanceY;
public:
    QNImageWatermark();
};

#endif // QNIMAGEWATERMARK_H
