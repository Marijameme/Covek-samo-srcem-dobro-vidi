#ifndef STEGCORE_IMAGEFORMATS_H
#define STEGCORE_IMAGEFORMATS_H

#include <map>
#include <set>
#include <string>

namespace stegcore
{

enum class ImageFormat
{
    JPEG,
    PNG,
    TIFF,
    BMP,
    GIF,
    UNKNOWN
};

// MIME subtype ("jpeg", "png", ...) -> ImageFormat
inline const std::map<std::string, ImageFormat> toImageFormat = {
    {"png", ImageFormat::PNG},   {"jpeg", ImageFormat::JPEG}, {"tiff", ImageFormat::TIFF},
    {"bmp", ImageFormat::BMP},   {"gif", ImageFormat::GIF},   {"unknown", ImageFormat::UNKNOWN},
};

inline const std::map<ImageFormat, std::string> toStdString = {
    {ImageFormat::BMP, "bmp"},   {ImageFormat::JPEG, "jpeg"}, {ImageFormat::PNG, "png"},
    {ImageFormat::TIFF, "tiff"}, {ImageFormat::GIF, "gif"},   {ImageFormat::UNKNOWN, "unknown"},
};

// Formats that routinely carry Exif metadata.
inline const std::set<ImageFormat> exifCompatible = {
    ImageFormat::JPEG,
    ImageFormat::TIFF,
};

inline std::string toString(ImageFormat format)
{
    const auto it = toStdString.find(format);
    return it == toStdString.end() ? "unknown" : it->second;
}

} // namespace stegcore

#endif // STEGCORE_IMAGEFORMATS_H
