#pragma once
#include "../game_modules/Board.hpp"
#include "Graph.hpp"
#include <queue>
#include <chrono>
#include <algorithm>

class Path {
    private:
        string pathRep;
        int fValue;
        int totalCost;
        long order;
        Graph* graph;
        Node* nodeResult;
        static long currentOrder;
    public:
        Path(const string pathRep, const int fValue, const int totalCost, Graph* graph) ;
        const string getPathRep() const;
        const int getTotalCost() const;
        const int getFValue() const;
        Node* getNodeResult() const;
        Path append(Edge* edge) const;
        Path append(Edge* edge, const int fValue) const;
        const bool isNodeVisited(Node* node) const;
        bool operator<(const Path& other) const;
};


class Algorithm {
    protected:
        int totalIterations;
        chrono::time_point<chrono::steady_clock> start;
        long timeElapsed;
        bool solutionFound;
        Path* solutionPath;
        priority_queue<Path> searchQueue;
        vector<Path> closedPaths;
        Board* board;
        Graph graphRep;
    public:
        Algorithm(Board* board);
        Board* getBoard() const;
        const Graph* getGraph() const;
        const int getTotalIterations() const;
        const long getTimeElapsed() const;
        const bool isSolutionFound() const;
        const Path* getSolutionPath() const;
        void printResults() const;
        virtual void solve() = 0;
};