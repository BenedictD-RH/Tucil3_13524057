#pragma once
#include <vector>
#include <set>
#include "Tile.hpp"
using namespace std;


enum MoveDirection {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE,
};

enum GameState {
    ONGOING,
    GAME_OVER,
    GAME_WIN
};

class Board;

class Block {
    private :
        int x;
        int y;
        MoveDirection lastMoveDir;
        int totalCost;
        NumberTile* lastNumberTileVisited;
        GameState gameState;
        Board* board;
    public :
        Block(Board* board);
        const int getX() const;
        const int getY() const;
        const MoveDirection getLastMoveDirection() const;
        const int getTotalCost() const;
        const bool isGameOver() const;
        const bool isGameWin() const;
        const bool isOngoing() const;
        const bool isAt(const Tile& tile) const;
        Tile* getCurrentTile() const;
        NumberTile* getLastNumberTileVisited() const;
        const Tile* getTileInFront() const;
        void moveBlockTo(const int x, const int y);
        void moveBlockBy(const int dx, const int dy);
        void slideBlock();
        void setCost(const int cost);
        void setLastMoveDir(MoveDirection moveDir);
        void setLastNumberTileVisited(NumberTile* numTile);
        void setGameState(GameState gs);
};