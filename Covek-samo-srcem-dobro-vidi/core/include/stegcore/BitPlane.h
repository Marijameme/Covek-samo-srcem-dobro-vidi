#ifndef STEGCORE_BITPLANE_H
#define STEGCORE_BITPLANE_H

#include <string>
#include <vector>

#include <opencv2/core.hpp>

namespace stegcore
{

// Bit-plane slicing for visual LSB inspection. Pure OpenCV, no Qt: the GUI turns
// the returned cv::Mat planes into QImage itself.
class BitPlane
{
  public:
    enum class Channel
    {
        Blue = 0,
        Green = 1,
        Red = 2,
        All // keep all three channels ("superimposed")
    };

    // Throws std::invalid_argument on an unknown name.
    static Channel channelFromString(const std::string &name);

    // Returns 8 images, one per bit position from LSB (index 0) to MSB (index 7).
    // Each plane is 8-bit, scaled so a set bit shows as 255. Single-channel for a
    // specific Channel, 3-channel for Channel::All.
    // Throws std::invalid_argument when bgr is empty.
    static std::vector<cv::Mat> extract(const cv::Mat &bgr, Channel channel);
};

} // namespace stegcore

#endif // STEGCORE_BITPLANE_H
