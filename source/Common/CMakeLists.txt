add_library(Common STATIC)

target_sources(Common
    PRIVATE
        source/ErrorHandle.cpp
)

target_include_directories(Common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)