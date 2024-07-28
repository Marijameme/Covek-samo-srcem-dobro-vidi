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
    {"jpeg", imageFormat::JPEG},
    {"tiff", imageFormat::TIFF},
    {"bmp", imageFormat::BMP},
    {"unknown", imageFormat::UNKNOWN}
};

const std::map<imageFormat, std::string> toStdString = {
    {imageFormat::BMP, "bmp"},
    {imageFormat::JPEG, "jpeg"},
    {imageFormat::PNG, "png"},
    {imageFormat::TIFF, "tiff"},
    {imageFormat::UNKNOWN, "unknown"}
};

const std::set<imageFormat> exifCompatible = {
    imageFormat::JPEG,
    imageFormat::BMP
};

#endif // IMAGEFORMATS_H
