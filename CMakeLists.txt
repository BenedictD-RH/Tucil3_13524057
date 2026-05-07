cmake_minimum_required(VERSION 3.11)
project(IceSliderSolver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/game_modules/Board.cpp
                               src/game_modules/Block.cpp
                               src/game_modules/Tile.cpp
                               src/pathfinding/Graph.cpp)

target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PUBLIC include)