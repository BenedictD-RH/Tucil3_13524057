#include "../headers/pathfinding/UCS.hpp"


UCS::UCS(Board* board) : Algorithm(board) {}

void UCS::solve() {
    searchQueue.push(Path("", 0, 0, &graphRep));
    while(!searchQueue.empty()) {
        totalIterations++;
        Path currPath = searchQueue.top();
        while(!searchQueue.empty()) {
            currPath = searchQueue.top();
            searchQueue.pop();
            closedPaths.push_back(currPath);
            auto it1 = find_if(closedPaths.begin(), closedPaths.end(), [currPath](const Path& p) {
                return (p.getNodeResult() == currPath.getNodeResult()) && p.getTotalCost() < currPath.getTotalCost();
            });
            if (it1 == closedPaths.end()) break;
        }
        if (currPath.getNodeResult() == graphRep.getGoalNode()) {
            solutionPath = new Path(currPath);
            solutionFound = true;
            break;
        }
        for (auto pair : currPath.getNodeResult()->getSuccEdges()) {
            Path nextPath = currPath.append(pair.second);


            searchQueue.push(nextPath);
        }
    }
}