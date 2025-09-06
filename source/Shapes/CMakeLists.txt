add_library(Shapes STATIC
    source/Circle.cpp
    source/Sphere.cpp
)

set_target_properties(Shapes PROPERTIES FOLDER "source")

target_include_directories(Shapes
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(Shapes
    PRIVATE 
        sfml-graphics
        Common
        Vector
)