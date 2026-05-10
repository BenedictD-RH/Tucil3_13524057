#pragma once
#include "BoardView.hpp"
#include "../Interactable.hpp"


class PlaybackControl : public View2D {
    private:
        BoardView* board;
        Interactable speedUpBtn;
        Interactable slowDownBtn;
        Interactable playBtn;
        Interactable pauseBtn;
        Interactable nextStep;
        Interactable previousStep;
    public:
        PlaybackControl(BoardView* board);
        void interactionCheck() override;
        void render() override;
};