#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "Parser.hpp"

class JsonParser : public Parser {
public:
    std::vector<Point> parse(const std::string& filename) override;
};

#endif // JSONPARSER_H
