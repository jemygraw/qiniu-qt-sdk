#include "QNImageView2.h"
#include <QString>


int QNImageView2::getMode() const
{
    return mode;
}

void QNImageView2::setMode(int value)
{
    mode = value;
}

int QNImageView2::getWidth() const
{
    return width;
}

void QNImageView2::setWidth(int value)
{
    width = value;
}

int QNImageView2::getHeight() const
{
    return height;
}

void QNImageView2::setHeight(int value)
{
    height = value;
}

int QNImageView2::getQuality() const
{
    return quality;
}

void QNImageView2::setQuality(int value)
{
    quality = value;
}

QString *QNImageView2::getFormat() const
{
    return format;
}

void QNImageView2::setFormat(QString *value)
{
    format = value;
}

int QNImageView2::getInterlace() const
{
    return interlace;
}

void QNImageView2::setInterlace(int value)
{
    interlace = value;
}
QNImageView2::QNImageView2(QString &rawUrl):rawUrl(rawUrl)
{
    this->mode=-1; //not set
    this->width=-1;//not set
    this->height=-1;//not set
    this->quality=-1;//default 85
    this->interlace=-1;//default 0
    this->format=0; //not set
}

QString QNImageView2::makeImageViewUrl()
{
    QString viewUrl=QString(rawUrl);
    viewUrl.append("?imageView2");
    if(this->mode>=0)
    {
        viewUrl.append("/").append(QString::number(mode));
    }
    if(this->width>=0)
    {
        viewUrl.append("/w/").append(QString::number(width));
    }
    if(this->height>=0)
    {
        viewUrl.append("/h/").append(QString::number(height));
    }
    if(this->quality>0)
    {
        viewUrl.append("/q/").append(QString::number(quality));
    }
    if(this->format!=0)
    {
        viewUrl.append("/format/").append(*format);
    }
    if(this->interlace>=0)
    {
        viewUrl.append("/interlace/").append(QString::number(interlace));
    }
    return viewUrl;
}

