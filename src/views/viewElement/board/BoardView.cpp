#include "../../../headers/views/viewElement/board/BoardView.hpp"
#include "../../../headers/views/animation/ViewAnimation.hpp"

BlockView::BlockView(Block& block) : block(block), View3D({0,0,0}, LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f)), VIOLET) {}

BoardView::BoardView(Board& board, View3DCamera* topViewCam) : View3D(), board(board), block(nullptr), 
                                     animationProgress(""), animationSpeed(1), animationReverse(false), solutionPath(""),
                                     topViewCam(topViewCam){
    reloadBoard();
}

Board& BoardView::getBoardState() const { return board; }

void BoardView::reloadBoard() {
    if (block != nullptr) delete block;
    block = nullptr;
    for (vector<TileView*> tileRow : tiles) {
        for (TileView* tile : tileRow) {
            delete tile;
        }
    }
    tiles.clear();
    numberTiles.clear();
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
    if (board.getStartTile() != nullptr) {
        block = new BlockView(*board.getBlockState());
        block->movePosition(tiles.at(board.getBlockState()->getY()).at(board.getBlockState()->getX())->getPos());
        block->movePositionDelta({0,(GetModelBoundingBox(block->getModel()).max.y - GetModelBoundingBox(block->getModel()).min.y)/2,0});
    }
    
    
    float camDisplacement = max((float)max(board.getCol(), board.getRow()), 10.0f);
    topViewCam->movePosition({-camDisplacement*0.3f, camDisplacement*1.2f,0.001f});
    topViewCam->moveTargetPos({-camDisplacement*0.3f, 0, 0});
}

void BoardView::loadBoardFromFile(string filePath) {
    if (board.loadBoard(filePath)) {
        reloadBoard();
        reloadBoard();
    } else {
        cout<<"File Invalid!"<<endl;
    }
}

Vector2 BoardView::getBoardSize() const {
    return {board.getCol(), board.getRow()};
}

void BoardView::setBoardSize(const int row, const int col) {
    board.setBoardDim(row, col);
    board.printBoardTiles();
    reloadBoard();
}

bool BoardView::isAnimationReversed() const {
    return animationReverse;
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

void BoardView::resetPlaybackSettings() {
    animationSpeed = 1;
    animationReverse = false;
    solutionPath = "";
    animationProgress = "";
    for (auto pair : animations) {
        pair.second->endAbrupt();
    }
    board.resetBlock();
    reloadBoard();
}

void BoardView::slideBlock(string path) {
    if (!animationReverse && path == "") return;
    if (animationReverse && animationProgress == "") return;
    if (!animationReverse) {
        animationProgress += path.substr(0,1);
    } else {
        animationProgress = animationProgress.substr(0, animationProgress.length() - 1);
    }
    board.resetBlock();
    Block* blockState = board.controlBlock(animationProgress);
    TileView* destTile = tiles.at(board.getBlockState()->getY()).at(board.getBlockState()->getX());
    string newPath = path.substr(1);
    View3DAnimation* slide_anim = new View3DAnimation(*block, 60/animationSpeed, true, [](){}, [this, newPath, blockState](){
        for_each(numberTiles.begin(), numberTiles.end(), [blockState](NumberTileView* numTile){
            if (blockState->getLastNumberTileVisited() == nullptr) {
                numTile->setColor({162, 210, 223, 255});
            }
            else if (blockState->getLastNumberTileVisited()->getNumber() >= numTile->getNumTile()->getNumber()) {
                numTile->setColor({0, 255, 127, 255});
            } else {
                numTile->setColor({162, 210, 223, 255});
            }
        });
        slideBlock(newPath);
    });
    float slide_distance = abs(destTile->getPos().x - block->getPos().x) + abs(destTile->getPos().z - block->getPos().z);
    slide_anim->setMoveAnimation({destTile->getPos().x, block->getPos().y, destTile->getPos().z}, 0.1*slide_distance);
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

void BoardView::reversePlayback() {
    bool paused = false;
    for (auto pair : animations) {
        paused = !pair.second->isPlaying();
        pair.second->endAbrupt();
    }
    animationReverse = !animationReverse;
    if (animationReverse) {
        slideBlock(animationProgress);
    } else {
        slideBlock(solutionPath.substr(animationProgress.length()));
    }
    if (paused) pausePlayback();
}

void BoardView::render() {
    animationCheck();
    if (block != nullptr) block->render();
    for(int i = 0; i < board.getRow(); i++) {
        for (int j = 0; j < board.getCol(); j++) {
            tiles.at(i).at(j)->render();
        }
    }
}