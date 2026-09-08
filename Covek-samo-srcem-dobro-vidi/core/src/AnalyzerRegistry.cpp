#include "stegcore/AnalyzerRegistry.h"

#include "analyzers/MetadataAnalyzer.h"
#include "analyzers/TrailingDataAnalyzer.h"

namespace stegcore
{

AnalyzerRegistry::AnalyzerRegistry()
{
    // Register built-in analyzers here. Order is the order results are shown in.
    m_analyzers.push_back(std::make_unique<MetadataAnalyzer>());
    m_analyzers.push_back(std::make_unique<TrailingDataAnalyzer>());
}

std::vector<Finding> AnalyzerRegistry::runAll(const ImageContext &image) const
{
    std::vector<Finding> findings;
    findings.reserve(m_analyzers.size());
    for (const AnalyzerPtr &analyzer : m_analyzers)
    {
        if (analyzer->supports(image.format()))
            findings.push_back(analyzer->run(image));
    }
    return findings;
}

} // namespace stegcore
