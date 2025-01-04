#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <cstdint>
#include <map>

struct Point {
    std::string group;
    uint32_t x;
    uint32_t y;
};

class Parser {
public:
    virtual ~Parser() = default;
    virtual std::vector<Point> parse(const std::string& filename) = 0;
};

class ParserFactory {
public:
    static Parser* createParser(const std::string& extension);
};

#endif // PARSER_H
