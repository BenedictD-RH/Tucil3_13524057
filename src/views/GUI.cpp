#include "../headers/views/GUI.hpp"


GUI::GUI() : camManager(CameraManager()) {
    camManager.addCamera("FREE_CAM", View3DCamera({10,7.5f,10}, {0,0,0}, 45.0f));
}

void GUI::update() {

}

void GUI::render() {
    BeginMode3D(camManager.getCurrentCamera()->mount());

    DrawGrid(10, 1);

    EndMode3D();
}

