#include "../../../headers/views/viewElement/board/BoardView.hpp"
#include "../../../headers/views/animation/ViewAnimation.hpp"

BlockView::BlockView(Block& block) : block(block), View3D({0,0,0}, LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f)), VIOLET) {}

BoardView::BoardView(Board& board) : View3D(), board(board), block(BlockView(*board.getBlockState())), animationSpeed(1), solutionPath(""){
    Vector3 originPos = {-(board.getCol() - 1)*0.5f, 0, -(board.getRow() - 1)*0.5f};
    for(int i = 0; i < board.getRow(); i++) {
        vector<TileView*> tileRow;
        for (int j = 0; j < board.getCol(); j++) {
            if (board.tileAt(j,i)->getType() == NUMBER_TILE) {
                NumberTile* num = static_cast<NumberTile*>(board.tileAt(j,i));
                NumberTileView* numTile = new NumberTileView(*num);
                numTile->movePosition({originPos.x + j*1.0f, 
                                       (GetModelBoundingBox(numTile->getModel()).max.y - GetModelBoundingBox(numTile->getModel()).min.y)/2,
                                       originPos.z + i*1.0f});
                tileRow.push_back(numTile);
                numberTiles.push_back(numTile);
            } else {
                TileView* tile = new TileView(*board.tileAt(j,i));
                tile->movePosition({originPos.x + j*1.0f, 
                                       (GetModelBoundingBox(tile->getModel()).max.y - GetModelBoundingBox(tile->getModel()).min.y)/2,
                                       originPos.z + i*1.0f});
                tileRow.push_back(tile);
            }
        }
        tiles.push_back(tileRow);
    }
    this->block.movePosition(tiles.at(board.getBlockState()->getY()).at(board.getBlockState()->getX())->getPos());
    this->block.movePositionDelta({0,(GetModelBoundingBox(this->block.getModel()).max.y - GetModelBoundingBox(this->block.getModel()).min.y)/2,0});
}

float BoardView::getAnimationSpeed() const {
    return animationSpeed;
}


void BoardView::setAnimationSpeed(const float speed) {
    animationSpeed = speed;
    for (auto pair : animations) {
        pair.second->setFPS(60/animationSpeed);
    }
}

void BoardView::slideBlock(string path) {
    if (path == "") return;
    Block* blockState = board.controlBlock(path.substr(0,1));
    TileView* destTile = tiles.at(board.getBlockState()->getY()).at(board.getBlockState()->getX());
    string newPath = path.substr(1);
    View3DAnimation* slide_anim = new View3DAnimation(block, 60/animationSpeed, true, [](){}, [this, newPath, blockState](){
        if (blockState->getLastNumberTileVisited() != nullptr) {
            for_each(numberTiles.begin(), numberTiles.end(), [blockState](NumberTileView* numTile){
                if (blockState->getLastNumberTileVisited()->getNumber() >= numTile->getNumTile()->getNumber()) {
                    numTile->setColor({0, 255, 127, 255});
                }
            });
        }
        slideBlock(newPath);
    });
    float slide_distance = abs(destTile->getPos().x - block.getPos().x) + abs(destTile->getPos().z - block.getPos().z);
    slide_anim->setMoveAnimation({destTile->getPos().x, block.getPos().y, destTile->getPos().z}, 0.1*slide_distance);
    slide_anim->start();
    addAnimation("SLIDE" + path, slide_anim);
}

void BoardView::setSolutionPath(const string path) {
    solutionPath = path;
}

void BoardView::startPlayback() {
    if (animations.empty()) {
        slideBlock(solutionPath);
    } else {
        for (auto pair : animations) {
            pair.second->start();
        }
        
    }
}

void BoardView::pausePlayback() {
    for (auto pair : animations) {
        pair.second->pause();
    }
}

void BoardView::render() {
    animationCheck();
    block.render();
    for(int i = 0; i < board.getRow(); i++) {
        for (int j = 0; j < board.getCol(); j++) {
            tiles.at(i).at(j)->render();
        }
    }
}