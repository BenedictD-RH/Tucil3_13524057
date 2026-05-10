#include "../headers/game_modules/Tile.hpp"
#include "../headers/game_modules/Block.hpp"


Tile::Tile(const int cost, const int x, const int y, TileType type) : cost(cost), x(x), y(y), type(type) {}

const int Tile::getCost() const { return cost; }
const int Tile::getX() const { return x; }
const int Tile::getY() const { return y; }
const Vector2 Tile::getRenderPos() const { return {50 + x*80, 50 + y*80};}
const TileType Tile::getType() const { return type; }
const string Tile::getSymbol() const { 
    switch(type) {
        case PASSABLE_TILE :
            return "*";
        case UNPASSABLE_TILE :
            return "X";
        case LAVA_TILE :
            return "L";
        case START_TILE :
            return "*";
        case GOAL_TILE :
            return "O";
        default :
            return "";
    }
}

void Tile::setType(TileType type) { this->type = type; }
void Tile::setCost(const int cost) { this->cost = cost; }
void Tile::onVisit(Block* block) {
    if (type ==LAVA_TILE)  {
        block->setGameState(GAME_OVER);
    }
}


UnpassableTile::UnpassableTile(const int x, const int y) : Tile(999, x, y, UNPASSABLE_TILE) {}

NumberTile::NumberTile(const int cost, const int x, const int y, const int num) : Tile(cost, x, y, NUMBER_TILE), number(num) {}

const int NumberTile::getNumber() const { return number; }

const string NumberTile::getSymbol() const { return to_string(number); }

void NumberTile::onVisit(Block* block) {
    if (block->getLastNumberTileVisited() == nullptr) {
        if (number != 0) block->setGameState(GAME_OVER);
        else {
            block->setLastNumberTileVisited(this);
        }
    } else if (block->getLastNumberTileVisited()->getNumber() == number - 1) {
        block->setLastNumberTileVisited(this);
    } else if (block->getLastNumberTileVisited()->getNumber() < number - 1){
        block->setGameState(GAME_OVER);
    }
}