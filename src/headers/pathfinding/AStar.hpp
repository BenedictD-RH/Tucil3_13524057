#pragma once
#include "Algorithm.hpp"
#include "Heuristic.hpp"


class AStar : public Algorithm {
    private:
        Heuristic* heuristic;
    public:
        AStar(Board* board, Heuristic* heuristic);
        void solve() override;
};