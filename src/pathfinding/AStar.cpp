#include "../headers/pathfinding/AStar.hpp"

AStar::AStar(Board* board, Heuristic* heuristic) : Algorithm(board), heuristic(heuristic) {}

void AStar::solve() {
    searchQueue.push(Path("", heuristic->calculate(graphRep.getStartNode()), 0, &graphRep));
    auto start = chrono::system_clock::now();
    while(!searchQueue.empty()) {
        totalIterations++;
        Path currPath = searchQueue.top();
        while(!searchQueue.empty()) {
            currPath = searchQueue.top();
            searchQueue.pop();
            closedPaths.push_back(currPath);
            auto it1 = find_if(closedPaths.begin(), closedPaths.end(), [currPath](const Path& p) {
                return (p.getNodeResult() == currPath.getNodeResult()) && p.getFValue() < currPath.getFValue();
            });
            if (it1 == closedPaths.end()) break;
        }
        if (currPath.getNodeResult() == graphRep.getGoalNode()) {
            if (solutionPath == nullptr) {
                solutionPath = new Path(currPath);
                auto end = chrono::system_clock::now();
                timeElapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
                solutionFound = true;
                break;
            }
        }
        for (auto pair : currPath.getNodeResult()->getSuccEdges()) {
            int nextCost = currPath.getTotalCost() + pair.second->getCost();
            Path nextPath = currPath.append(pair.second, nextCost + heuristic->calculate(pair.second->getSucc()));
            auto it1 = find_if(closedPaths.begin(), closedPaths.end(), [nextPath](const Path& p) {
                return (p.getNodeResult() == nextPath.getNodeResult()) && p.getFValue() < nextPath.getFValue();
            });


            if (it1 == closedPaths.end()) {
                searchQueue.push(nextPath);
            }
        }
    }
}