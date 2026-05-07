#pragma once
#include "Tile.hpp"
#include "Block.hpp"


class Board {
    private:
        Block* block;
        vector<vector<Tile*>> tiles;
        int row;
        int col;
        Tile* startTile;
        Tile* goalTile;
        vector<NumberTile*> numberTiles;
    public:
        Board(const int row, const int col);
        Tile* tileAt(const int x, const int y) const;
        Tile* getStartTile() const;
        Tile* getGoalTile() const;
        Block* getBlockState() const;
        NumberTile* getFinalNumberTile() const;
        const bool isOutOfBounds(const int x, const int y) const;
        void loadBoard(const string filename);
        void resetBlock();
        Block* controlBlock(const string path);
        void printBoardTiles() const;
        void printBoardCosts() const;
};