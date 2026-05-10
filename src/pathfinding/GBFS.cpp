#include "../headers/pathfinding/GBFS.hpp"


GBFS::GBFS(Board* board, Heuristic* heuristic) : Algorithm(board), heuristic(heuristic) {}

void GBFS::solve() {
    if (!graphRep.isGraphSolvable()) return;
    searchQueue.push(Path("", heuristic->calculate(graphRep.getStartNode()), 0, &graphRep));
    while(!searchQueue.empty()) {
        totalIterations++;
        Path currPath = searchQueue.top();
        if (currPath.getNodeResult() == graphRep.getGoalNode()) {
            solutionPath = new Path(currPath);
            auto end = chrono::steady_clock::now();
            timeElapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            solutionFound = true;
            break;
        }
        searchQueue.pop();
        closedPaths.push_back(currPath);
        for (auto pair : currPath.getNodeResult()->getSuccEdges()) {
            Path nextPath = currPath.append(pair.second, heuristic->calculate(pair.second->getSucc()));
            auto it1 = find_if(closedPaths.begin(), closedPaths.end(), [nextPath](const Path& p) {
                return (p.getNodeResult() == nextPath.getNodeResult());
            });

            if (it1 == closedPaths.end()) {
                searchQueue.push(nextPath);
            }
        }
    }
}