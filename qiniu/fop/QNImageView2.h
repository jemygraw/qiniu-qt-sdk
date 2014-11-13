#ifndef QNIMAGEVIEW2_H
#define QNIMAGEVIEW2_H

class QString;

class QNImageView2
{
private:
    QString &rawUrl;
    int mode;
    int width;
    int height;
    int quality;
    QString *format;
    int interlace;
public:
    QNImageView2(QString &rawUrl);
    QString makeImageViewUrl();
    int getMode() const;
    void setMode(int value);
    int getWidth() const;
    void setWidth(int value);
    int getHeight() const;
    void setHeight(int value);
    int getQuality() const;
    void setQuality(int value);
    QString *getFormat() const;
    void setFormat(QString *value);
    int getInterlace() const;
    void setInterlace(int value);
};

#endif // QNIMAGEVIEW2_H
