#include "FileHandler.h"

#include <fstream>

using namespace citymap;

void FileHandler::loadCoordinates(FilePathRef path, CityGraph& graph) {
    std::ifstream file(path);
    int id, x, y;
    std::string name;

    while (!file.eof()) {
        file >> id >> name >> x >> y;
        graph.insertVertex(name, {x, y});
    }
    file.close();
}

void citymap::FileHandler::loadConnections(FilePathRef path, CityGraph& graph) {
    // if (graph.empty()) throw 1;
    // std::ifstream file(path);
    // std::vector<std::vector<int>> matrix(graph.size(), std::vector<int>(graph.size()));
    // bool hasConnection;

    // for(std::size_t i = 0; i < graph.size(); i++) {
    //     for(std::size_t j = 0; j < graph.size(); j++) {
    //         file >> hasConnection;
    //         if (hasConnection)
    //             graph.addEdge(i, j);
    //     }
    // }
    // file.close();
}

// void citymap::FileHandler::loadQueries(FilePathRef path) {}

// void citymap::FileHandler::writeOutput(FilePathRef path) {}

bool FileHandler::fail() const noexcept {
    return err_.size();
}

const std::vector<std::string>& FileHandler::errorList() const noexcept {
    return err_;
}