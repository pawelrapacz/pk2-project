cmake_minimum_required(VERSION 4.0.1)
project(MapaMiasta VERSION 1.0.0
                   DESCRIPTION "pk-project"
                   LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


add_subdirectory(external)

add_executable(${PROJECT_NAME}
    include/App.h
    include/graph_traits.h
    include/UndirectedGraph.h
    include/Point.h
    include/CityGraph.h
    include/metrics.h

    src/main.cpp
    src/App.cpp
    src/metrics.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE clipper)
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
    <cmath>
    <cstring>
)