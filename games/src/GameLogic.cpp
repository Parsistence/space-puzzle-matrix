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

    // Start with a random tile
    setRandomCell();

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
    // If there are no targets, create one first.
    if (target_cells.empty()) {
        setRandomCell();
    }

    // Toggle the pressed cell and its cardinal neighbors
    toggleCell(press.x, press.y);     // Center
    // toggleCell(press.x, press.y - 1); // North
    // toggleCell(press.x, press.y + 1); // South
    // toggleCell(press.x - 1, press.y); // West
    // toggleCell(press.x + 1, press.y); // East

    // If the press corresponds to any target cell, remove that target
    for (auto it = target_cells.begin(); it != target_cells.end();) {
        if (it->first == press.x && it->second == press.y) {
            // Clear the target on the grid
            if (press.y >= 0 && press.y < m_gridHeight && press.x >= 0 && press.x < m_gridWidth) {
                m_gridState[press.y][press.x] = Colors::BLACK;
            }
            it = target_cells.erase(it);
        } else {
            ++it;
        }
    }

    // If we've cleared all targets, spawn another one
    if (target_cells.empty()) {
        setRandomCell();
    }
}

void GameLogic::toggleCell(int x, int y) {
    // Check bounds
    if (x < 0 || x >= m_gridWidth || y < 0 || y >= m_gridHeight) {
        return;
    }

    // Toggle logic: If it's black, make it a color. If it's a color, make it black.
    if (m_gridState[y][x] == Colors::BLACK) {
        // Pick a color (e.g., magenta)
        m_gridState[y][x] = Colors::RED;
    } else {
        m_gridState[y][x] = Colors::BLACK;
    }
}

void GameLogic::setRandomCell() {
    // Use stored grid dimensions and correct indexing: m_gridState[y][x]
    if (m_gridWidth <= 0 || m_gridHeight <= 0) {
        // Dimensions not initialized; try to read from the grid interface
        m_gridWidth = p_grid->getWidth();
        m_gridHeight = p_grid->getHeight();
        if (m_gridWidth <= 0 || m_gridHeight <= 0) {
            return; // Can't place a random cell without valid dimensions
        }
    }

    int x_coord = rand() % m_gridWidth;
    int y_coord = rand() % m_gridHeight;
    m_gridState[y_coord][x_coord] = Colors::BLUE;
    target_cells.emplace_back(static_cast<int8_t>(x_coord), static_cast<int8_t>(y_coord));
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