#include "colorfilter.h"

#include <iostream>
#include <vector>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <QLabel>

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"

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
    // else if(this->m_layer == ColorFilter::Layer::RED)
    //     newImages = this->superImage()

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
        alteredImages.push_back(tmp);
    }
    return alteredImages;
}

QImage ColorFilter::cvMatToQImage(const cv::Mat &image)
{
    if (image.type() == CV_8UC1) {
        // Grayscale image
        return QImage(image.data, image.cols, image.rows, image.step, QImage::Format_Grayscale8);
    } else if (image.type() == CV_8UC3) {
        // 3-channel color image (BGR format)
        // cv stores images in BGR format, but QImage expects RGB, that's why it it swapped
        return QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888).rgbSwapped();
    } else {
        qDebug() << "Unsupported cv::Mat format for QImage conversion";
        return QImage();
    }
    // return QImage(image.data, image.cols, image.rows, QImage::Format_RGB888).rgbSwapped();
}
