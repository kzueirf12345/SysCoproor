cmake_minimum_required(VERSION 3.21)

project(SysCoproor)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # to generate compile_commands.json

add_executable(${CMAKE_PROJECT_NAME})

# add_subdirectory(source/third_party)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        
    source/main.cpp
)

# target_link_libraries(gas
#     PRIVATE
# )