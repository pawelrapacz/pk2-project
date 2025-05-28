#include "FileHandler.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <fstream>
#include <limits>
#include <stdexcept>

using namespace citymap;

void FileHandler::loadCoordinates(FilePathRef path, Map& map) {
    std::ifstream file(path);
    if (fail() || !checkInputFile(path)) return;

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
    }
    file.close();
}

void FileHandler::loadConnections(FilePathRef path, Map& map) {
    if (fail() || !checkInputFile(path)) return;
    std::ifstream file(path);
    bool hasConnection;

    for (auto i : idSequence_) {
        for (auto j : idSequence_) {
            file >> hasConnection;
            if (hasConnection) map.addConnection(i, j);
        }
        // skip whitespace, but don't exit on eof,
        // because the loop will automatically end when the whole matrix is read,
        // if any value is mising it will fail
        if (!file.eof()) file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (!file) err_ = "An error occured while reading file: " + path.string();
    file.close();
}

void FileHandler::loadQueries(FilePathRef path, std::vector<UnifiedQuery>& queries, PathType type,
                              const Map& map) {
    if (fail() || !checkInputFile(path)) return;
    std::ifstream file(path);
    std::string from, to;
    while (file >> from >> to) {
        if (!validateQueryPoints(from, to, map))
            break;
        else
            queries.emplace_back(from, to, map, type);

        if (file.eof()) break;
    }

    if (!file) err_ = "An error occured while reading file: " + path.string();
    file.close();
}

void FileHandler::writeOutput(FilePathRef path, const PolymorphicPathList& paths, const Map& map) {
    if (fail()) return;
    std::ofstream file(path);

    std::ranges::for_each(paths, [&map, &file](auto& pptr) {
        if (pptr->points().empty()) return;

        if (pptr->type() == PathType::Pedestrian)
            file << "Pedestrian route: ";
        else
            file << "Car route: ";

        file << map.describe({pptr->from(), pptr->to()}, " -> ");
        file << ' ' << pptr->distance() << '\n';
        file << map.describe(*pptr, " -> ") << "\n\n";
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
        err_ = "An error occured while reading connections file, key: " + from + " does not exist.";
        return false;
    }
    else if (!map.contains(to)) {
        err_ = "An error occured while reading connections file, key: " + to + " does not exist.";
        return false;
    }
    else
        return true;
}

bool FileHandler::checkInputFile(FilePathRef path) {
    if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)
        && not std::filesystem::is_empty(path))
    {
        return true;
    }
    else {
        err_ = "File: " + path.string() + " does not exist, is empty or is not a regular file.";
        return false;
    }
}