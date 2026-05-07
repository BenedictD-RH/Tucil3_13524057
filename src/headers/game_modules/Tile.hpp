#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
using namespace std;

enum TileType {
    PASSABLE_TILE,
    UNPASSABLE_TILE,
    LAVA_TILE,
    NUMBER_TILE,
    START_TILE,
    GOAL_TILE
};

class Block;

class Tile {
    protected:
        int cost;
        int x;
        int y;
        TileType type;
    public:
        Tile(const int cost, const int x, const int y, TileType type);
        const int getCost() const;
        const int getX() const;
        const int getY() const;
        const Vector2 getRenderPos() const;
        const TileType getType() const;
        const bool isNextTo(const Tile& tile) const;
        const bool isNextTo(const int x, const int y) const;
        void setCost(const int cost);
        virtual void onVisit(Block* block);
        virtual const string getSymbol() const;
};

class UnpassableTile : public Tile {
    public:
        UnpassableTile(const int x, const int y);
};

class NumberTile : public Tile {
    private:
        int number;
    public:
        NumberTile(const int cost, const int x, const int y, const int num);
        const int getNumber() const;
        void onVisit(Block* block) override;
        const string getSymbol() const override;
};