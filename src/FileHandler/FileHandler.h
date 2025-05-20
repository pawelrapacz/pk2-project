#pragma once

#include <filesystem>
#include <vector>
#include <string>


#include "Map.h"

namespace citymap
{

    class FileHandler {
        using FilePath     = std::filesystem::path;
        using FilePathRef     = const std::filesystem::path&;
    public:
        FileHandler() = default;
        ~FileHandler() = default;

        void loadCoordinates(FilePathRef, Map&);
        void loadConnections(FilePathRef, Map&);
        // void loadQueries(FilePathRef);
        // void writeOutput(FilePathRef);
        bool fail() const noexcept;
        const std::vector<std::string>& errorList() const noexcept;

    private:
        std::vector<std::string> err_;
    };

}  // namespace citymap