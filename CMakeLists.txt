cmake_minimum_required(VERSION 3.1)	 

project(pacman)

include_directories(headers)
include_directories(levels)
include_directories(cpp)

FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/pictures"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB cpp/factory.cpp cpp/characters.cpp cpp/observe.cpp cpp/game.cpp)

add_library(Game STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main Game sfml-graphics sfml-window sfml-system)
