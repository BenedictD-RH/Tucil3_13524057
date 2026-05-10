#include "../headers/pathfinding/Algorithm.hpp"

long Path::currentOrder = 0;

Path::Path(const string pathRep, const int fValue, const int totalCost, Graph* graph) : pathRep(pathRep), fValue(fValue), 
                                                                      graph(graph), order(currentOrder), totalCost(totalCost) {                      
        currentOrder++;
        Node* current = graph->getStartNode();
        for(char c : pathRep) {
            current = current->succEdgeAt(c)->getSucc();
        }
        nodeResult = current;
    }

const string Path::getPathRep() const { return pathRep; }
const int Path::getFValue() const { return fValue; }
const int Path::getTotalCost() const { return totalCost; }
Node* Path::getNodeResult() const {
    return nodeResult;
}

const bool Path::isNodeVisited(Node* node) const {
    Node* current = graph->getStartNode();
    if (current == node) return true;
    for(char c : pathRep) {
        current = current->succEdgeAt(c)->getSucc();
        if (current == node) return true;
    }
    return false;
}

Path Path::append(Edge* edge) const {
    return Path(pathRep + edge->getEdgeDir(), fValue + edge->getCost(), totalCost + edge->getCost(), graph);
}

Path Path::append(Edge* edge, const int fValue) const {
    return Path(pathRep + edge->getEdgeDir(), fValue, totalCost + edge->getCost(), graph);
}

bool Path::operator<(const Path& other) const {
    if (this->fValue != other.fValue) return this->fValue > other.fValue;
    else return this->order > other.order;
}

Algorithm::Algorithm(Board* board) : totalIterations(0), timeElapsed(0),
                                     solutionFound(false), solutionPath(nullptr), 
                                     graphRep(constructPathfindingGraph(board)), board(board), start(chrono::steady_clock::now()) {}

Board* Algorithm::getBoard() const { return board; }
const Graph* Algorithm::getGraph() const { return &graphRep; }
const int Algorithm::getTotalIterations() const { return totalIterations; }
const long Algorithm::getTimeElapsed() const { return timeElapsed; }
const bool Algorithm::isSolutionFound() const { return solutionFound; }
const Path* Algorithm::getSolutionPath() const { return solutionPath; }

void Algorithm::printResults() const {
    if (solutionFound) {
        cout<<"Total Iterations: "<<totalIterations<<endl;
        cout<<"Time Elapsed: "<<timeElapsed<<"ms"<<endl;
        cout<<"Solution Path: "<<solutionPath->getPathRep()<<endl;
        cout<<"Total Cost: "<<solutionPath->getTotalCost()<<endl;
    }
}