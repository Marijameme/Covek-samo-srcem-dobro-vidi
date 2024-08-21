#ifndef COLORFILTER_H
#define COLORFILTER_H

#include "opencv2/core.hpp"
#include <QImage>
#include <QString>
#include <vector>

class ColorFilter
{
  public:
    std::vector<cv::Mat> images;
    enum class Layer
    {
        RED,
        GREEN,
        BLUE,
        SUPER,
        UNDEFINED
    };
    ColorFilter(QString &fName, ColorFilter::Layer layer);
    std::vector<QImage> getImages();
    static ColorFilter::Layer toLayer(const QString &layer);

  private:
    QString m_fName;
    Layer m_layer;
    std::vector<cv::Mat> superImage(const cv::Mat &image);
    std::vector<cv::Mat> oneLayerImage(const cv::Mat &image, int layerLevel);
    std::vector<cv::Mat> colorImage(const cv::Mat &image, const Layer color);
    QImage cvMatToQImage(cv::Mat &image);
};

#endif // COLORFILTER_H
