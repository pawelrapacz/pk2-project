#include "FileHandler.h"

#include <algorithm>
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

void FileHandler::writeOutput(FilePathRef filePath, const Map& map,
                              const PolymorphicPathList& paths) {
    std::ofstream file(filePath);
    if (!file) return;
    std::ranges::for_each(paths, [&map, &file](auto& path) {
        if (path->type() == PathType::Pedestrian)
            file << "Pedestrian route: ";
        else
            file << "Car route: ";

        file << map.nameOf(path->from()) << " -> " << map.nameOf(path->to()) << ": ";
        file << path->distance() << "\n";
        file << map.describe(*path, " -> ");
    });
    file.close();
}

bool FileHandler::fail() const noexcept {
    return err_.size();
}

const std::vector<std::string>& FileHandler::errorList() const noexcept {
    return err_;
}