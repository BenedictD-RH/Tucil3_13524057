#pragma once
#include "Algorithm.hpp"
#include "Heuristic.hpp"


class GBFS : public Algorithm {
    private:
        Heuristic* heuristic;
    public:
        GBFS(Board* board, Heuristic* heuristic);
        void solve() override;
};