#ifndef STEGCORE_METADATA_H
#define STEGCORE_METADATA_H

#include <string>
#include <vector>

#include "stegcore/ImageFormats.h"

namespace stegcore
{

struct MetadataEntry
{
    std::string group; // "Exif", "Iptc" or "Xmp"
    std::string key;
    std::string value;
};

// Thin wrapper around Exiv2. This is the only place in the code base that talks
// to a metadata library, so swapping / extending it stays local.
namespace Metadata
{

// MIME type as reported by Exiv2, e.g. "image/jpeg". Empty when unknown.
std::string mimeType(const std::string &path);

// mimeType() mapped onto the ImageFormat enum.
ImageFormat detectFormat(const std::string &path);

// Every Exif + IPTC + XMP record in the file. Empty when the file carries none
// or cannot be parsed.
std::vector<MetadataEntry> readAll(const std::string &path);

} // namespace Metadata

} // namespace stegcore

#endif // STEGCORE_METADATA_H
