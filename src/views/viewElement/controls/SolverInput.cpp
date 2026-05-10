#include "../../../headers/views/viewElement/controls/SolverInput.hpp"
#include "../../../headers/pathfinding/UCS.hpp"
#include "../../../headers/pathfinding/GBFS.hpp"
#include "../../../headers/pathfinding/AStar.hpp"


SolverInput::SolverInput(BoardView* board) : View2D((Vector2){GetScreenWidth()*0.15f, GetScreenHeight()*0.5f}, 
                                                  (Vector2){GetScreenWidth()*0.3f, GetScreenHeight()*1.0f}, [](){}), board(board), 
                                                  rowInput(Entry((Vector2){GetScreenWidth()*0.075f, 50.0f}, "", 36, "Futura", [](){})),
                                                  colInput(Entry((Vector2){GetScreenWidth()*0.075f, 50.0f}, "", 36, "Futura", [](){})),
                                                  fileInput(Entry((Vector2){GetScreenWidth()*0.2f, 50.0f}, "Input File Path", 36, "Futura", [](){})),
                                                  algorithmState(0),
                                                  algorithmSwitch(Interactable((Vector2){GetScreenWidth()*0.25f, 60.0f}, true, false, "", [](){}, [](){})),
                                                  heuristicState(0),
                                                  heuristicSwitch(Interactable((Vector2){GetScreenWidth()*0.25f, 60.0f}, true, false, "", [](){}, [](){})),
                                                  solveBtn(Interactable((Vector2){GetScreenWidth()*0.175f, 60.0f}, true, false, "", [](){}, [](){})),
                                                  playbackControl(nullptr), results("") {
    rowInput.movePosition(getPos() + (Vector2){-120.0f, -350.0f});
    rowInput.setOnEnterFunc([this](){
        int newRow = this->board->getBoardSize().y;
        try {
            newRow = stoi(rowInput.getEntryText());
            if (newRow <= 0) {
                newRow = this->board->getBoardSize().y;
                stoi("a");
            }
            this->board->setBoardSize(newRow, this->board->getBoardSize().x);
        } catch (invalid_argument e) {

        }
        rowInput.setEntryText(to_string(newRow));
    });
    colInput.movePosition(getPos() + (Vector2){120.0f, -350.0f});
    colInput.setOnEnterFunc([this](){
        int newCol = this->board->getBoardSize().x;
        try {
            newCol = stoi(colInput.getEntryText());
            if (newCol <= 0) {
                newCol = this->board->getBoardSize().x;
                stoi("a");
            }
            this->board->setBoardSize(this->board->getBoardSize().y, newCol);
        } catch (invalid_argument e) {

        }
        colInput.setEntryText(to_string(newCol));
    });

    fileInput.movePosition(getPos() + (Vector2){0, -350.0f});
    fileInput.setOnEnterFunc([this](){
        this->board->loadBoardFromFile(fileInput.getEntryText());
        solveBtn.setActive(this->board->getBoardState().isBoardValid());
        if (playbackControl != nullptr) delete playbackControl;
        playbackControl = nullptr;
        this->board->resetPlaybackSettings();
        results = "";
    });

    algorithmSwitch.movePosition(getPos() + (Vector2) {0, -250.0f});
    algorithmSwitch.setOnClicked([this](){
        algorithmState = (algorithmState + 1) % 3;
        if (algorithmState == 0) {
            heuristicSwitch.setActive(false);
            heuristicSwitch.setVisible(false);
        } else {
            heuristicSwitch.setActive(true);
            heuristicSwitch.setVisible(true);
        }
    });
    algorithmSwitch.setRender([this](){
        Color color;
        string text;
        if (algorithmState == 0) {
            color = MAROON;
            text = "Uniform Cost Search";
        }
        else if (algorithmState == 1) {
            color = MAGENTA;
            text = "Greedy Best First Search";
        }
        else {
            color = {111, 209, 215, 255};
            text = "A*";
        }
        DrawRectangleRounded({algorithmSwitch.getRenderPos().x, algorithmSwitch.getRenderPos().y,
                              algorithmSwitch.getRenderWidth(), algorithmSwitch.getRenderHeight()}, 0.4f, 1, getRenderColor(color));
        drawTextLinesWrapped(getFont("Futura"), text, algorithmSwitch.getPos(), getRenderFontSize(36), 0, getRenderColor(WHITE), algorithmSwitch.getBoundingDim());
    });

    heuristicSwitch.setActive(false);
    heuristicSwitch.setVisible(false);
    heuristicSwitch.movePosition(getPos() + (Vector2) {0, -125.0f});
    heuristicSwitch.setOnClicked([this](){
        heuristicState = (heuristicState + 1) % 3;
    });
    heuristicSwitch.setRender([this](){
        Color color;
        string text;
        if (heuristicState == 0) {
            color = {93, 248, 216, 255};
            text = "Closest To Checkpoint by Coordinate Manhattan Distance";
        }
        else if (heuristicState == 1) {
            color = {250, 185, 91, 255};
            text = "Closest To Checkpoint by Cost Manhattan Distance";
        }
        else {
            color = {247, 165, 165, 255};
            text = "Checkpoints Away from Goal";
        }
        DrawRectangleRounded({heuristicSwitch.getRenderPos().x, heuristicSwitch.getRenderPos().y,
                              heuristicSwitch.getRenderWidth(), heuristicSwitch.getRenderHeight()}, 0.4f, 1, getRenderColor(color));
        drawTextLinesWrapped(getFont("FuturaSmall"), text, heuristicSwitch.getPos(), getRenderFontSize(25), 0, getRenderColor(WHITE), heuristicSwitch.getBoundingDim());
    });
    if (board != nullptr) {
        solveBtn.setActive(board->getBoardState().isBoardValid());
    } else {
        solveBtn.setActive(false);
    }
    solveBtn.movePosition(getPos());
    solveBtn.setOnClicked([this](){
        solve();
    });
    solveBtn.setRender([this](){
        Color color;
        string text;
        if (!solveBtn.isActive()) {
            color = {220, 20, 60, 255};
            text = "Board Invalid!";
        } else {
            color = {138, 154, 91, 255};
            text = "Solve Board";
        }
        DrawRectangleRounded({solveBtn.getRenderPos().x, solveBtn.getRenderPos().y,
                              solveBtn.getRenderWidth(), solveBtn.getRenderHeight()}, 0.4f, 1, getRenderColor(color));
        drawTextLinesWrapped(getFont("Futura"), text, solveBtn.getPos(), getRenderFontSize(36), 0, getRenderColor(WHITE), solveBtn.getBoundingDim());
    });
}

void SolverInput::solve() {
    board->resetPlaybackSettings();
    Heuristic* heuristic;
    switch(heuristicState) {
        case 0: heuristic = new CTCCoordinateManhattan(&board->getBoardState()); break;
        case 1: heuristic = new CTCCostManhattan(&board->getBoardState()); break;
        default: heuristic = new CheckpointsAwayFromGoal(&board->getBoardState()); break;
    }
    Algorithm* alg;
    switch(algorithmState) {
        case 0: alg = new UCS(&board->getBoardState()); break;
        case 1: alg = new GBFS(&board->getBoardState(), heuristic); break;
        default: alg = new AStar(&board->getBoardState(), heuristic); break;
    }
    alg->solve();
    alg->printResults();
    if (alg->isSolutionFound()) {
        board->setSolutionPath(alg->getSolutionPath()->getPathRep());
        playbackControl = new PlaybackControl(board);
        results = "Total Iterations: " + to_string(alg->getTotalIterations()) +
                  "\nTime Elapsed: " + to_string(alg->getTimeElapsed()) +
                  "ms\nTotal Cost: " + to_string(alg->getSolutionPath()->getTotalCost()) +
                  "\nSolution Path: " + alg->getSolutionPath()->getPathRep();
    } else {
        results = "No Solution Found";
    }
}

void SolverInput::setBoardView(BoardView* board) {
    this->board = board;
    std::stringstream ss;
    ss << board->getBoardSize().y;
    rowInput.setEntryText(ss.str());
    std::stringstream ss2;
    ss2 << board->getBoardSize().x;
    colInput.setEntryText(ss2.str());
}

void SolverInput::interactionCheck() {
    // rowInput.interactionCheck();
    // colInput.interactionCheck();
    fileInput.interactionCheck();
    algorithmSwitch.interactionCheck();
    heuristicSwitch.interactionCheck();
    solveBtn.interactionCheck();
    if (playbackControl != nullptr) playbackControl->interactionCheck();
}

void SolverInput::render() {
    DrawRectangle(getRenderPos().x, getRenderPos().y, getRenderWidth(), getRenderHeight(), {9, 60, 93, 255});
    drawTextLinesWrapped(getFont("Futura"), "File Input:", fileInput.getPos() + (Vector2){0, -50.0f}, 36, 0, WHITE, {200, 50});
    drawTextLinesWrapped(getFont("Futura"), results, getPos() + (Vector2){0, 150.0f}, 36, 0, WHITE, {getBoundingWidth()*0.8f, 50});
    // rowInput.render();
    // colInput.render();
    fileInput.render();
    algorithmSwitch.render();
    heuristicSwitch.render();
    solveBtn.render();
    if (playbackControl != nullptr) playbackControl->render();
}