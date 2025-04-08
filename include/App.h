#pragma once

#include <string>
#include "clipper.hpp"

namespace citymap
{
    class App
    {
    public:
        struct CliOptions {
            bool help;
            std::string coordinates;
            std::string connectionsTable;
            std::string traces;
            std::string outputFile;
        };

        App(int, char**);
        ~App() = default;

        void run();

    protected:
        inline void handleCli();


    private:
        const int argc_;
        char** argv_;
        CLI::clipper cli_;
        CliOptions options_;
    };
} // namespace citymap