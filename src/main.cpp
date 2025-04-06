#include <iostream>
#include "clipper.hpp"

int main(int argc, char** argv) {
    bool help;
    std::string coordinates;
    std::string connectionsTable;
    std::string traces;
    std::string outputFile;


    CLI::clipper cli;
    cli.name("MapaMiasta").author("Paweł Rapacz");

    cli.help_flag("--help", "-h")
        .set(help);

    cli.add_option<std::string>("-coor")
        .set("file", coordinates)
        .doc("Input with coordinates")
        .req();

    cli.add_option<std::string>("-tab")
        .set("file", connectionsTable)
        .doc("Input with connections table")
        .req();

    cli.add_option<std::string>("-q")
        .set("file", traces)
        .doc("Input with traces")
        .req();

    cli.add_option<std::string>("-out")
        .set("file", outputFile)
        .doc("Output file")
        .req();


    if (!cli.parse(argc, argv)) {
        for (auto& i: cli.wrong)
            std::cout << i << "\n";
        return 1;
    }

    if (help)
        std::cout << cli.make_help();

    // do stuff

    return 0;
}