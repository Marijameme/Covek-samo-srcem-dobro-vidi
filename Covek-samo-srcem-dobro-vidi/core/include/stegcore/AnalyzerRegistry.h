#ifndef STEGCORE_ANALYZERREGISTRY_H
#define STEGCORE_ANALYZERREGISTRY_H

#include <vector>

#include "stegcore/Analyzer.h"

namespace stegcore
{

// Owns one instance of every built-in analyzer. Add a technique by registering it
// in the constructor (AnalyzerRegistry.cpp) - nothing else changes.
class AnalyzerRegistry
{
  public:
    AnalyzerRegistry();

    const std::vector<AnalyzerPtr> &analyzers() const
    {
        return m_analyzers;
    }

    // Runs every analyzer whose supports() accepts the image's format.
    std::vector<Finding> runAll(const ImageContext &image) const;

  private:
    std::vector<AnalyzerPtr> m_analyzers;
};

} // namespace stegcore

#endif // STEGCORE_ANALYZERREGISTRY_H
