#pragma once
#include "Algorithm.hpp"


class UCS : public Algorithm {
    private:
    public:
        UCS(Board* board);
        void solve() override;
};