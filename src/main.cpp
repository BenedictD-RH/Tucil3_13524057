#include "headers/game_modules/Board.hpp"
#include "headers/views/GUI.hpp"


int main() {
    Board b(0,0);
    b.loadBoard("");
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

    const int screenWidth = 1600;
    const int screenHeight = 900;
    SetTraceLogLevel(LOG_NONE);
    InitWindow(screenWidth, screenHeight, "Ice Slider Solver");
    View2D::addFont("Futura", "assets/Futura Heavy.otf");
    SetTargetFPS(60);
    GUI gui;
    gui.loadBoard(b);
    while (!WindowShouldClose())
    {
        gui.update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        gui.render();
        DrawFPS(10,10);
        EndDrawing();
    }

    CloseWindow();


}