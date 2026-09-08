#ifndef STEGCORE_TRAILINGDATAANALYZER_H
#define STEGCORE_TRAILINGDATAANALYZER_H

#include "stegcore/Analyzer.h"

namespace stegcore
{

// Finds the logical end of the image container (PNG IEND, JPEG EOI, GIF trailer,
// BMP size field) and reports any bytes that follow it, scanning them for known
// archive / document signatures.
class TrailingDataAnalyzer : public Analyzer
{
  public:
    std::string id() const override
    {
        return "trailing-data";
    }
    std::string name() const override
    {
        return "Trailing data after end of image";
    }
    bool supports(ImageFormat format) const override;
    Finding run(const ImageContext &image) const override;
};

} // namespace stegcore

#endif // STEGCORE_TRAILINGDATAANALYZER_H
