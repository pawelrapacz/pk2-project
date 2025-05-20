#include "FileHandler.h"

#include <fstream>

using namespace citymap;

void FileHandler::loadCoordinates(FilePathRef path, Map& map) {
    std::ifstream file(path);
    int id, x, y;
    std::string name;

    while (!file.eof()) {
        file >> id >> name >> x >> y;
        map.addPoint(id, name, {x, y});
    }
    file.close();
}

void FileHandler::loadConnections(FilePathRef path, Map& map) {
    std::ifstream file(path);
    bool hasConnection;

    for(std::size_t i = 0; !file.eof(); i++) {
        for(std::size_t j = 0; j < map.size(); j++) {
            file >> hasConnection;
            if (hasConnection)
                map.addConnection(i, j);
        }
    }
    file.close();
}

// void citymap::FileHandler::loadQueries(FilePathRef path) {}

// void citymap::FileHandler::writeOutput(FilePathRef path) {}

// void FileHandler::writeOutput(FilePathRef, const PolymorphicPathList&) {}

bool FileHandler::fail() const noexcept {
    return err_.size();
}

const std::vector<std::string>& FileHandler::errorList() const noexcept {
    return err_;
}