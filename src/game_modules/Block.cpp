#include "../headers/game_modules/Block.hpp"
#include "../headers/game_modules/Board.hpp"
#include "math.h"


Block::Block(Board* board) : x(board->getStartTile()->getX()), y(board->getStartTile()->getY()), 
                             lastMoveDir(NONE), totalCost(0), board(board), gameState(ONGOING),
                             lastNumberTileVisited(nullptr) {}

const int Block::getX() const { return x; }
const int Block::getY() const { return y; }
const int Block::getTotalCost() const { return totalCost; }
const bool Block::isGameOver() const { return gameState == GAME_OVER; }
const bool Block::isGameWin() const { return gameState == GAME_WIN; }
const bool Block::isOngoing() const { return gameState == ONGOING; }
const MoveDirection Block::getLastMoveDirection() const { return lastMoveDir; }
NumberTile* Block::getLastNumberTileVisited() const { return lastNumberTileVisited; }
const bool Block::isAt(const Tile& tile) const {
    return x == tile.getX() && y == tile.getY();
}
Tile* Block::getCurrentTile() const {
    return board->tileAt(x,y);
}
const Tile* Block::getTileInFront() const {
    if (lastMoveDir == UP) return board->tileAt(x, y - 1);
    else if (lastMoveDir == LEFT) return board->tileAt(x - 1, y);
    else if (lastMoveDir == RIGHT) return board->tileAt(x + 1, y);
    else if (lastMoveDir == DOWN) return board->tileAt(x, y + 1);
    return board->tileAt(x,y);
}

void Block::moveBlockTo(const int x, const int y) { 
    this->x = x;
    this->y = y;
}   

void Block::moveBlockBy(const int dx, const int dy) {
    if (board->isOutOfBounds(x + dx, y + dy)) {
        gameState = GAME_OVER;
        return;
    }
    x += dx;
    y += dy;
}

void Block::slideBlock() {
    if (lastMoveDir == NONE) return;
    else {
        if (getTileInFront() != nullptr) {
            if (getTileInFront()->getType() == UNPASSABLE_TILE) {
                lastMoveDir = NONE;
                if (board->tileAt(x,y) == board->getGoalTile() && board->getFinalNumberTile() == lastNumberTileVisited) {
                    setGameState(GAME_WIN);
                }
            }
        } 
        if (lastMoveDir != NONE) {
            if (lastMoveDir == UP) moveBlockBy(0,-1);
            else if (lastMoveDir == LEFT) moveBlockBy(-1,0);
            else if (lastMoveDir == RIGHT) moveBlockBy(1,0);
            else if (lastMoveDir == DOWN) moveBlockBy(0,1);
            board->tileAt(x, y)->onVisit(this);
            totalCost += board->tileAt(x,y)->getCost();
        }
    }
}

void Block::setCost(const int cost) {
    totalCost = cost;
}

void Block::setLastMoveDir(MoveDirection moveDir) {
    lastMoveDir = moveDir;
}

void Block::setLastNumberTileVisited(NumberTile* numTile) {
    lastNumberTileVisited = numTile;
}

void Block::setGameState(GameState gs) {
    gameState = gs;
}