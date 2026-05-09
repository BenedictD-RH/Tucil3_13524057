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
        map<char, Edge*> succEdges;
        vector<Edge*> predEdges;
    public :
        Node(Tile* tile, NumberTile* lastNumTile);
        Tile* getTile() const;
        NumberTile* getLastNumVisited() const;
        map<char, Edge*> getSuccEdges() const;
        vector<Edge*> getPredEdges() const;
        Edge* succEdgeAt(const char dir) const;
        Node* succNodeAt(const char dir) const;
        Edge* predEdgeAt(const int idx) const;
        void addSuccEdge(const char dir, Edge* edge);
        void addPredEdge(Edge* edge);
        void printNode();
};

class Edge {
    private:
        int cost;
        const char dir;
        Node* pred;
        Node* succ;  
    public:
        Edge(Node* pred, Node* succ, const int cost, const char dir);
        const char getEdgeDir() const;
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
        map<pair<Tile*, NumberTile*>, Node*> getNodeList() const;
        map<pair<Node*, Node*>, Edge*> getEdgeList() const;
        void printGraph() const;
        void drawNodes(int num);
        void drawEdges(int num);
};


Graph constructPathfindingGraph(Board *board);

