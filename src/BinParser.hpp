#ifndef BINPARSER_H
#define BINPARSER_H

#include "Parser.hpp"

class BinParser : public Parser {
public:
    std::vector<Point> parse(const std::string& filename) override;
};

#endif // BINPARSER_H
