#include "BinParser.hpp"
#include <fstream>
#include <stdexcept>
#include <bitset>

struct PointToFile {
    uint32_t group : 8;
    uint32_t x : 12;
    uint32_t y : 12;
};

std::vector<Point> BinParser::parse(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream infile(filename, std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    PointToFile pt;
    while (infile.read(reinterpret_cast<char*>(&pt), sizeof(pt))) {
        points.push_back(Point{std::to_string(pt.group), pt.x, pt.y});
    }

    if (!infile.eof()) {
        throw std::runtime_error("Error reading binary file: " + filename);
    }

    infile.close();
    return points;
}
