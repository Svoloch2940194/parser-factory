#include "Parser.hpp"
#include "TxtParser.hpp"
#include "BinParser.hpp"
#include "JsonParser.hpp"
#include <algorithm>

Parser* ParserFactory::createParser(const std::string& extension) {
    std::string ext = extension;
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext == ".txt") {
        return new TxtParser();
    } else if (ext == ".bin") {
        return new BinParser();
    } else if (ext == ".json") {
        return new JsonParser();
    } else {
        return nullptr;
    }
}
