#ifndef STEGCORE_FINDING_H
#define STEGCORE_FINDING_H

#include <string>
#include <vector>

#include <opencv2/core.hpp>

namespace stegcore
{

enum class Verdict
{
    NotApplicable, // analyzer had nothing to work with
    Inconclusive,  // ran, but no clear signal either way
    Clean,         // ran, found nothing suspicious
    Suspicious,    // weak / partial indication of hidden data
    Positive       // strong indication of hidden data
};

std::string toString(Verdict verdict);

// Result of a single Analyzer.
struct Finding
{
    std::string title;
    Verdict verdict = Verdict::NotApplicable;
    double score = 0.0;          // analyzer-defined; 0..1 where meaningful
    std::string detail;          // human-readable, possibly multi-line report
    std::vector<cv::Mat> visuals; // optional image outputs (bit planes, residuals, ...)
};

} // namespace stegcore

#endif // STEGCORE_FINDING_H
