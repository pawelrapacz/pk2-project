#pragma once

#include <filesystem>
#include "clipper.hpp"

namespace citymap
{
    class App
    {
    public:
        struct CliOptions {
            bool help;
            std::filesystem::path coordinates;
            std::filesystem::path connectionsTable;
            std::filesystem::path traces;
            std::filesystem::path outputFile;
        };

        App(CLI::arg_count, CLI::args);
        ~App() = default;

        void run();

    private:
        inline void handleCli();

    private:
        const CLI::arg_count argc_;
        const CLI::args argv_;
        CLI::clipper cli_;
        CliOptions options_;
    };
} // namespace citymap