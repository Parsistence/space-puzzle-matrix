#include "GameLogic.h"
#include <unistd.h> // For usleep()

GameLogic::GameLogic(GridInterface* grid)
    : p_grid(grid),
      m_running(false),
      m_gridWidth(0),
      m_gridHeight(0) {
}

void GameLogic::run() {
    if (p_grid->init() != 0) {
        return; // Failed to initialize
    }

    m_gridWidth = p_grid->getWidth();
    m_gridHeight = p_grid->getHeight();

    // Initialize the grid state
    m_gridState.resize(m_gridHeight, std::vector<uint32_t>(m_gridWidth, Colors::BLACK));

    // Create a simple starting pattern
    m_gridState[1][1] = Colors::RED;
    m_gridState[2][3] = Colors::GREEN;
    m_gridState[3][2] = Colors::BLUE;

    m_running = true;
    while (m_running) {
        // 1. Process Input
        ButtonPress press = p_grid->readInput();
        
        if (press.x == -2) { // Special "QUIT" signal from terminal
            m_running = false;
        } else if (press.x != -1) { // A valid button press
            processInput(press);
        }

        // 2. Update Game State (no updates needed for this game)

        // 3. Render
        render();

        // Frame rate limiting (~60 FPS)
        usleep(16667);
    }

    p_grid->shutdown();
}

void GameLogic::processInput(ButtonPress press) {
    // "Lights Out" game logic:
    // Toggle the pressed cell and its neighbors
    toggleCell(press.x, press.y);     // Center
    toggleCell(press.x, press.y - 1); // North
    toggleCell(press.x, press.y + 1); // South
    toggleCell(press.x - 1, press.y); // West
    toggleCell(press.x + 1, press.y); // East
}

void GameLogic::toggleCell(int x, int y) {
    // Check bounds
    if (x < 0 || x >= m_gridWidth || y < 0 || y >= m_gridHeight) {
        return;
    }

    // Toggle logic: If it's black, make it a color. If it's a color, make it black.
    if (m_gridState[y][x] == Colors::BLACK) {
        // Pick a color (e.g., magenta)
        m_gridState[y][x] = Colors::MAGENTA;
    } else {
        m_gridState[y][x] = Colors::BLACK;
    }
}

void GameLogic::render() {
    // 1. Clear the screen
    p_grid->clear();

    // 2. Draw the grid state
    for (int y = 0; y < m_gridHeight; ++y) {
        for (int x = 0; x < m_gridWidth; ++x) {
            uint32_t color = m_gridState[y][x];
            // Optimization: only draw non-black pixels
            // (clear() already handled black)
            if (color != Colors::BLACK) {
                p_grid->drawPixel(x, y, color);
            }
        }
    }

    // 3. Refresh the display (also draws the cursor in terminal)
    p_grid->refresh();
}