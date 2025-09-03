add_library(Plot STATIC)

target_sources(Plot
    PRIVATE
        source/Plot.cpp
)

target_include_directories(Plot
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        Common
        Vector
)