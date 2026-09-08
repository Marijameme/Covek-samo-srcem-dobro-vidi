#include "stegcore/Finding.h"

namespace stegcore
{

std::string toString(Verdict verdict)
{
    switch (verdict)
    {
    case Verdict::NotApplicable:
        return "not applicable";
    case Verdict::Inconclusive:
        return "inconclusive";
    case Verdict::Clean:
        return "clean";
    case Verdict::Suspicious:
        return "suspicious";
    case Verdict::Positive:
        return "positive";
    }
    return "unknown";
}

} // namespace stegcore
