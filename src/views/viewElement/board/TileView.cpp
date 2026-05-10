#include "../../../headers/views/viewElement/board/TileView.hpp"

View3D getTileModel(TileType type) {
    switch(type) {   
        case LAVA_TILE:
            return View3D({0,0,0}, LoadModelFromMesh(GenMeshCube(1.0f, 0.3f, 1.0f)), {247, 104, 6, 255});
        case UNPASSABLE_TILE:
            return View3D({0,0,0}, LoadModelFromMesh(GenMeshCube(1.0f, 0.75f, 1.0f)), GRAY);
        case GOAL_TILE:
            return View3D({0,0,0}, LoadModelFromMesh(GenMeshCube(1.0f, 0.01f, 1.0f)), {180, 196, 36, 255});
        default:
            return View3D({0,0,0}, LoadModelFromMesh(GenMeshCube(1.0f, 0.01f, 1.0f)), {162, 210, 223, 255});
    }
}


TileView::TileView(Tile& tile) : tile(tile), View3D(getTileModel(tile.getType())) {
    if (tile.getType() != NUMBER_TILE && tile.getType() != UNPASSABLE_TILE && tile.getType() != LAVA_TILE) {
        RenderTexture2D texture = LoadRenderTexture(40, 40);
        BeginTextureMode(texture);
        ClearBackground(RAYWHITE);
        drawTextLinesWrapped(GetFontDefault(), to_string(tile.getCost()), {35,35}, 10, 0, BLACK, {35,35});
        EndTextureMode();
        SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture.texture);
    }
}

NumberTileView::NumberTileView(NumberTile& numTile) : TileView(numTile), numTile(numTile) {
    RenderTexture2D texture = LoadRenderTexture(80, 80);
    BeginTextureMode(texture);
    ClearBackground(LIGHTGRAY);
    drawTextLinesWrapped(GetFontDefault(), to_string(numTile.getNumber()), {40,40}, 36, 0, BLACK, {80,80});
    drawTextLinesWrapped(GetFontDefault(), to_string(numTile.getCost()), {70,70}, 20, 0, BLACK, {80,80});
    EndTextureMode();
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture.texture);
}

NumberTile* NumberTileView::getNumTile() { return &numTile;}