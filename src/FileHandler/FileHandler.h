#pragma once

#include <filesystem>
#include <vector>
#include <string>

#include "App.h"
#include "CityGraph.h"

namespace citymap
{

    class FileHandler {
        using FilePath     = std::filesystem::path;
        using FilePathRef     = const std::filesystem::path&;
    public:
        FileHandler() = default;
        ~FileHandler() = default;

        void loadCoordinates(FilePathRef, CityGraph&);
        void loadConnections(FilePathRef, CityGraph&);
        // void loadQueries(FilePathRef);
        // void writeOutput(FilePathRef);
        bool fail() const noexcept;
        const std::vector<std::string>& errorList() const noexcept;

    private:
        std::vector<std::string> err_;
    };

}  // namespace citymap