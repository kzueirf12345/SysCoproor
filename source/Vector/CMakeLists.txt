add_library(Vector STATIC)

target_sources(Vector
    PRIVATE
        source/Vector.cpp
)

target_include_directories(Vector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)