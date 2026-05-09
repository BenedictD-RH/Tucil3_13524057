#include "../headers/pathfinding/Heuristic.hpp"


int getManhattanDistance(Tile* t1, Tile* t2) {
    return abs(t1->getX() - t2->getX()) + abs(t1->getY() - t2->getY()); 
}


int getActualManhattanDistance(Tile* t1, Tile* t2, Board* board) {
    int path1Cost = 0;
    int path2Cost = 0;
    if (t1 != t2) {
        path1Cost = t2->getCost();
        path2Cost = t2->getCost();
    }
    if (t2->getX() - t1->getX() != 0) {
        int xInc = (t2->getX() - t1->getX())/abs(t1->getX() - t2->getX());
        for (int i = t1->getX() + xInc; i != t2->getX(); i += xInc) {
            path1Cost += board->tileAt(i, t1->getY())->getCost();
        }
        for (int i = t1->getX(); i != t2->getX(); i += xInc) {
            path2Cost += board->tileAt(i, t2->getY())->getCost();
        }
    }
    
    if (t2->getY() - t1->getY() != 0) {
        int yInc = (t2->getY() - t1->getY())/abs(t1->getY() - t2->getY());
        for (int i = t1->getY(); i != t2->getY(); i += yInc) {
            path1Cost += board->tileAt(t2->getX(), i)->getCost();
        }

        for (int i = t1->getY() + yInc; i != t2->getY(); i += yInc) {
            path2Cost += board->tileAt(t1->getX(), i)->getCost();
        }
    }
    

    return min(path1Cost, path2Cost);
}

int getAverageCost(Board* board) {
    int n = 0;
    int total = 0;
    for (int i = 0; i < board->getRow(); i++) {
        for (int j = 0; j < board->getCol(); j++) {
            if (board->tileAt(j, i)->getType() != UNPASSABLE_TILE && board->tileAt(j, i)->getType() != LAVA_TILE) {
                n++;
                total += board->tileAt(j, i)->getCost();
            }
        }
    }
    return total;
}

Heuristic::Heuristic(Board* board) : board(board) {}

CTCCoordinateManhattan::CTCCoordinateManhattan(Board* board) : Heuristic(board) {}

int CTCCoordinateManhattan::calculate(Node* node) const {
    Tile* nextCheckpointTile  = board->getNextNumberTile(node->getLastNumVisited());
    if (nextCheckpointTile == nullptr) {
        nextCheckpointTile = board->getGoalTile();
    }
    return getManhattanDistance(node->getTile(), nextCheckpointTile);
}

CTCCostManhattan::CTCCostManhattan(Board* board) : Heuristic(board) {}

int CTCCostManhattan::calculate(Node* node) const {
    Tile* nextCheckpointTile  = board->getNextNumberTile(node->getLastNumVisited());
    if (nextCheckpointTile == nullptr) {
        nextCheckpointTile = board->getGoalTile();
    }
    return getActualManhattanDistance(node->getTile(), nextCheckpointTile, board);
}

NoHeuristic::NoHeuristic(Board* board) : Heuristic(board) {}

int NoHeuristic::calculate(Node* node) const { return 0; }


CTGCoordinateManhattan::CTGCoordinateManhattan(Board* board) : Heuristic(board) {}

int CTGCoordinateManhattan::calculate(Node* node) const {
    return getManhattanDistance(node->getTile(), board->getGoalTile());
}

CheckpointsAwayFromGoal::CheckpointsAwayFromGoal(Board* board) : Heuristic(board), avgEdgeCost(1) {
    Graph g = constructPathfindingGraph(board);
    int total = 0;
    int n = 0;
    for (auto pair : g.getEdgeList()) {
        total += pair.second->getCost();   
        n++;     
    }
    if (n != 0) {
        if (total/n >= 1) {
            avgEdgeCost = total/n;
        }
    }
}

int CheckpointsAwayFromGoal::calculate(Node* node) const {
    if (node-> getTile() == board->getGoalTile()) return 0;
    if (node->getLastNumVisited() == nullptr) {
        if (board->getFinalNumberTile() == nullptr) {
            return avgEdgeCost;
        }
        return (board->getFinalNumberTile()->getNumber() + 1)*avgEdgeCost;
    } else {
        return (board->getFinalNumberTile()->getNumber() - node->getLastNumVisited()->getNumber() + 1)*avgEdgeCost;
    }
}