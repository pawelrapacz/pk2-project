#include "FileHandler.h"
#include <fstream>
#include <vector>

using namespace citymap;

FileHandler::FileHandler(const App::CliOptions& opt)
    : coords(opt.coordinates), connect(opt.connectionsTable), quries(opt.traces), output(opt.outputFile)
{}

void FileHandler::loadCoordinates(CityGraph& graph) {
    std::ifstream file(coords);
    int id, x, y;
    std::string name;

    while(!file.eof()) {
        file >> id >> name >> x >> y;
        graph.insertVertex(name, {x, y});
    }
    file.close();
}

void FileHandler::loadConnections(CityGraph& graph) {
    // if (graph.empty()) throw 1;
    // std::ifstream file(coords);
    // std::vector<std::vector<int>> matrix(graph.size(), std::vector<int>(graph.size()));
    // bool hasConnection;

    // for(std::size_t i = 0; i < graph.size(); i++) {
    //     for(std::size_t j = 0; j < graph.size(); j++) {
    //         file >> hasConnection;
    //         if (hasConnection) graph.addEdge(i, j);
    //     }
    // }
    // file.close();
}

// void FileHandler::loadQueries(const std::filesystem::path&) {
// }

// void FileHandler::writeOutput(const std::filesystem::path&) {
// }
