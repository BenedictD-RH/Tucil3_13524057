#include "../headers/pathfinding/Graph.hpp"

Node::Node(Tile* tile, NumberTile* lastNumTile) : tile(tile), lastNumVisited(lastNumTile) {}

Tile* Node::getTile() const { return tile; }
NumberTile* Node::getLastNumVisited() const { return lastNumVisited; }
map<char, Edge*> Node::getSuccEdges() const { return succEdges; }
vector<Edge*> Node::getPredEdges() const { return predEdges; }
Edge* Node::succEdgeAt(const char dir) const { return succEdges.at(dir); }
Node* Node::succNodeAt(const char dir) const { return succEdges.at(dir)->getSucc(); }
Edge* Node::predEdgeAt(const int idx) const { return predEdges.at(idx); }

void Node::addPredEdge(Edge* edge) {
    predEdges.push_back(edge);
}

void Node::addSuccEdge(const char dir, Edge* edge) {
    succEdges[dir] = edge;
}

void Node::printNode() {
    cout<<"("<<tile->getX()<<", "<<tile->getY()<<") ";
    if (lastNumVisited == nullptr) {
        cout <<"-1";
    } else {
        cout<<lastNumVisited->getNumber();
    }
}

Edge::Edge(Node* pred, Node* succ, const int cost, const char dir) : pred(pred), succ(succ), cost(cost), dir(dir) {
    pred->addSuccEdge(dir, this);
    succ->addPredEdge(this);
}

const char Edge::getEdgeDir() const { return dir; }
const int Edge::getCost() const { return cost; }
Node* Edge::getPred() const { return pred; }
Node* Edge::getSucc() const { return succ; }

Graph::Graph(Node* startNode, Node* goalNode) : startNode(startNode), goalNode(goalNode) {
    addNode(startNode);
    addNode(goalNode);
}

Node* Graph::getStartNode() const { return startNode; }
Node* Graph::getGoalNode() const { return goalNode; }

void Graph::addNode(Node* node) {
    nodeList[{node->getTile(), node->getLastNumVisited()}] = node;
}

void Graph::addEdge(Edge* edge) {
    edgeList[{edge->getPred(), edge->getSucc()}] = edge;
}

Node* Graph::getNode(Tile* tile, NumberTile* lastNumTile) const {
    if (nodeList.find({tile, lastNumTile}) == nodeList.end()) return nullptr;
    return nodeList.at({tile, lastNumTile});
}
map<pair<Tile*, NumberTile*>, Node*> Graph::getNodeList() const {
    return nodeList;
}
map<pair<Node*, Node*>, Edge*> Graph::getEdgeList() const {
    return edgeList;
}

void Graph::printGraph() const {
    cout<<"NODES: "<<endl;
    for (auto pair : nodeList) {
        pair.second->printNode();
        cout<<endl;
    }
    cout<<endl<<endl;
    cout<<"EDGES: "<<endl;
    for (auto pair : edgeList) {
        pair.first.first->printNode();
        cout<<" -"<<pair.second->getCost()<<"-> ";
        pair.first.second->printNode();
        cout<<endl;
    }
}

const bool Graph::isGraphSolvable() const {
    return goalNode->getPredEdges().size() > 0;
}

void constructGraphPath(Graph* g, Node* currNode, const string currPath, Board * board) {
    int currPathCost = board->controlBlock(currPath)->getTotalCost();
    board->resetBlock();
    for(char dir : {'U', 'L', 'R', 'D'}) {
        Block* blockState = board->controlBlock(currPath + dir);
        Tile* nextTile = blockState->getCurrentTile();
        int nextCost = blockState->getTotalCost() - currPathCost;
        NumberTile* lastNumTile = blockState->getLastNumberTileVisited();
        bool checkPath = !blockState->isGameOver() && !blockState->isAt(*currNode->getTile());
        board->resetBlock();
        if (checkPath) {
            Node* nextNode = g->getNode(nextTile, lastNumTile);
            if (nextNode == nullptr) {
                nextNode = new Node(nextTile, lastNumTile);
                g->addNode(nextNode);
                constructGraphPath(g, nextNode, currPath + dir, board);
            }
            
            Edge* nextEdge = new Edge(currNode, nextNode, nextCost, dir);
            g->addEdge(nextEdge);
            
        }
    }
}

Graph constructPathfindingGraph(Board *board) {
    Graph g(new Node(board->getStartTile(), nullptr), new Node(board->getGoalTile(), board->getFinalNumberTile()));
    constructGraphPath(&g, g.getStartNode(), "", board);
    return g;
}

