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

}

NumberTileView::NumberTileView(NumberTile& numTile) : TileView(numTile), numTile(numTile) {
    RenderTexture2D texture = LoadRenderTexture(80, 80);
    BeginTextureMode(texture);
    ClearBackground(RAYWHITE);
    drawTextLinesWrapped(GetFontDefault(), to_string(numTile.getNumber()), {40,40}, 36, 0, BLACK, {80,80});
    EndTextureMode();
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture.texture);
}

NumberTile* NumberTileView::getNumTile() { return &numTile;}