#include "metadata.h"
#include <QString>
#include <QWidget>
#include <iostream>
#include <string>
#include <unordered_map>

#include "ExifTool.h"
#include "exiv2/exiv2.hpp"

Metadata::Metadata()
{
    // konstruktor
}

std::unordered_map<std::string, std::string> Metadata::read_data(const QString &fName)
{
    std::unordered_map<std::string, std::string> features;
    ExifTool *tool = new ExifTool();
    // first argument must be cost char*
    TagInfo *info = tool->ImageInfo(fName.toUtf8().constData());
    if (info)
    {
        for (TagInfo *i = info; i; i = i->next)
        {
            features[i->name] = i->value;
        }
        delete info;
    }
    else if (tool->LastComplete() <= 0)
    {
        std::cerr << "Error occured while executing exiftool!" << std::endl;
    }

    delete tool;
    return features;
}

std::string Metadata::get_image_format(const QString &fName)
{
    auto image = Exiv2::ImageFactory::open(fName.toStdString());
    const std::string fullFormat = image->mimeType();
    auto ptr = fullFormat.find_last_of('/');
    return fullFormat.substr(ptr + 1);
}
