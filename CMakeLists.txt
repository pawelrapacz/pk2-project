cmake_minimum_required(VERSION 3.28.1)

project(MapaMiasta VERSION 2.0.1 LANGUAGES CXX)

set(SOURCE_FILES
    src/main.cpp
    src/App.cpp
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME} PRIVATE
    external/
    include/
)


# pedantic errors
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -pedantic-errors)
endif()



if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("-- Build type: Debug")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message("-- Build type: Release")
    target_link_options(${PROJECT_NAME} PRIVATE -static)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_FLAGS "-O3"
    )
endif()