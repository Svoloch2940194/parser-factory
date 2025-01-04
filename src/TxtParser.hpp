#ifndef TXTPARSER_H
#define TXTPARSER_H

#include "Parser.hpp"

class TxtParser : public Parser {
public:
    std::vector<Point> parse(const std::string& filename) override;
};

#endif // TXTPARSER_H
