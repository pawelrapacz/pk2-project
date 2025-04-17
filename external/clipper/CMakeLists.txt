add_library(clipper INTERFACE)
target_compile_features(clipper INTERFACE cxx_std_20)
target_include_directories(clipper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_precompile_headers(clipper INTERFACE [["clipper.hpp"]])