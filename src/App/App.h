#pragma once

#include <filesystem>

#include "Map.h"
#include "Path.h"
#include "clipper.hpp"

namespace citymap
{

    class App {
    public:
        struct CliOptions {
            bool help;
            std::filesystem::path coordsFile;
            std::filesystem::path connectFile;
            std::filesystem::path queriesFile;
            std::filesystem::path outputFile;
        };

        App(CLI::arg_count, CLI::args);
        ~App() = default;

        void run();
        
    private:
        inline void handleCli();
        inline void loadInputs();

    private:
        const CLI::arg_count argc_;
        const CLI::args argv_;
        CLI::clipper cli_;
        CliOptions options_;
        Map map_;
        PolymorphicPathList foundPaths_;
    };

}  // namespace citymap