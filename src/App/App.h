#pragma once

#include <filesystem>
#include <string>

#include "FileHandler.h"
#include "Map.h"
#include "Path.h"
#include "Query.h"
#include "clipper.hpp"

namespace citymap
{

    class App {
    public:
        struct CliOptions {
            bool help;
            std::string type;
            std::filesystem::path coordsFile;
            std::filesystem::path connectFile;
            std::filesystem::path queriesFile;
            std::filesystem::path outputFile;
        };

        App(CLI::arg_count, CLI::args);
        ~App() = default;

        int run();

    protected:
        enum class State {
            cli_help = 1,
            cli_error,
            loading_error,
            writing_error,
        };

        inline void handleCli();
        inline void loadInputs();
        inline void resolveQueries();
        inline void resolveQueriesBoth();
        inline void resolveQueriesSpecific();
        inline void writeOutput();

    private:
        const CLI::arg_count argc_;
        const CLI::args argv_;
        CLI::clipper cli_;
        CliOptions options_;
        FileHandler fileHandler_;
        Map map_;
        PolymorphicPathList foundPaths_;
        std::vector<UnifiedQuery> queries_;
        State state_ {};
    };

}  // namespace citymap