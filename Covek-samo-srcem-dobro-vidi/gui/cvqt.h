#ifndef CVQT_H
#define CVQT_H

#include <QImage>
#include <opencv2/core.hpp>

// OpenCV <-> Qt bridging. Lives on the GUI side so stegcore stays Qt-free.
namespace cvqt
{

// Deep-copies a continuous 8-bit 1- or 3-channel cv::Mat into a QImage that owns
// its pixels. 3-channel input is assumed BGR and swapped to RGB. Returns a null
// QImage for unsupported layouts.
QImage matToQImage(const cv::Mat &mat);

} // namespace cvqt

#endif // CVQT_H
