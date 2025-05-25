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

    c.add_option<std::string>("--type", "-t")
        .set("type", o.type, "Both")
        .doc("Sets the output type for queries, defaults to both.")
        .match("Pedestrian", "Car", "Both");
    // clang-format on
}

App::App(CLI::arg_count argc, CLI::args argv)
    : argc_(argc), argv_(argv) {
    initCliOptions(cli_, options_);
}

#define EXIT_ON_FAIL                                        \
    if (state_ != State {}) return static_cast<int>(state_)

int App::run() {
    handleCli();
    EXIT_ON_FAIL;
    loadInputs();
    EXIT_ON_FAIL;
    resolveQueries();
    writeOutput();
    EXIT_ON_FAIL;
    return 0;  // exit success
}

inline void App::loadInputs() {
    fileHandler_.loadCoordinates(options_.coordsFile, map_);
    fileHandler_.loadConnections(options_.connectFile, map_);

    if (options_.type == "Pedestrian")
        fileHandler_.loadQueries(options_.queriesFile, queries_, PathType::Pedestrian, map_);
    else
        fileHandler_.loadQueries(options_.queriesFile, queries_, PathType::Car, map_);

    if (fileHandler_.fail()) {
        std::cerr << fileHandler_.error() << '\n';
        state_ = State::loading_error;
    }
}

inline void App::resolveQueries() {
    if (options_.type == "Both")
        resolveQueriesBoth();
    else
        resolveQueriesSpecific();
}

inline void App::resolveQueriesBoth() {
    for (auto& query : queries_) {
        foundPaths_.emplace_back(map_.findPath(query));
        query.toggleType();
        foundPaths_.emplace_back(map_.findPath(query));
    }
}

inline void App::resolveQueriesSpecific() {
    for (auto& query : queries_)
        foundPaths_.emplace_back(map_.findPath(query));
}

inline void App::writeOutput() {
    fileHandler_.writeOutput(options_.outputFile, foundPaths_, map_);
    if (fileHandler_.fail()) {
        std::cerr << fileHandler_.error() << '\n';
        state_ = State::writing_error;
    }
}

inline void App::handleCli() {
    if (!cli_.parse(argc_, argv_)) {
        state_ = State::cli_error;
        for (auto& i : cli_.wrong())
            std::cerr << i << '\n';
    }

    if (options_.help or cli_.no_args()) {
        std::cout << cli_.make_help();
        state_ = State::cli_help;
    }
}