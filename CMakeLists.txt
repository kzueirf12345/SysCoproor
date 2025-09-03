cmake_minimum_required(VERSION 3.21)

project(SysCoproor)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # to generate compile_commands.json

include_directories(source)

add_subdirectory(source/Common)
add_subdirectory(source/Vector)
add_subdirectory(source/Plot)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    source/main.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/source
)

target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE
        sfml-graphics

        Common
        Vector
        Plot
)
