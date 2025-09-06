add_library(Plot STATIC
    source/Plot.cpp
)

set_target_properties(Plot PROPERTIES FOLDER "source")

target_include_directories(Plot
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(Plot
    PRIVATE 
        Common
)