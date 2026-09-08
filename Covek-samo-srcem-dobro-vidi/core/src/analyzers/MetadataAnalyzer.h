#ifndef STEGCORE_METADATAANALYZER_H
#define STEGCORE_METADATAANALYZER_H

#include "stegcore/Analyzer.h"

namespace stegcore
{

// Lists every Exif / IPTC / XMP record and flags unusually large text fields,
// a common place to stash a payload.
class MetadataAnalyzer : public Analyzer
{
  public:
    std::string id() const override
    {
        return "metadata";
    }
    std::string name() const override
    {
        return "Metadata (Exif / IPTC / XMP)";
    }
    bool supports(ImageFormat) const override
    {
        return true;
    }
    Finding run(const ImageContext &image) const override;
};

} // namespace stegcore

#endif // STEGCORE_METADATAANALYZER_H
