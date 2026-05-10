#pragma once
#include "../board/BoardView.hpp"
#include "../Interactable.hpp"


class PlaybackControl : public View2D {
    private:
        BoardView* board;
        Interactable speedUpBtn;
        Interactable slowDownBtn;
        Interactable playBtn;
        Interactable pauseBtn;
        Interactable reverseBtn;
        View2D playbackDetails;
    public:
        PlaybackControl(BoardView* board);
        void interactionCheck() override;
        void render() override;
};