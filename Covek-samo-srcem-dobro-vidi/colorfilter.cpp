#include "colorfilter.h"

#include <iostream>
#include <vector>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <QLabel>

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/imgproc.hpp>

ColorFilter::ColorFilter(QString &fName, ColorFilter::Layer layer):
    m_fName{fName}, m_layer{layer}
{}

std::vector<QImage> ColorFilter::getImages()
{
    cv::Mat image = cv::imread(this->m_fName.toStdString(), cv::IMREAD_COLOR);
    if(image.empty())
        qDebug() << "No image";
    std::vector<cv::Mat> newImages;
    if(this->m_layer == ColorFilter::Layer::SUPER)
        newImages = this->superImage(image);
    else if(this->m_layer == ColorFilter::Layer::RED)
        newImages = this->oneLayerImage(image, 2);
    else if(this->m_layer == ColorFilter::Layer::GREEN)
        newImages = this->oneLayerImage(image, 1);
    else if(this->m_layer == ColorFilter::Layer::BLUE)
        newImages = this->oneLayerImage(image, 0);

    std::vector<QImage> result;
    for(auto &im : newImages)
        result.push_back(this->cvMatToQImage(im));

    return result;
}

ColorFilter::Layer ColorFilter::toLayer(const QString &layer)
{
    std::unordered_map<QString, Layer> toLayer = {
        {"red", ColorFilter::Layer::RED},
        {"blue", ColorFilter::Layer::BLUE},
        {"green", ColorFilter::Layer::GREEN},
        {"superimposed", ColorFilter::Layer::SUPER}
    };
    auto it = toLayer.find(layer);
    if(it != toLayer.end())
        return it->second;
    return ColorFilter::Layer::UNDEFINED;
}

std::vector<cv::Mat> ColorFilter::superImage(const cv::Mat &image)
{
    std::vector<cv::Mat> alteredImages;
    cv::Mat tmp;

    for(int i = 0; i < 8; i++){
        tmp = image.clone();
        for(int n = 0; n < tmp.rows; n++)
        {
            cv::Vec3b *row = tmp.ptr<cv::Vec3b>(n);
            for(int m = 0; m < tmp.cols; m++){
                cv::Vec3b &pixel = row[m];
                // pixel[i] is uchar to represent values between 0 and 255
                tmp.ptr<cv::Vec3b>(n)[m][0] = (uchar)(((((int)pixel[0]) >> i) & 1)*255);
                tmp.ptr<cv::Vec3b>(n)[m][1] = (uchar)(((((int)pixel[1]) >> i) & 1)*255);
                tmp.ptr<cv::Vec3b>(n)[m][2] = (uchar)(((((int)pixel[2]) >> i) & 1)*255);
            }
        }
        alteredImages.push_back(tmp.clone());
    }
    return alteredImages;
}

std::vector<cv::Mat> ColorFilter::oneLayerImage(const cv::Mat &image, int layerLevel)
{
    std::vector<cv::Mat> alteredImages;
    std::vector<cv::Mat> channels;
    cv::split(image, channels);
    cv::Mat tmp;

    for(int i = 0; i < 8; i++){
        tmp = channels[layerLevel].clone();
        for(int n = 0; n < tmp.rows; n++)
        {
            uchar *row = tmp.ptr<uchar>(n);
            for(int m = 0; m < tmp.cols; m++){
                uchar &pixel = row[m];
                // pixel[i] is uchar to represent values between 0 and 255
                row[m] = (uchar)(((((int)pixel) >> i) & 1)*255);

            }
        }
        alteredImages.push_back(tmp.clone());
    }

    return alteredImages;
}

QImage ColorFilter::cvMatToQImage( cv::Mat &image)
{
    if(!image.isContinuous()) {
        qDebug() << "Mat is not continuous";
        return QImage();
    }

    int chanells = image.channels();
    QImage res;
    if(1 == chanells)
        res = QImage(image.cols, image.rows, QImage::Format_Grayscale8);
    else if(3 == chanells)
        res = QImage(image.cols, image.rows, QImage::Format_RGB888);
    else
        return QImage();

    uchar *sptr,*dptr;
    int linesize = image.cols*chanells;
    for(int y = 0; y < image.rows; y++){
        sptr = image.ptr(y);
        dptr = res.scanLine(y);
        memcpy(dptr,sptr,linesize);
    }

    if(3 == chanells)
        res = res.rgbSwapped();

    return res;
}
