#include "GameInterfaces.h"
#include "GameLogic.h"

// --- Configuration ---
// Option 1: Terminal (ncurses)
#include "TerminalImplementation.h"

// Option 2: Hardware (Stub)
// #include "HardwareImplementation.h"
// ---------------------


int main() {
    // --- Select Implementation ---
    
    // Option 1: Terminal (ncurses)
    TerminalGrid grid;

    // Option 2: Hardware (Stub)
    // HardwareGrid grid;
    
    // ---------------------------

    // The GameLogic is created with the chosen grid.
    // It doesn't know if it's a 5x5 terminal sim
    // or an 8x8 hardware grid.
    GameLogic game(&grid);

    // Run the game
    game.run();

    return 0;
}