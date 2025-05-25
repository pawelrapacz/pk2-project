#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Map.h"
#include "Path.h"
#include "Query.h"

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
        void loadQueries(FilePathRef, std::vector<UnifiedQuery>&, PathType, const Map&);
        void writeOutput(FilePathRef, const PolymorphicPathList&, const Map&);
        bool fail() const noexcept;
        void clear() noexcept;
        const std::string& error() const noexcept;

    private:
        bool validateQueryPoints(const std::string&, const std::string&, const Map&) noexcept;
        void setFirstMapId(std::ifstream&);
        bool checkInputFile(FilePathRef);

        std::string err_;
        PointId firstMapId_ {};
        std::vector<PointId> idSequence_;
    };

}  // namespace citymap