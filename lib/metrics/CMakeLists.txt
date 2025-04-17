add_library(metrics STATIC
    include/metrics.h
    src/metrics.cpp
)
target_include_directories(metrics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_precompile_headers(metrics PUBLIC <cmath>)