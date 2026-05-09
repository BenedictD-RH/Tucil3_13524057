#include "headers/game_modules/Board.hpp"
#include "headers/pathfinding/UCS.hpp"
#include "headers/pathfinding/GBFS.hpp"
#include "headers/pathfinding/AStar.hpp"
#include "raylib.h"


int main() {
    Board b(0,0);
    b.loadBoard("data/test.txt");
    b.printBoardTiles();
    b.printBoardCosts();
    cout<<endl<<endl;

    Heuristic* h = new CheckpointsAwayFromGoal(&b);
    //UCS alg(&b);
    AStar alg(&b, h);
    //GBFS alg(&b, h);
    alg.solve();
    alg.printResults();

    // Graph g = constructPathfindingGraph(&b);
    // g.printGraph();

    // const int screenWidth = 800;
    // const int screenHeight = 800;

    // InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // SetTargetFPS(60);

    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();

    //         ClearBackground(RAYWHITE);

    //         g.drawEdges(1);
    //         //g.drawNodes();

    //     EndDrawing();
    // }

    // CloseWindow();



    // while(true) {
    //     string s;
    //     cin>>s;
    //     Block *blockState = b.controlBlock(s);
    //     b.printBoardTiles();
    //     cout<<"Current Cost: "<<blockState->getTotalCost()<<endl;
    //     if (!blockState->isOngoing()) {
    //         if (blockState->isGameOver()) {
    //             cout<<"GAME OVER"<<endl;
    //         } else {
    //             cout<<"GOAL_REACHED"<<endl;
    //         }
    //         break;
    //     };
    // }
}