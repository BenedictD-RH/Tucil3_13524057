#pragma once
#include "viewElement/View3D.hpp"
#include "viewElement/View2D.hpp"
#include "viewElement/Interactable.hpp"
#include "viewElement/Entry.hpp"
#include "viewElement/board/BoardView.hpp"
#include "viewElement/controls/SolverInput.hpp"
#include "animation/ViewAnimation.hpp"
#include "animation/camera/CameraManager.hpp"
#include "animation/camera/View3DCamera.hpp"
#include "animation/camera/CameraMovement.hpp"


class GUI {
    private:
        CameraManager camManager;
        BoardView* boardView;
        SolverInput boardInput;
    public:
        GUI();
        void loadBoard(Board& board);
        void update();
        void render();
};