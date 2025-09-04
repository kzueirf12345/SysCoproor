add_library(Common STATIC
    source/ErrorHandle.cpp
)

set_target_properties(Common PROPERTIES FOLDER "source")

target_include_directories(Common
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)