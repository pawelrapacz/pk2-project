add_library(graphs INTERFACE
    include/graph_traits.h
    include/GraphBase.h
    include/DirectedGraph.h
    include/UndirectedGraph.h
)
target_compile_features(graphs INTERFACE cxx_std_23)
target_include_directories(graphs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)