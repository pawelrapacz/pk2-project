#include "App.h"

#include <iostream>

#include "FileHandler.h"
#include "config.h"

using namespace citymap;

static inline void initCliOptions(CLI::clipper& c, App::CliOptions& o) {
    // clang-format off
    c.name(PROJECT_NAME).author(PROJECT_AUTHOR);
    c.version(PROJECT_VERSION);
    c.description("Determines the shortest path between two points in the city.");

    c.help_flag("--help", "-h").set(o.help);

    c.add_option<std::filesystem::path>("-coor")
        .set("file", o.coordsFile)
        .doc("Input with coordinates")
        .req();

    c.add_option<std::filesystem::path>("-tab")
        .set("file", o.connectFile)
        .doc("Input with connections table")
        .req();

    c.add_option<std::filesystem::path>("-q")
        .set("file", o.queriesFile)
        .doc("Input with path queries")
        .req();

    c.add_option<std::filesystem::path>("-out")
        .set("file", o.outputFile)
        .doc("Output file")
        .req();
    // clang-format on
}

citymap::App::App(CLI::arg_count argc, CLI::args argv)
    : argc_(argc), argv_(argv) {
    initCliOptions(cli_, options_);
}

void App::run() {
    handleCli();
    loadInputs();
}

void App::loadInputs() {
    FileHandler fh;
    fh.loadCoordinates(options_.coordsFile, map_);
    fh.loadConnections(options_.connectFile, map_);
    // fh.loadQueries(options_.queriesFile);
}

inline void App::handleCli() {
    if (!cli_.parse(argc_, argv_)) {
        for (auto& i : cli_.wrong())
            std::cout << i << '\n';
    }

    if (options_.help or cli_.no_args()) {
        std::cout << cli_.make_help();
    }
}