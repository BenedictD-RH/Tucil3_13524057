#include "../View2D.hpp"
#include "../Entry.hpp"
#include "../board/BoardView.hpp"
#include "PlaybackControl.hpp"

class SolverInput : public View2D {
    private:
        Entry rowInput;
        Entry colInput;
        Entry fileInput;
        Interactable algorithmSwitch;
        int algorithmState;
        Interactable heuristicSwitch;
        int heuristicState;
        Interactable solveBtn;
        PlaybackControl* playbackControl;
        BoardView* board;
        string results;
        void solve();
    public:
        SolverInput(BoardView* board);
        void setBoardView(BoardView* board);
        void interactionCheck() override;
        void render() override;
};