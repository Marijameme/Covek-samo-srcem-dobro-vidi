#ifndef STEGCORE_IMAGECONTEXT_H
#define STEGCORE_IMAGECONTEXT_H

#include <cstdint>
#include <string>
#include <vector>

#include <opencv2/core.hpp>

#include "stegcore/ImageFormats.h"

namespace stegcore
{

// Everything an Analyzer needs about the target image: decoded pixels for
// pixel-domain checks, raw bytes for structural checks, plus format info.
class ImageContext
{
  public:
    // Reads the file from disk. Throws std::runtime_error when the file cannot be
    // opened. A format OpenCV cannot decode is not an error: pixels() is then empty.
    static ImageContext load(const std::string &path);

    const std::string &path() const
    {
        return m_path;
    }
    ImageFormat format() const
    {
        return m_format;
    }
    const std::string &mimeType() const
    {
        return m_mime;
    }

    // BGR, 8-bit, 3-channel (cv::imread with IMREAD_COLOR). May be empty.
    const cv::Mat &pixels() const
    {
        return m_pixels;
    }

    // Full file contents for structural / signature / strings analysis.
    const std::vector<std::uint8_t> &bytes() const
    {
        return m_bytes;
    }

  private:
    std::string m_path;
    std::string m_mime;
    ImageFormat m_format = ImageFormat::UNKNOWN;
    cv::Mat m_pixels;
    std::vector<std::uint8_t> m_bytes;
};

} // namespace stegcore

#endif // STEGCORE_IMAGECONTEXT_H
