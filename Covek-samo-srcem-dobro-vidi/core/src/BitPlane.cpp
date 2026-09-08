#include "stegcore/BitPlane.h"

#include <stdexcept>

#include <opencv2/core.hpp>

namespace stegcore
{

BitPlane::Channel BitPlane::channelFromString(const std::string &name)
{
    if (name == "red")
        return Channel::Red;
    if (name == "green")
        return Channel::Green;
    if (name == "blue")
        return Channel::Blue;
    if (name == "superimposed")
        return Channel::All;
    throw std::invalid_argument("BitPlane: unknown channel '" + name + "'");
}

std::vector<cv::Mat> BitPlane::extract(const cv::Mat &bgr, Channel channel)
{
    if (bgr.empty())
        throw std::invalid_argument("BitPlane::extract: empty image");

    cv::Mat source;
    if (channel == Channel::All)
    {
        source = bgr; // 3 channels
    }
    else
    {
        std::vector<cv::Mat> channels;
        cv::split(bgr, channels);
        source = channels.at(static_cast<int>(channel)); // 1 channel
    }

    std::vector<cv::Mat> planes;
    planes.reserve(8);
    for (int bit = 0; bit < 8; ++bit)
    {
        const int mask = 1 << bit;
        cv::Mat plane;
        cv::bitwise_and(source, cv::Scalar::all(mask), plane);
        // mask -> 255, 0 -> 0
        plane.convertTo(plane, CV_8U, 255.0 / mask);
        planes.push_back(plane);
    }
    return planes;
}

} // namespace stegcore
