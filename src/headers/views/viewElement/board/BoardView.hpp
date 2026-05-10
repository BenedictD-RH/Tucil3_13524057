#pragma once
#include "../View3D.hpp"
#include "../../animation/camera/View3DCamera.hpp"
#include "TileView.hpp"
#include "../../../game_modules/Board.hpp"

class BlockView : public View3D {
    private:
        Block& block;
    public:
        BlockView(Block& block);
};

class BoardView : public View3D {
    private:
        Board& board;
        View3DCamera* topViewCam;
        BlockView* block;
        vector<vector<TileView*>> tiles;
        vector<NumberTileView*> numberTiles;
        string solutionPath;
        string animationProgress;
        float animationSpeed;
        bool animationReverse;
    public:
        BoardView(Board& board, View3DCamera* topViewCam);
        Board& getBoardState() const;
        void reloadBoard();
        void loadBoardFromFile(string filePath);
        Vector2 getBoardSize() const;
        void setBoardSize(const int row, const int col);
        void setSolutionPath(const string path);
        void startPlayback();
        void pausePlayback();
        void reversePlayback();
        void resetPlaybackSettings();
        bool isAnimationReversed() const;
        float getAnimationSpeed() const;
        void setAnimationSpeed(const float speed);
        void slideBlock(string path);
        void render() override;
};