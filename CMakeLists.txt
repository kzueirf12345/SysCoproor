cmake_minimum_required(VERSION 3.21)

project(SysCoproor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES FOLDER "bin")

add_subdirectory(source/Common)
add_subdirectory(source/Vector)
add_subdirectory(source/Plot)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    source/main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE
        sfml-graphics

        Common
        Vector
        Plot
)
