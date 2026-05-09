#pragma once
#include "Algorithm.hpp"


class Heuristic {
    protected:
        Board* board;
    public:
        Heuristic(Board* board);
        virtual int calculate(Node* node) const = 0;
};

class CTCCoordinateManhattan : public Heuristic{
    public:
        CTCCoordinateManhattan(Board* board);
        int calculate(Node* node) const override;
};

class CTCCostManhattan : public Heuristic{
    public:
        CTCCostManhattan(Board* board);
        int calculate(Node* node) const override;
};

class NoHeuristic : public Heuristic{
    public:
        NoHeuristic(Board* board);
        int calculate(Node* node) const override;
};

class CTGCoordinateManhattan : public Heuristic {
    public:
        CTGCoordinateManhattan(Board* board);
        int calculate(Node* node) const override;
};

class CheckpointsAwayFromGoal : public Heuristic {
    private:
        int avgEdgeCost;
    public:
        CheckpointsAwayFromGoal(Board* board);
        int calculate(Node* node) const override;
};
