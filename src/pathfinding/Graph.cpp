#include "../headers/pathfinding/Graph.hpp"

Node::Node(Tile* tile, NumberTile* lastNumTile) : tile(tile), lastNumVisited(lastNumTile) {}

Tile* Node::getTile() const { return tile; }
NumberTile* Node::getLastNumVisited() const { return lastNumVisited; }
vector<Edge*> Node::getSuccEdges() const { return succEdges; }
vector<Edge*> Node::getPredEdges() const { return predEdges; }
Edge* Node::succEdgeAt(const int idx) const { return succEdges.at(idx); }
Edge* Node::predEdgeAt(const int idx) const { return predEdges.at(idx); }

void Node::addPredEdge(Edge* edge) {
    predEdges.push_back(edge);
}

void Node::addSuccEdge(Edge* edge) {
    succEdges.push_back(edge);
}

void Node::printNode() {
    cout<<"("<<tile->getX()<<", "<<tile->getY()<<") ";
    if (lastNumVisited == nullptr) {
        cout <<"-1";
    } else {
        cout<<lastNumVisited->getNumber();
    }
}

Edge::Edge(Node* pred, Node* succ, const int cost) : pred(pred), succ(succ), cost(cost) {
    pred->addSuccEdge(this);
    succ->addPredEdge(this);
}

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
        cout<<" --> ";
        pair.first.second->printNode();
        cout<<endl;
    }
}

void Graph::drawEdges(int num) {
    for (auto pair : edgeList) {
        bool drawEdge = false;
        drawEdge = num == -1 && pair.first.first->getLastNumVisited() == nullptr && pair.first.second->getLastNumVisited() == nullptr;
        if (!drawEdge && pair.first.first->getLastNumVisited() != nullptr && pair.first.second->getLastNumVisited() != nullptr) 
            drawEdge = (pair.first.first->getLastNumVisited()->getNumber() == num && pair.first.second->getLastNumVisited()->getNumber() == num);
        if (drawEdge) {
            Vector2 start = pair.first.first->getTile()->getRenderPos();
            Vector2 end = pair.first.second->getTile()->getRenderPos();
            Vector2 dir = Vector2Normalize(end - start);
            int neg = (dir.y == 0) ? 1 : -1;
            DrawLineEx(start, end, 1.0f, BLACK);
            DrawTriangle(
                end,
                end + dir*-10 + (Vector2){dir.y, dir.x}*-5*neg,
                end + dir*-10 + (Vector2){dir.y, dir.x}*5*neg,
                BLACK
            );
        }
    }
}

void Graph::drawNodes(int num) {
    for (auto pair : nodeList) {
        DrawCircle(pair.first.first->getRenderPos().x, pair.first.first->getRenderPos().y, 30, GRAY);
        
    }
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
            
            Edge* nextEdge = new Edge(currNode, nextNode, nextCost);
            g->addEdge(nextEdge);
            
        }
    }
}

Graph constructPathfindingGraph(Board *board) {
    Graph g(new Node(board->getStartTile(), nullptr), new Node(board->getGoalTile(), board->getFinalNumberTile()));
    constructGraphPath(&g, g.getStartNode(), "", board);
    return g;
}

