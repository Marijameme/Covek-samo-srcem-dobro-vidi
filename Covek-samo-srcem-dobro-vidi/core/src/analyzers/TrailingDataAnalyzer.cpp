#include "analyzers/TrailingDataAnalyzer.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <optional>
#include <sstream>

namespace stegcore
{

namespace
{

using Bytes = std::vector<std::uint8_t>;

bool startsWith(const Bytes &b, std::initializer_list<std::uint8_t> sig)
{
    if (b.size() < sig.size())
        return false;
    std::size_t i = 0;
    for (std::uint8_t s : sig)
        if (b[i++] != s)
            return false;
    return true;
}

std::optional<std::size_t> find(const Bytes &b, const std::vector<std::uint8_t> &pat,
                                std::size_t from = 0)
{
    if (pat.empty() || b.size() < pat.size())
        return std::nullopt;
    for (std::size_t i = from; i + pat.size() <= b.size(); ++i)
    {
        bool hit = true;
        for (std::size_t j = 0; j < pat.size(); ++j)
            if (b[i + j] != pat[j])
            {
                hit = false;
                break;
            }
        if (hit)
            return i;
    }
    return std::nullopt;
}

std::optional<std::size_t> rfind(const Bytes &b, const std::vector<std::uint8_t> &pat)
{
    if (pat.empty() || b.size() < pat.size())
        return std::nullopt;
    for (std::size_t i = b.size() - pat.size() + 1; i-- > 0;)
    {
        bool hit = true;
        for (std::size_t j = 0; j < pat.size(); ++j)
            if (b[i + j] != pat[j])
            {
                hit = false;
                break;
            }
        if (hit)
            return i;
    }
    return std::nullopt;
}

// Byte offset one past the last byte that legitimately belongs to the image.
std::optional<std::size_t> logicalEnd(const Bytes &b, ImageFormat format)
{
    switch (format)
    {
    case ImageFormat::PNG:
    {
        if (!startsWith(b, {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}))
            return std::nullopt;
        std::size_t pos = 8;
        while (pos + 8 <= b.size())
        {
            const std::uint32_t len = (std::uint32_t(b[pos]) << 24) | (std::uint32_t(b[pos + 1]) << 16) |
                                      (std::uint32_t(b[pos + 2]) << 8) | std::uint32_t(b[pos + 3]);
            const bool isEnd = b[pos + 4] == 'I' && b[pos + 5] == 'E' && b[pos + 6] == 'N' &&
                               b[pos + 7] == 'D';
            const std::size_t next = pos + 12 + len; // len + type(4) + data + crc(4)
            if (isEnd)
                return next <= b.size() ? std::optional<std::size_t>(next) : std::nullopt;
            if (next <= pos || next > b.size())
                return std::nullopt;
            pos = next;
        }
        return std::nullopt;
    }
    case ImageFormat::JPEG:
    {
        if (!startsWith(b, {0xFF, 0xD8}))
            return std::nullopt;
        const auto eoi = rfind(b, {0xFF, 0xD9});
        if (!eoi)
            return std::nullopt;
        return *eoi + 2;
    }
    case ImageFormat::GIF:
    {
        if (!startsWith(b, {'G', 'I', 'F', '8'}))
            return std::nullopt;
        const auto trailer = rfind(b, {0x3B});
        if (!trailer)
            return std::nullopt;
        return *trailer + 1;
    }
    case ImageFormat::BMP:
    {
        if (!startsWith(b, {'B', 'M'}) || b.size() < 6)
            return std::nullopt;
        const std::size_t declared = std::uint32_t(b[2]) | (std::uint32_t(b[3]) << 8) |
                                     (std::uint32_t(b[4]) << 16) | (std::uint32_t(b[5]) << 24);
        return declared <= b.size() ? std::optional<std::size_t>(declared) : std::nullopt;
    }
    default:
        return std::nullopt;
    }
}

std::string hexPreview(const Bytes &b, std::size_t from, std::size_t count)
{
    std::ostringstream out;
    const std::size_t end = std::min(b.size(), from + count);
    for (std::size_t i = from; i < end; ++i)
        out << std::hex << std::setw(2) << std::setfill('0') << int(b[i]) << ' ';
    if (end < b.size())
        out << "...";
    return out.str();
}

struct Signature
{
    const char *name;
    std::vector<std::uint8_t> magic;
};

const std::array<Signature, 6> kSignatures = {{
    {"ZIP archive (or Office / ODF / APK)", {0x50, 0x4B, 0x03, 0x04}},
    {"RAR archive", {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07}},
    {"7-Zip archive", {0x37, 0x7A, 0xBC, 0xAF, 0x27, 0x1C}},
    {"gzip stream", {0x1F, 0x8B, 0x08}},
    {"PDF document", {0x25, 0x50, 0x44, 0x46, 0x2D}},
    {"embedded PNG image", {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}},
}};

} // namespace

bool TrailingDataAnalyzer::supports(ImageFormat format) const
{
    switch (format)
    {
    case ImageFormat::PNG:
    case ImageFormat::JPEG:
    case ImageFormat::GIF:
    case ImageFormat::BMP:
        return true;
    default:
        return false;
    }
}

Finding TrailingDataAnalyzer::run(const ImageContext &image) const
{
    Finding finding;
    finding.title = name();

    const Bytes &b = image.bytes();
    const auto end = logicalEnd(b, image.format());
    if (!end)
    {
        finding.verdict = Verdict::Inconclusive;
        finding.detail = "Could not locate the end-of-image marker for this file.";
        return finding;
    }

    const std::size_t trailing = b.size() - *end;
    std::ostringstream out;
    out << "File size:      " << b.size() << " bytes\n";
    out << "End of image:   offset " << *end << "\n";
    out << "Trailing bytes: " << trailing << "\n";

    if (trailing == 0)
    {
        finding.verdict = Verdict::Clean;
        finding.detail = out.str() + "\nNothing is appended after the image.";
        return finding;
    }

    out << "\nFirst bytes:    " << hexPreview(b, *end, 32) << "\n";

    finding.verdict = Verdict::Suspicious;
    finding.score = 0.6;
    for (const Signature &sig : kSignatures)
    {
        const auto at = find(b, sig.magic, *end);
        if (at)
        {
            out << "Signature:      " << sig.name << " at offset " << *at << "\n";
            finding.verdict = Verdict::Positive;
            finding.score = 0.9;
        }
    }

    finding.detail = out.str();
    return finding;
}

} // namespace stegcore
