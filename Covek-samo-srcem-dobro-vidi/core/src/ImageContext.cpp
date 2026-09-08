#include "stegcore/ImageContext.h"

#include <fstream>
#include <iterator>
#include <stdexcept>

#include <opencv2/imgcodecs.hpp>

#include "stegcore/Metadata.h"

namespace stegcore
{

ImageContext ImageContext::load(const std::string &path)
{
    ImageContext ctx;
    ctx.m_path = path;

    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("ImageContext::load: cannot open file: " + path);

    ctx.m_bytes.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    ctx.m_mime = Metadata::mimeType(path);
    ctx.m_format = Metadata::detectFormat(path);
    ctx.m_pixels = cv::imread(path, cv::IMREAD_COLOR); // empty Mat if undecodable

    return ctx;
}

} // namespace stegcore
