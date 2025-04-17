#include "App.h"
#include <iostream>

using namespace citymap;


citymap::App::App(int argc, char ** argv)
    : argc_(argc), argv_(argv) {}


void App::run()
{
    handleCli();
}


static inline void initCliOptions(CLI::clipper &c,  App::CliOptions &o) {
    c.name("MapaMiasta").author("Paweł Rapacz");

    c.help_flag("--help", "-h")
        .set(o.help);

    c.add_option<std::string>("-coor")
        .set("file", o.coordinates)
        .doc("Input with coordinates")
        .req();

    c.add_option<std::string>("-tab")
        .set("file", o.connectionsTable)
        .doc("Input with connections table")
        .req();

    c.add_option<std::string>("-q")
        .set("file", o.traces)
        .doc("Input with traces")
        .req();

    c.add_option<std::string>("-out")
        .set("file", o.outputFile)
        .doc("Output file")
        .req();
}


inline void App::handleCli()
{
    initCliOptions(cli_, options_);

    if (!cli_.parse(argc_, argv_)) {
        for (auto &i : cli_.wrong())
            std::cout << i << '\n';

        return;
    }

    if (options_.help) {
        std::cout << cli_.make_help();
    }
}
