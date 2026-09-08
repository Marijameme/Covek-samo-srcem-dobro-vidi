#include "stegcore/Metadata.h"

#include <exception>

#include <exiv2/exiv2.hpp>

namespace stegcore
{

std::string Metadata::mimeType(const std::string &path)
{
    try
    {
        // open() returns std::unique_ptr (exiv2 >= 0.28) or std::auto_ptr (0.27.x
        // as packaged by Debian); .get() works for both.
        auto image = Exiv2::ImageFactory::open(path);
        if (image.get() == nullptr)
            return {};
        image->readMetadata();
        return image->mimeType();
    }
    catch (const std::exception &)
    {
        return {};
    }
}

ImageFormat Metadata::detectFormat(const std::string &path)
{
    const std::string mime = mimeType(path);
    const auto slash = mime.find_last_of('/');
    const std::string sub = (slash == std::string::npos) ? mime : mime.substr(slash + 1);

    const auto it = toImageFormat.find(sub);
    return (it == toImageFormat.end()) ? ImageFormat::UNKNOWN : it->second;
}

std::vector<MetadataEntry> Metadata::readAll(const std::string &path)
{
    std::vector<MetadataEntry> out;
    try
    {
        auto image = Exiv2::ImageFactory::open(path);
        if (image.get() == nullptr)
            return out;
        image->readMetadata();

        const Exiv2::ExifData &exif = image->exifData();
        for (auto i = exif.begin(); i != exif.end(); ++i)
            out.push_back({"Exif", i->key(), i->toString()});

        const Exiv2::IptcData &iptc = image->iptcData();
        for (auto i = iptc.begin(); i != iptc.end(); ++i)
            out.push_back({"Iptc", i->key(), i->toString()});

        const Exiv2::XmpData &xmp = image->xmpData();
        for (auto i = xmp.begin(); i != xmp.end(); ++i)
            out.push_back({"Xmp", i->key(), i->toString()});
    }
    catch (const std::exception &)
    {
        // Return whatever was collected before the failure.
    }
    return out;
}

} // namespace stegcore
