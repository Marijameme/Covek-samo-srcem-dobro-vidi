#include "analyzers/MetadataAnalyzer.h"

#include <sstream>

#include "stegcore/Metadata.h"

namespace stegcore
{

namespace
{
constexpr std::size_t kLargeFieldBytes = 512;
}

Finding MetadataAnalyzer::run(const ImageContext &image) const
{
    Finding finding;
    finding.title = name();

    const std::vector<MetadataEntry> entries = Metadata::readAll(image.path());
    if (entries.empty())
    {
        finding.verdict = Verdict::NotApplicable;
        finding.detail = "No Exif, IPTC or XMP metadata found.";
        return finding;
    }

    std::size_t largeFields = 0;
    std::ostringstream out;
    for (const MetadataEntry &entry : entries)
    {
        out << '[' << entry.group << "] " << entry.key << " = " << entry.value << '\n';
        if (entry.value.size() > kLargeFieldBytes)
            ++largeFields;
    }
    finding.detail = out.str();

    if (largeFields > 0)
    {
        finding.verdict = Verdict::Suspicious;
        finding.score = 0.5;
        finding.detail += '\n' + std::to_string(largeFields) + " field(s) exceed " +
                          std::to_string(kLargeFieldBytes) +
                          " bytes - possible embedded payload.\n";
    }
    else
    {
        finding.verdict = Verdict::Inconclusive;
    }
    return finding;
}

} // namespace stegcore
