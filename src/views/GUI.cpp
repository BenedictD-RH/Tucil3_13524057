#include "../headers/views/GUI.hpp"


GUI::GUI() : camManager(CameraManager()), boardView(nullptr), boardInput(nullptr) {
    camManager.addCamera("TOP_CAM", View3DCamera({-4,25.0f,0.001f}, {-4,0,0}, 45.0f));
}


void GUI::loadBoard(Board& board) {
    boardView = new BoardView(board, &camManager.getCamera("TOP_CAM"));
    boardInput.setBoardView(boardView);
}



void GUI::update() {
    boardInput.interactionCheck();
}

void GUI::render() {
    BeginMode3D(camManager.getCurrentCamera()->mount());
    if (boardView != nullptr) boardView->render();
    
    DrawGrid(50, 1);

    EndMode3D();
    boardInput.render();
}

