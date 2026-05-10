#include "../../../headers/views/viewElement/board/PlaybackControl.hpp"


PlaybackControl::PlaybackControl(BoardView* board) : board(board) {
    setPosition({600, 700});
    playBtn = Interactable({50,50}, true, false, "PLAY", [](){}, [this](){ 
        cout<<"hey"<<endl;
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
                     getRenderColor(WHITE));
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
                      pauseBtn.getBoundingWidth()*0.3, pauseBtn.getBoundingHeight()*0.9, getRenderColor(WHITE));
        DrawRectangle(pauseBtn.getX() + pauseBtn.getBoundingWidth()*0.1, pauseBtn.getY() - pauseBtn.getBoundingHeight()*0.45,
                      pauseBtn.getBoundingWidth()*0.3, pauseBtn.getBoundingHeight()*0.9, getRenderColor(WHITE));
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
                     getRenderColor(WHITE));
        DrawTriangle({speedUpBtn.getX() + speedUpBtn.getBoundingWidth()/2, speedUpBtn.getY()},
                     {speedUpBtn.getX(), speedUpBtn.getY() - speedUpBtn.getBoundingHeight()/2},
                     {speedUpBtn.getX(), speedUpBtn.getY() + speedUpBtn.getBoundingHeight()/2},
                     getRenderColor(WHITE));
    });
    speedUpBtn.setPosition(getPos() + (Vector2){100, 0});

    slowDownBtn = Interactable({50,50}, true, false, "SLOW_DOWN", [](){}, [this](){
        if (this->board->getAnimationSpeed() > 0.125) {
            this->board->setAnimationSpeed(this->board->getAnimationSpeed()*0.5);
        }
    });
    slowDownBtn.setRender([this](){
        DrawTriangle({slowDownBtn.getX(), speedUpBtn.getY()},
                     {slowDownBtn.getX() + slowDownBtn.getBoundingWidth()/2, speedUpBtn.getY() + slowDownBtn.getBoundingHeight()/2},
                     {slowDownBtn.getX() + slowDownBtn.getBoundingWidth()/2, speedUpBtn.getY() - slowDownBtn.getBoundingHeight()/2},
                     getRenderColor(WHITE));
        DrawTriangle({slowDownBtn.getX() - slowDownBtn.getBoundingWidth()/2, speedUpBtn.getY()},
                     {slowDownBtn.getX(), speedUpBtn.getY() + slowDownBtn.getBoundingHeight()/2},
                     {slowDownBtn.getX(), speedUpBtn.getY() - slowDownBtn.getBoundingHeight()/2},
                     getRenderColor(WHITE));
    });
    slowDownBtn.setPosition(getPos() + (Vector2){-100, 0});
}

void PlaybackControl::interactionCheck() {
    playBtn.interactionCheck();
    pauseBtn.interactionCheck();
    speedUpBtn.interactionCheck();
    slowDownBtn.interactionCheck();
}

void PlaybackControl::render() {
    playBtn.render();
    pauseBtn.render();
    speedUpBtn.render();
    slowDownBtn.render();
}