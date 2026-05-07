#pragma once
#include "../game_modules/Board.hpp"
#include <vector>
#include <set>
#include <map>

class Edge;

class Node {
    private:
        Tile* tile;
        NumberTile* lastNumVisited;
        vector<Edge*> succEdges;
        vector<Edge*> predEdges;
    public :
        Node(Tile* tile, NumberTile* lastNumTile);
        Tile* getTile() const;
        NumberTile* getLastNumVisited() const;
        vector<Edge*> getSuccEdges() const;
        vector<Edge*> getPredEdges() const;
        Edge* succEdgeAt(const int idx) const;
        Edge* predEdgeAt(const int idx) const;
        string getNodeKey() const;
        void addSuccEdge(Edge* edge);
        void addPredEdge(Edge* edge);
        void printNode();
};

class Edge {
    private:
        int cost;
        Node* pred;
        Node* succ;  
    public:
        Edge(Node* pred, Node* succ, const int cost);
        const int getCost() const;
        Node* getPred() const;
        Node* getSucc() const;
};

class Graph {
    private:
        Node* startNode;
        Node* goalNode;
        map<pair<Tile*, NumberTile*>, Node*> nodeList;
        map<pair<Node*, Node*>, Edge*> edgeList;
    public:
        Graph(Node* startNode, Node* goalNode);
        Node* getStartNode() const;
        Node* getGoalNode() const;
        void addNode(Node* node);
        void addEdge(Edge* edge);
        Node* getNode(Tile* tile, NumberTile* numTile) const;
        void printGraph() const;
        void drawNodes(int num);
        void drawEdges(int num);
};


Graph constructPathfindingGraph(Board *board);


