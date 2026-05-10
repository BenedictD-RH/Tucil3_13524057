#include "../headers/views/GUI.hpp"


GUI::GUI() : camManager(CameraManager()), boardView(nullptr), playbackControl(nullptr) {
    camManager.addCamera("FREE_CAM", View3DCamera({0,25.0f,0.001f}, {0,0,0}, 45.0f));
}


void GUI::loadBoard(Board& board) {
    boardView = new BoardView(board);
}

void GUI::loadPlaybackControl() {
    playbackControl = new PlaybackControl(boardView);
}

void GUI::setBoardSolution(string path) {
    if (boardView != nullptr) {
        loadPlaybackControl();
        boardView->setSolutionPath(path);
    }
}

void GUI::update() {
    if (playbackControl != nullptr) playbackControl->interactionCheck();
}

void GUI::render() {
    BeginMode3D(camManager.getCurrentCamera()->mount());
    if (boardView != nullptr) boardView->render();
    
    DrawGrid(50, 1);

    EndMode3D();
    if (playbackControl != nullptr) playbackControl->render();
}

