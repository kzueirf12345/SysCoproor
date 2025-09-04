add_library(Vector STATIC
    source/Vector.cpp
)

set_target_properties(Vector PROPERTIES FOLDER "source")

target_include_directories(Vector
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(Vector
    PRIVATE 
        Common
)