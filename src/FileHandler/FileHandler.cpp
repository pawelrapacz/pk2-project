#include "FileHandler.h"

#include <algorithm>
#include <fstream>

using namespace citymap;

void FileHandler::loadCoordinates(FilePathRef path, Map& map) {
    if (fail()) return;
    std::ifstream file(path);
    int id, x, y;
    std::string name;

    while (file >> id >> name >> x >> y)
        map.addPoint(id, name, {x, y});
    file.seekg(std::ios::beg);
    file >> firstMapId_;
    if (file) err_ = "An error occured while reading file: " + path.string();
    file.close();
}

void FileHandler::loadConnections(FilePathRef path, Map& map) {
    if (fail()) return;
    std::ifstream file(path);
    bool hasConnection;

    for (std::size_t i = firstMapId_; !file.eof(); i++) {
        for (std::size_t j = firstMapId_; j < map.size() + firstMapId_; j++) {
            file >> hasConnection;
            if (hasConnection) map.addConnection(i, j);
        }
    }
    if (file) err_ = "An error occured while reading file: " + path.string();
    file.close();
}

// void citymap::FileHandler::loadQueries(FilePathRef path) {}

void FileHandler::writeOutput(FilePathRef path, const Map& map, const PolymorphicPathList& paths) {
    if (fail()) return;
    std::ofstream file(path);

    std::ranges::for_each(paths, [&map, &file](auto& pptr) {
        if (pptr->type() == PathType::Pedestrian)
            file << "Pedestrian route: ";
        else
            file << "Car route: ";

        file << map.describe({pptr->from(), pptr->to()}, " -> ");
        file << pptr->distance() << "\n";
        file << map.describe(*pptr, " -> ");
    });
    if (file) err_ = "An error occured while writing to file: " + path.string();
    file.close();
}

bool FileHandler::fail() const noexcept {
    return !err_.empty();
}

void FileHandler::clear() noexcept {
    err_.clear();
}

const std::string& FileHandler::error() const noexcept {
    return err_;
}