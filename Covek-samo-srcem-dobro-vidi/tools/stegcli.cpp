// Headless runner for the stegcore engine. Useful for quick checks, scripting
// and (later) as the harness for automated tests.
//
//   stegcli <image-file>

#include <cstdlib>
#include <exception>
#include <iostream>

#include "stegcore/AnalyzerRegistry.h"
#include "stegcore/ImageContext.h"
#include "stegcore/ImageFormats.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " <image-file>\n";
        return EXIT_FAILURE;
    }

    stegcore::ImageContext image;
    try
    {
        image = stegcore::ImageContext::load(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "file:   " << image.path() << '\n'
              << "format: " << stegcore::toString(image.format()) << " (" << image.mimeType() << ")\n"
              << "size:   " << image.bytes().size() << " bytes\n";

    const stegcore::AnalyzerRegistry registry;
    for (const stegcore::Finding &finding : registry.runAll(image))
    {
        std::cout << "\n=== " << finding.title << " ===\n"
                  << "verdict: " << stegcore::toString(finding.verdict) << '\n';
        if (!finding.detail.empty())
            std::cout << finding.detail << '\n';
    }
    return EXIT_SUCCESS;
}
