#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "GameInterfaces.h"
#include "Colors.h"
#include <vector>

/**
 * @class GameLogic
 * @brief A "Lights Out" style game, perfect for a button matrix.
 *
 * Pressing a button toggles its color and the color of its
 * four cardinal neighbors.
 */
class GameLogic {
public:
    /**
     * @brief Constructor.
     * @param grid A pointer to the unified grid implementation.
     */
    GameLogic(GridInterface* grid);

    /**
     * @brief Runs the main game loop.
     */
    void run();

private:
    /**
     * @brief Processes a single button press.
     * @param press The ButtonPress struct (with x, y) to process.
     */
    void processInput(ButtonPress press);

    /**
     * @brief Renders the current game state to the grid.
     */
    void render();

    /**
     * @brief Helper function to toggle the color of a cell at (x, y).
     * It safely handles out-of-bounds attempts.
     */
    void toggleCell(int x, int y);

    GridInterface* p_grid; // Pointer to the abstracted grid
    bool m_running;

    int m_gridWidth;
    int m_gridHeight;

    /**
     * @brief 2D vector to store the state (color) of our game grid.
     */
    std::vector<std::vector<uint32_t>> m_gridState;
};

#endif // GAME_LOGIC_H