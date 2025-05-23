#include "FileHandler.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <fstream>
#include <limits>

using namespace citymap;

void FileHandler::loadCoordinates(FilePathRef path, Map& map) {
    std::ifstream file(path);
    setFirstMapId(file);
    if (fail()) return;

    std::size_t lineCount {};
    int id, x, y;
    std::string name;

    while (file >> id >> name >> x >> y) {
        lineCount++;
        idSequence_.push_back(id);
        if (Map::npnt == map.addPoint(id, name, {x, y})) {
            err_ = "An error occured while reading file: " + path.string()
                   + "\n Invalid or missing parameter(s) on line: " + std::to_string(lineCount);
            break;
        }

        // skip whitespace
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (file.eof()) break;
    }
    file.close();
}

void FileHandler::loadConnections(FilePathRef path, Map& map) {
    if (fail()) return;
    std::ifstream file(path);
    bool hasConnection;

    for (auto i : idSequence_) {
        // skip whitespace, but don't exit on eof,
        // because the loop will automatically end when the whole matrix is read,
        // if any value is mising it will fail
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (auto j : idSequence_) {
            file >> hasConnection;
            if (hasConnection) map.addConnection(i, j);
        }
    }

    if (!file) err_ = "An error occured while reading file: " + path.string();
    file.close();
}

void FileHandler::loadQueries(FilePathRef path, std::vector<UnifiedQuery>& queries, PathType type,
                              const Map& map) {
    if (fail()) return;
    std::ifstream file(path);
    std::string from, to;
    while (file >> from >> to) {
        if (!validateQueryPoints(from, to, map))
            break;
        else
            queries.emplace_back(from, to, map, type);

        // skip whitespace
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (file.eof()) break;
    }

    if (!file) err_ = "An error occured while reading file: " + path.string();
    file.close();
}

void FileHandler::writeOutput(FilePathRef path, const PolymorphicPathList& paths, const Map& map) {
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
    if (!file) err_ = "An error occured while writing to file: " + path.string();
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

bool FileHandler::validateQueryPoints(const std::string& from, const std::string& to,
                                      const Map& map) noexcept {
    if (!map.contains(from)) {
        err_ = "An error occured while reading file, key: " + from + " does not exist.";
        return false;
    }
    else if (!map.contains(to)) {
        err_ = "An error occured while reading file, key: " + to + " does not exist.";
        return false;
    }
    return true;
}

void FileHandler::setFirstMapId(std::ifstream& s) {
    std::size_t count {};
    std::string id;
    do {
        id += s.get();
        count++;
    } while (std::isdigit(id.back()));

    while (count) {
        count--;
        s.unget();
    }

    if (std::from_chars(id.data(), id.data() + id.length(), firstMapId_).ec != std::errc {})
        err_ = "Could not succesfully parse first id.";

    s.seekg(std::ios::beg);
}