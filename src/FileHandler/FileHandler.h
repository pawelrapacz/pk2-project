#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Map.h"
#include "Path.h"

namespace citymap
{

    class FileHandler {
        using FilePath    = std::filesystem::path;
        using FilePathRef = const std::filesystem::path&;

    public:
        FileHandler()  = default;
        ~FileHandler() = default;

        void loadCoordinates(FilePathRef, Map&);
        void loadConnections(FilePathRef, Map&);
        // void loadQueries(FilePathRef);
        void writeOutput(FilePathRef, const Map&, const PolymorphicPathList&);
        bool fail() const noexcept;
        void clear() noexcept;
        const std::string& error() const noexcept;

    private:
        std::string err_;
        PointId firstMapId_ {};
    };

}  // namespace citymap