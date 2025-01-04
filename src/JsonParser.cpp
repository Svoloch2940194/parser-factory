#include "JsonParser.hpp"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<Point> JsonParser::parse(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    json j;
    try {
        infile >> j;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("Error parsing JSON file: " + filename);
    }

    if (!j.contains("points") || !j["points"].is_array()) {
        throw std::runtime_error("Invalid JSON file format: " + filename);
    }

    for (const auto& item : j["points"]) {
        if (!item.contains("group") || !item.contains("x") || !item.contains("y")) {
            throw std::runtime_error("Invalid dot format in JSON file: " + filename);
        }
        std::string group = item["group"].get<std::string>();
        uint32_t x = item["x"].get<uint32_t>();
        uint32_t y = item["y"].get<uint32_t>();
        points.push_back(Point{group, x, y});
    }

    infile.close();
    return points;
}
