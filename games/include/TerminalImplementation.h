#ifndef TERMINAL_IMPLEMENTATION_H
#define TERMINAL_IMPLEMENTATION_H

#include "GameInterfaces.h"
#include <ncurses.h>

/**
 * @class TerminalGrid
 * @brief Simulates a 5x5 button grid in the terminal.
 *
 * Uses ncurses to draw a 5x5 grid of "cells".
 * Arrow keys move a cursor.
 * Spacebar/Enter "presses" the button at the cursor.
 */
class TerminalGrid : public GridInterface {
public:
    TerminalGrid();
    virtual ~TerminalGrid();

    virtual int init() override;
    virtual void clear() override;
    virtual void drawPixel(int x, int y, uint32_t color) override;
    virtual void refresh() override;
    virtual ButtonPress readInput() override;
    virtual void shutdown() override;
    virtual int getWidth() override;
    virtual int getHeight() override;

private:
    void init_color_pairs();
    int get_color_pair(uint32_t color);

    /**
     * @brief Draws the cursor outline at its current position.
     */
    void drawCursor();

    int m_gridWidth;
    int m_gridHeight;
    
    // Size of each "cell" in the terminal (in characters)
    const int m_cellWidth = 7;
    const int m_cellHeight = 3;

    // Terminal cursor position (tracks which button is "selected")
    int m_cursorX;
    int m_cursorY;
};

#endif // TERMINAL_IMPLEMENTATION_H