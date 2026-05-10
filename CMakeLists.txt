cmake_minimum_required(VERSION 3.11)
project(IceSliderSolver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/game_modules/Board.cpp
                               src/game_modules/Block.cpp
                               src/game_modules/Tile.cpp
                               src/pathfinding/Algorithm.cpp
                               src/pathfinding/Heuristic.cpp
                               src/pathfinding/Graph.cpp
                               src/pathfinding/UCS.cpp
                               src/pathfinding/GBFS.cpp
                               src/pathfinding/AStar.cpp
                               src/views/GUI.cpp
                               src/views/viewElement/View2D.cpp
                               src/views/viewElement/View3D.cpp
                               src/views/viewElement/Interactable.cpp
                               src/views/viewElement/Entry.cpp
                               src/views/viewElement/board/BoardView.cpp
                               src/views/viewElement/board/TileView.cpp
                               src/views/viewElement/controls/PlaybackControl.cpp
                               src/views/viewElement/controls/SolverInput.cpp
                               src/views/animation/ViewAnimation.cpp
                               src/views/animation/camera/CameraManager.cpp
                               src/views/animation/camera/CameraMovement.cpp
                               src/views/animation/camera/View3DCamera.cpp)

target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PUBLIC include)