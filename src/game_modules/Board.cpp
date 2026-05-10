#include "../headers/game_modules/Board.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

Board::Board(const int row, const int col) : row(row), col(col), block(nullptr), startTile(nullptr), goalTile(nullptr) {
    for (int i = 0; i < row; i++) {
        vector<Tile*> tileRow;
        for (int j = 0; j < col; j++) {
            tileRow.push_back(new Tile(0, j, i, PASSABLE_TILE));
        }
        tiles.push_back(tileRow);
    }
}

const int Board::getRow() const { return row; }
const int Board::getCol() const { return col; }
Tile* Board::getStartTile() const { return startTile; }
Tile* Board::getGoalTile() const { return goalTile; }
Tile* Board::tileAt(const int x, const int y) const { 
    try {
        return tiles.at(y).at(x); 
    } catch (out_of_range e) {
        return nullptr;
    }
}
Block* Board::getBlockState() const { return block; }
const bool Board::isOutOfBounds(const int x, const int y) const {
    return x < 0 || x >= col || y < 0 || y >= row;
}


vector<NumberTile*> Board::getNumberTiles() const {
    return numberTiles;
}

NumberTile* Board::getNumberTile(const int num) const { 
    auto it = find_if(numberTiles.begin(), numberTiles.end(), [num](NumberTile* numtile) {
        return numtile->getNumber() == num;
    });
    if (it == numberTiles.end()) return nullptr;
    return *it;
}

NumberTile* Board::getNextNumberTile(NumberTile* numTile) const { 
    if (numTile == nullptr) {
        return getNumberTile(0);
    } else if (numTile == getFinalNumberTile()) {
        return nullptr;
    } else {
        return getNumberTile(numTile->getNumber() + 1);
    }
}

NumberTile* Board::getFinalNumberTile() const { 
    return getNumberTile(numberTiles.size() - 1);
}

void Board::resetBlock() {
    block->moveBlockTo(startTile->getX(), startTile->getY());
    block->setCost(0);
    block->setLastMoveDir(NONE);
    block->setLastNumberTileVisited(nullptr);
    block->setGameState(ONGOING);
}

Block* Board::controlBlock(const string path) {
    string slicedPath = path;
    while(!block->isGameOver() && slicedPath.length() > 0) {
        if (slicedPath.at(0) == 'U') block->setLastMoveDir(UP);
        else if (slicedPath.at(0) == 'R') block->setLastMoveDir(RIGHT);
        else if (slicedPath.at(0) == 'L') block->setLastMoveDir(LEFT);
        else if (slicedPath.at(0) == 'D') block->setLastMoveDir(DOWN);
        while(block->getLastMoveDirection() != NONE && !block->isGameOver()) {
            block->slideBlock();
        }
        slicedPath = slicedPath.substr(1);
    }
    return block;
}

void Board::loadBoard(const string filename) {
    ifstream file(filename);
    string line;
    Board newB(0,0);
    if (file.is_open()) {
        int k = 0;
        getline(file, line);
        string token;
        stringstream ss(line);
        while(getline(ss, token, ' ')) {
            if (token != "") {
                try {
                    if (k == 0) {
                        newB.row = stoi(token);
                    } else if (k == 1) {
                        newB.col = stoi(token);
                    }
                    k++;
                } catch (invalid_argument e) {
                    cout<<"Error: Invalid row/column amount"<<endl;
                    return;
                }
            }
        }
        if (k < 2) {
            cout<<"Error: Invalid row/column amount"<<endl;
            return;
        }

        int j = 0;
        while(!file.eof() && j < newB.row) {
            getline(file, line);
            if (newB.col != line.length()) {
                return;
            }
            vector<Tile*> tileRow;
            for (int i = 0; i < line.length(); i++) {
                Tile* tile;
                switch(line.at(i)) {
                    case 'X':
                        tile = new UnpassableTile(i, j);
                        break;
                    case '*':
                        tile = new Tile(0, i, j, PASSABLE_TILE);
                        break;
                    case 'L':
                        tile = new Tile(0, i, j, LAVA_TILE);
                        break;
                    case 'O':
                        tile = new Tile(0, i, j, GOAL_TILE);
                        newB.goalTile = tile;
                        break;
                    case 'Z':
                        tile = new Tile(0, i, j, START_TILE);
                        newB.startTile = tile;
                        break;
                    default:
                        if (line.at(i) >= '0' && line.at(i) <= '9') {
                            NumberTile* numtile = new NumberTile(0, i, j, line.at(i) - 48);
                            newB.numberTiles.push_back(numtile);
                            tile = numtile;
                        } else {
                            cout<<"Error: Invalid Symbol! : "<<line.at(i)<<endl;
                            return;
                        }
                }
                tileRow.push_back(tile);
            }
            newB.tiles.push_back(tileRow);
            j++;
        }
        if (j != newB.row) {
            cout<<"Error: Invalid row amount"<<endl;
            return;
        }
        j = 0;
        while(!file.eof() && j < newB.row) {
            getline(file, line);
            string token;
            stringstream ss(line);
            int i = 0;
            while(getline(ss, token, ' ')) {
                if (token != "") {
                    try {
                        int val = stoi(token);
                        if (val < 0) {
                            cout<<"Error: Invalid cost value"<<endl;
                            return;
                        }
                        newB.tiles[j][i]->setCost(val);
                        i++;
                    } catch (invalid_argument e) {
                        cout<<"Error: Invalid cost value"<<endl;
                        return;
                    }
                }
            }
            if (i != newB.col) {
                cout<<"Error: Invalid column amount :"<<i<<endl;
                return;
            }
            j++;
        }
        if (j != newB.row) {
            cout<<"Error: Invalid row amount"<<endl;
            return;
        }
    }
    sort(newB.numberTiles.begin(), newB.numberTiles.end(), [](const NumberTile* t1, const NumberTile* t2){
        return t1->getNumber() < t2->getNumber();
    });
    *this = newB;
    block = new Block(this);
}

void Board::printBoardTiles() const {
    cout<<"Row : "<<row<<endl;
    cout<<"Column : "<<col<<endl;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if (block != nullptr) {
                if (block->getX() == j && block->getY() == i) {
                    cout<<"Z";
                } else {
                    cout<<tiles[i][j]->getSymbol();
                }   
            } else {    
                cout<<tiles[i][j]->getSymbol();
            }
            if (j != col - 1) {
                cout<<" ";
            }
        }
        cout<<endl;
    }
}

void Board::printBoardCosts() const {
    cout<<"Row : "<<row<<endl;
    cout<<"Column : "<<col<<endl;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            cout<<tiles[i][j]->getCost();
            if (j != col - 1) {
                cout<<"\t";
            }
        }
        cout<<endl;
    }
}

