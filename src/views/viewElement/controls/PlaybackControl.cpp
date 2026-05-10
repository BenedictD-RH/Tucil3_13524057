#include "../../../headers/views/viewElement/controls/PlaybackControl.hpp"
#include <sstream>

PlaybackControl::PlaybackControl(BoardView* board) : board(board), 
                                                     View2D({GetScreenWidth()*0.175f, GetScreenHeight()*0.875f},
                                                            {500, 100}, [](){}) {
    playBtn = Interactable({50,50}, true, false, "PLAY", [](){}, [this](){ 
        this->board->startPlayback(); 
        this->playBtn.setVisible(false);
        this->playBtn.setActive(false);
        this->pauseBtn.setVisible(true);
        this->pauseBtn.setActive(true);
    });
    playBtn.setRender([this](){
        DrawTriangle({playBtn.getX() + playBtn.getBoundingWidth()/2, playBtn.getY()},
                     {playBtn.getX() - playBtn.getBoundingWidth()/2, playBtn.getY() - playBtn.getBoundingHeight()/2},
                     {playBtn.getX() - playBtn.getBoundingWidth()/2, playBtn.getY() + playBtn.getBoundingHeight()/2},
                     playBtn.getRenderColor(WHITE));
    });
    playBtn.setPosition(getPos());
    
    pauseBtn = Interactable({50,50}, false, false, "PAUSE", [](){}, [this](){ 
        this->board->pausePlayback(); 
        this->pauseBtn.setVisible(false);
        this->pauseBtn.setActive(false);
        this->playBtn.setVisible(true);
        this->playBtn.setActive(true);
    });
    pauseBtn.setVisible(false);
    pauseBtn.setRender([this](){
        DrawRectangle(pauseBtn.getX() - pauseBtn.getBoundingWidth()*0.4, pauseBtn.getY() - pauseBtn.getBoundingHeight()*0.45,
                      pauseBtn.getBoundingWidth()*0.3, pauseBtn.getBoundingHeight()*0.9, pauseBtn.getRenderColor(WHITE));
        DrawRectangle(pauseBtn.getX() + pauseBtn.getBoundingWidth()*0.1, pauseBtn.getY() - pauseBtn.getBoundingHeight()*0.45,
                      pauseBtn.getBoundingWidth()*0.3, pauseBtn.getBoundingHeight()*0.9, pauseBtn.getRenderColor(WHITE));
    });
    pauseBtn.setPosition(getPos());

    speedUpBtn = Interactable({50,50}, true, false, "SPEED_UP", [](){}, [this](){
        if (this->board->getAnimationSpeed() < 8) {
            this->board->setAnimationSpeed(this->board->getAnimationSpeed()*2);
        }
    });
    speedUpBtn.setRender([this](){
        DrawTriangle({speedUpBtn.getX(), speedUpBtn.getY()},
                     {speedUpBtn.getX() - speedUpBtn.getBoundingWidth()/2, speedUpBtn.getY() - speedUpBtn.getBoundingHeight()/2},
                     {speedUpBtn.getX() - speedUpBtn.getBoundingWidth()/2, speedUpBtn.getY() + speedUpBtn.getBoundingHeight()/2},
                     speedUpBtn.getRenderColor(WHITE));
        DrawTriangle({speedUpBtn.getX() + speedUpBtn.getBoundingWidth()/2, speedUpBtn.getY()},
                     {speedUpBtn.getX(), speedUpBtn.getY() - speedUpBtn.getBoundingHeight()/2},
                     {speedUpBtn.getX(), speedUpBtn.getY() + speedUpBtn.getBoundingHeight()/2},
                     speedUpBtn.getRenderColor(WHITE));
    });
    speedUpBtn.setPosition(getPos() + (Vector2){100, 0});

    slowDownBtn = Interactable({50,50}, true, false, "SLOW_DOWN", [](){}, [this](){
        if (this->board->getAnimationSpeed() > 0.125) {
            this->board->setAnimationSpeed(this->board->getAnimationSpeed()*0.5);
        }
    });
    slowDownBtn.setRender([this](){
        DrawTriangle({slowDownBtn.getX(), slowDownBtn.getY()},
                     {slowDownBtn.getX() + slowDownBtn.getBoundingWidth()/2, slowDownBtn.getY() + slowDownBtn.getBoundingHeight()/2},
                     {slowDownBtn.getX() + slowDownBtn.getBoundingWidth()/2, slowDownBtn.getY() - slowDownBtn.getBoundingHeight()/2},
                     slowDownBtn.getRenderColor(WHITE));
        DrawTriangle({slowDownBtn.getX() - slowDownBtn.getBoundingWidth()/2, slowDownBtn.getY()},
                     {slowDownBtn.getX(), slowDownBtn.getY() + slowDownBtn.getBoundingHeight()/2},
                     {slowDownBtn.getX(), slowDownBtn.getY() - slowDownBtn.getBoundingHeight()/2},
                     slowDownBtn.getRenderColor(WHITE));
    });
    slowDownBtn.setPosition(getPos() + (Vector2){-100, 0});

    reverseBtn = Interactable({60,50}, true, false, "SLOW_DOWN", [](){}, [this](){
        this->board->reversePlayback();
    });
    reverseBtn.setRender([this](){
        DrawTriangle({reverseBtn.getX(), reverseBtn.getY()},
                     {reverseBtn.getX() + reverseBtn.getBoundingWidth()*0.4f, reverseBtn.getY() + reverseBtn.getBoundingHeight()/2},
                     {reverseBtn.getX() + reverseBtn.getBoundingWidth()*0.4f, reverseBtn.getY() - reverseBtn.getBoundingHeight()/2},
                     reverseBtn.getRenderColor(WHITE));
        DrawTriangle({reverseBtn.getX() - reverseBtn.getBoundingWidth()*0.4f, reverseBtn.getY()},
                     {reverseBtn.getX(), reverseBtn.getY() + reverseBtn.getBoundingHeight()/2},
                     {reverseBtn.getX(), reverseBtn.getY() - reverseBtn.getBoundingHeight()/2},
                     reverseBtn.getRenderColor(WHITE));
        DrawRectangle(reverseBtn.getX() - reverseBtn.getBoundingWidth()*0.5f, reverseBtn.getY() - reverseBtn.getBoundingHeight()*0.45f,
                      reverseBtn.getBoundingWidth()*0.1f, reverseBtn.getBoundingHeight()*0.9f, reverseBtn.getRenderColor(WHITE));
    });
    reverseBtn.setPosition(getPos() + (Vector2){-200, 0});

    playbackDetails = View2D(getPos() + (Vector2){0, 75}, {500, 50}, [this](){
        string details = "";
        if (this->board->getAnimationSpeed() != 1) {
            std::stringstream ss;
            ss << this->board->getAnimationSpeed();
            details += "x" + ss.str() + " Speed\n";
        }
        if (this->board->isAnimationReversed()) {
            details += "(Reversed)\n";
        }
        drawTextLinesWrapped(getFont("FuturaSmall"), details, playbackDetails.getPos(), 25, 0, WHITE, playbackDetails.getBoundingDim());
    });
}

void PlaybackControl::interactionCheck() {
    playBtn.interactionCheck();
    pauseBtn.interactionCheck();
    speedUpBtn.interactionCheck();
    slowDownBtn.interactionCheck();
    reverseBtn.interactionCheck();
}

void PlaybackControl::render() {
    playBtn.render();
    pauseBtn.render();
    speedUpBtn.render();
    slowDownBtn.render();
    reverseBtn.render();
    playbackDetails.render();
}