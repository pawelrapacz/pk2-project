#pragma once

#include <filesystem>

#include "App.h"
#include "CityGraph.h"

namespace citymap
{

    class FileHandler {
    public:
        FileHandler(const App::CliOptions&);
        ~FileHandler() = default;

        void loadCoordinates(CityGraph&);
        void loadConnections(CityGraph&);
        // void loadQueries();
        // void writeOutput();

    private:
        using path_type     = std::filesystem::path;
        using path_type_ref = const std::filesystem::path&;

        path_type_ref coords;
        path_type_ref connect;
        path_type_ref quries;
        path_type_ref output;
    };

}  // namespace citymap