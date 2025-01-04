#include "TxtParser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Point> TxtParser::parse(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string group;
        if (!std::getline(iss, group, ':')) {
            throw std::runtime_error("Invalid string format: " + line);
        }
        std::string coords;
        if (!std::getline(iss, coords)) {
            throw std::runtime_error("Invalid coordinate format in string: " + line);
        }
        size_t comma = coords.find(',');
        if (comma == std::string::npos) {
            throw std::runtime_error("Invalid coordinate format in string: " + line);
        }
        uint32_t x = std::stoi(coords.substr(0, comma));
        uint32_t y = std::stoi(coords.substr(comma + 1));
        points.push_back(Point{group, x, y});
    }

    infile.close();
    return points;
}
