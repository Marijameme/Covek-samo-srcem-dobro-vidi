#include "metadata.h"
#include <QString>
#include <QWidget>
#include <iostream>
#include <string>
#include <unordered_map>

#include "exiv2/exiv2.hpp"

Metadata::Metadata() {
    // konstruktor
}

std::unordered_map<std::string, std::string> Metadata::read_data(const QString &fName)
{
    auto image = Exiv2::ImageFactory::open(fName.toStdString());
    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    if(exifData.empty())
        std::cout << "Nema metapodataka\n";

    std::unordered_map<std::string, std::string> features;
    auto end = exifData.end();
    for(auto i = exifData.begin(); i != end; i++){
        const std::string fullFieldName = i->key();
        auto pos = fullFieldName.find_last_of('.');
        const std::string fieldName = fullFieldName.substr(pos+1);
        const std::string fieldValue = i->toString();
        features[fieldName] = fieldValue;
        // std::cout << fieldName << " " << fieldValue << std::endl;
        // std::cout << std::setw(44) << std::setfill(' ') << std::left << i->key() << " "
                  // << "0x" << std::setw(4) << std::setfill('0') << std::right << std::hex << i->tag() << " "
                  // << std::setw(9) << std::setfill(' ') << std::left << (tn ? tn : "Unknown") << " " << std::dec
                  // << std::setw(3) << std::setfill(' ') << std::right << i->count() << "  " << std::dec << i->toString()
                  // << "\n";
    }
    return features;
}
