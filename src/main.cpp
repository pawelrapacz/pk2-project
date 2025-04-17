#include <iostream>
#include "clipper.hpp"
#include "CityGraph.h"
#include "UndirectedGraph.h"

int main(/* int argc, char** argv */) {
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


    // if (!cli.parse(argc, argv)) {
    //     for (auto& i: cli.wrong)
    //         std::cout << i << "\n";
    //     return 1;
    // }

    if (help)
        std::cout << cli.make_help();

    // do stuff

    citymap::CityGraph graph;
    graph.insertVertex("Sklep", {0, 10});
    graph.insertVertex("Dom", {50, 11});
    graph.insertVertex("Szpital", {4, 2});
    graph.insertVertex("Szkoła", {4, 2});
    graph.addEdge("Szkoła", "Dom");
    graph.addEdge("Szkoła", "Szpital");
    graph.addEdge("Szpital", "Sklep");

    std::cout << "Szkoła:\n";
    for (auto& i : graph.adjacent("Szkoła"))
        std::cout << i << '\n';
    
    std::cout << "\nDom:\n";
    for (auto& i : graph.adjacent("Dom"))
        std::cout << i << '\n';

    graph.removeVertex("Dom");
    std::cout << "\n\nSzkoła:\n";
    for (auto& i : graph.adjacent("Szkoła"))
        std::cout << i << '\n';


    std::cout << "\n\n#############################\n############################\n\n";


    UndirectedGraph<std::string, citymap::Point> g2;
    g2.size();
    g2.insertVertex("Sklep", {10, 11});
    g2.insertVertex("Dom", {10, 15});
    g2.insertVertex("Szpital", {50, 11});
    g2.insertVertex("Szkoła", {10, 90});
    g2.addEdge("Szkoła", "Dom");
    g2.addEdge("Szkoła", "Szpital");
    g2.addEdge("Szpital", "Sklep");

    std::cout << "Szkoła:\n";
    for (auto& i : g2.adjacent("Szkoła"))
        std::cout << i << '\n';
    
    std::cout << "\nDom:\n";
    for (auto& i : g2.adjacent("Dom"))
        std::cout << i << '\n';

    g2.removeVertex("Dom");
    std::cout << "\n\nSzkoła:\n";
    for (auto& i : g2.adjacent("Szkoła"))
        std::cout << i << '\n';

    std::cout << g2["Szpital"].x;

    return 0;
}
