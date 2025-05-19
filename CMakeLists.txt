cmake_minimum_required(VERSION 4.0.1)
project(citymap VERSION 1.0.0
                   DESCRIPTION "pk-project"
                   LANGUAGES CXX)

set(PROJECT_AUTHOR "Paweł Rapacz")
string(TIMESTAMP PROJECT_PUBLICATION_YEAR "%Y")

configure_file(config.h.in config.h @ONLY)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


add_subdirectory(external/clipper)
add_subdirectory(lib/graphs)
add_subdirectory(lib/metrics)

add_executable(${PROJECT_NAME}
    src/main.cpp

    src/App/App.cpp
    src/App/App.h

    src/FileHandler/FileHandler.cpp
    src/FileHandler/FileHandler.h

    src/CityGraph/Point.h
    src/CityGraph/CityGraph.h

    src/Path/Path.h
    src/Path/Path.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}/
    src/
    src/App/
    src/Path/
    src/FileHandler/
    src/CityGraph/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    clipper
    graphs
    metrics
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror --pedantic-errors)

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <type_traits>
    <memory>
    <vector>
    <unordered_map>
    <filesystem>
    <algorithm>
    <string>
    <string_view>
    <iostream>
    <cstring>
)