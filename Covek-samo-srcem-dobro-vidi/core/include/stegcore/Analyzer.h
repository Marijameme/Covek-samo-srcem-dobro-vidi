#ifndef STEGCORE_ANALYZER_H
#define STEGCORE_ANALYZER_H

#include <memory>
#include <string>

#include "stegcore/Finding.h"
#include "stegcore/ImageContext.h"
#include "stegcore/ImageFormats.h"

namespace stegcore
{

// One steganalysis technique. Implementations live in core/src/analyzers/ and are
// registered in AnalyzerRegistry. The GUI never mentions a concrete analyzer.
class Analyzer
{
  public:
    virtual ~Analyzer() = default;

    // Short stable identifier, e.g. "metadata", "trailing-data".
    virtual std::string id() const = 0;

    // Human-readable name for tabs / menus.
    virtual std::string name() const = 0;

    // Whether this analyzer can say anything useful about the given format.
    virtual bool supports(ImageFormat format) const = 0;

    virtual Finding run(const ImageContext &image) const = 0;
};

using AnalyzerPtr = std::unique_ptr<Analyzer>;

} // namespace stegcore

#endif // STEGCORE_ANALYZER_H
