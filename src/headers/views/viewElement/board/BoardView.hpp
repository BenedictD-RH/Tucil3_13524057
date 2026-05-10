#pragma once
#include "../View3D.hpp"
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
        BlockView block;
        vector<vector<TileView*>> tiles;
        vector<NumberTileView*> numberTiles;
        string solutionPath;
        float animationSpeed;
    public:
        BoardView(Board& board);
        void setSolutionPath(const string path);
        void startPlayback();
        void pausePlayback();
        float getAnimationSpeed() const;
        void setAnimationSpeed(const float speed);
        void slideBlock(string path);
        void render() override;
};