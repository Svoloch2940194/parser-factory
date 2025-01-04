#include "Parser.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No files specified for processing.\n";
        return 1;
    }

    std::map<std::string, std::vector<Point>> data;

    try {
        #pragma omp parallel for
        for (int i = 1; i < argc; ++i) {
            std::string filepath = argv[i];
            size_t dot = filepath.find_last_of('.');
            if (dot == std::string::npos) {
                throw std::runtime_error("Unknown file format: " + filepath);
           }
            std::string ext = filepath.substr(dot);
            Parser* parser = ParserFactory::createParser(ext);
            if (!parser) {
                throw std::runtime_error("Unknown file format: " + filepath);
            }
            std::vector<Point> points = parser->parse(filepath);
            delete parser;

            #pragma omp critical
            {
                data[filepath] = points;
            }
        }

        json output;
        for (const auto& [filename, points] : data) {
            for (const auto& point : points) {
                json point_json;
                point_json["file"] = filename;
                point_json["group"] = point.group;
                point_json["x"] = point.x;
                point_json["y"] = point.y;
                output["points"].push_back(point_json);
            }
        }

        std::cout << output.dump();
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
