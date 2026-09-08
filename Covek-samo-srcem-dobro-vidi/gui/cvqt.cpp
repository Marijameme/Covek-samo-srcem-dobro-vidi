#include "cvqt.h"

#include <cstring>

namespace cvqt
{

QImage matToQImage(const cv::Mat &mat)
{
    if (mat.empty() || !mat.isContinuous())
        return QImage();

    const int channels = mat.channels();
    QImage::Format format;
    if (channels == 1)
        format = QImage::Format_Grayscale8;
    else if (channels == 3)
        format = QImage::Format_RGB888;
    else
        return QImage();

    QImage image(mat.cols, mat.rows, format);
    const int lineBytes = mat.cols * channels;
    for (int y = 0; y < mat.rows; ++y)
        std::memcpy(image.scanLine(y), mat.ptr(y), static_cast<std::size_t>(lineBytes));

    return channels == 3 ? image.rgbSwapped() : image;
}

} // namespace cvqt
