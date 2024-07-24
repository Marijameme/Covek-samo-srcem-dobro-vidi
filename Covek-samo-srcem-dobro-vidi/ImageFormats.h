#ifndef IMAGEFORMATS_H
#define IMAGEFORMATS_H

#include <map>
#include <set>

enum class imageFormat{
    JPEG,
    PNG,
    TIFF,
    BMP,
    UNKNOWN
};

const std::map<std::string, imageFormat> toImageFormat = {
    {"png", imageFormat::PNG},
    {"jpg", imageFormat::JPEG},
    {"tiff", imageFormat::TIFF},
    {"bmp", imageFormat::BMP},
    {"unknown", imageFormat::UNKNOWN}
};

const std::set<imageFormat> exifCompatible = {
    imageFormat::JPEG,
    imageFormat::BMP
};

#endif // IMAGEFORMATS_H
