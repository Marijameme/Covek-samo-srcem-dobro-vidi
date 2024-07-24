#ifndef METADATA_H
#define METADATA_H

#include <QString>
#include <unordered_map>

class Metadata
{
public:
    Metadata();
    static std::unordered_map<std::string, std::string> read_data(const QString &fName);
};

#endif // METADATA_H
