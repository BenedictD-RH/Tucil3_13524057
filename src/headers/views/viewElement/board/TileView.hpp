#pragma once
#include "../View3D.hpp"
#include "../View2D.hpp"
#include "../../../game_modules/Tile.hpp"

class TileView : public View3D {
    private:
        Tile& tile;
    public:
        TileView(Tile& tile);
};

class NumberTileView : public TileView {
    private:
        NumberTile& numTile;
    public:
        NumberTileView(NumberTile& numTile);
        NumberTile* getNumTile();
};