#include "App.h"

int main(CLI::arg_count argc, CLI::args argv) {
    citymap::App app(argc, argv);
    app.run();
}