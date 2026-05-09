#include "headers/game_modules/Board.hpp"
#include "headers/pathfinding/UCS.hpp"
#include "headers/pathfinding/GBFS.hpp"
#include "headers/pathfinding/AStar.hpp"
#include "headers/views/GUI.hpp"


int main() {
    // Board b(0,0);
    // b.loadBoard("data/test.txt");
    // b.printBoardTiles();
    // b.printBoardCosts();
    // cout<<endl<<endl;

    // Heuristic* h = new CheckpointsAwayFromGoal(&b);
    // //UCS alg(&b);
    // AStar alg(&b, h);
    // //GBFS alg(&b, h);
    // alg.solve();
    // alg.printResults();

    // Graph g = constructPathfindingGraph(&b);
    // g.printGraph();

    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Ice Slider Solver");

    SetTargetFPS(60);
    GUI gui;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        gui.render();

        EndDrawing();
    }

    CloseWindow();


}