#include "TerminalImplementation.h"
#include "Colors.h"

// ncurses color pair definitions
const int PAIR_BLACK   = 1;
const int PAIR_RED     = 2;
const int PAIR_GREEN   = 3;
const int PAIR_YELLOW  = 4;
const int PAIR_BLUE    = 5;
const int PAIR_MAGENTA = 6;
const int PAIR_CYAN    = 7;
const int PAIR_WHITE   = 8;


TerminalGrid::TerminalGrid()
    : m_gridWidth(5),  // Hardcode a 5x5 grid for the terminal
      m_gridHeight(5),
      m_cursorX(0),
      m_cursorY(0) {
}

TerminalGrid::~TerminalGrid() {
    if (isendwin() == FALSE) {
        shutdown();
    }
}

int TerminalGrid::init() {
    if (initscr() == NULL) return -1;
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return -1;
    }
    
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // non-blocking getch()

    init_color_pairs();
    return 0;
}

void TerminalGrid::init_color_pairs() {
    init_pair(PAIR_BLACK,   COLOR_BLACK,   COLOR_BLACK);
    init_pair(PAIR_RED,     COLOR_RED,     COLOR_RED);
    init_pair(PAIR_GREEN,   COLOR_GREEN,   COLOR_GREEN);
    init_pair(PAIR_YELLOW,  COLOR_YELLOW,  COLOR_YELLOW);
    init_pair(PAIR_BLUE,    COLOR_BLUE,    COLOR_BLUE);
    init_pair(PAIR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(PAIR_CYAN,    COLOR_CYAN,    COLOR_CYAN);
    init_pair(PAIR_WHITE,   COLOR_WHITE,   COLOR_WHITE);
}

int TerminalGrid::get_color_pair(uint32_t color) {
    switch (color) {
        case Colors::RED:     return PAIR_RED;
        case Colors::GREEN:   return PAIR_GREEN;
        case Colors::BLUE:    return PAIR_BLUE;
        case Colors::YELLOW:  return PAIR_YELLOW;
        case Colors::CYAN:    return PAIR_CYAN;
        case Colors::MAGENTA: return PAIR_MAGENTA;
        case Colors::WHITE:   return PAIR_WHITE;
        case Colors::BLACK:
        default:
            return PAIR_BLACK;
    }
}

void TerminalGrid::clear() {
    ::clear(); // ncurses clear
}

void TerminalGrid::drawPixel(int x, int y, uint32_t color) {
    // Check grid bounds
    if (x < 0 || x >= m_gridWidth || y < 0 || y >= m_gridHeight) {
        return;
    }

    // Get the ncurses color
    int pair_id = get_color_pair(color);
    
    // Calculate top-left corner of the "cell"
    int startRow = y * m_cellHeight;
    int startCol = x * m_cellWidth;

    attron(COLOR_PAIR(pair_id));

    // Draw the cell block
    for (int r = 0; r < m_cellHeight; ++r) {
        for (int c = 0; c < m_cellWidth; ++c) {
            // Check terminal screen bounds
            if (startRow + r < LINES && startCol + c < COLS) {
                mvaddch(startRow + r, startCol + c, ACS_BLOCK);
            }
        }
    }

    attroff(COLOR_PAIR(pair_id));
}

void TerminalGrid::drawCursor() {
    // Calculate top-left corner of the cell under the cursor
    int startRow = m_cursorY * m_cellHeight;
    int startCol = m_cursorX * m_cellWidth;
    int endRow = startRow + m_cellHeight - 1;
    int endCol = startCol + m_cellWidth - 1;

    // Use white color for the cursor
    init_pair(99, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(99));

    // Draw a 'plus' sign outline
    mvaddch(startRow, startCol, '+');
    mvaddch(startRow, endCol, '+');
    mvaddch(endRow, startCol, '+');
    mvaddch(endRow, endCol, '+');

    attroff(COLOR_PAIR(99));
}

void TerminalGrid::refresh() {
    drawCursor(); // Draw the cursor on top of the grid
    ::refresh();  // ncurses refresh
}

ButtonPress TerminalGrid::readInput() {
    int ch = getch();

    switch (ch) {
        case KEY_UP:
            if (m_cursorY > 0) m_cursorY--;
            break;
        case KEY_DOWN:
            if (m_cursorY < m_gridHeight - 1) m_cursorY++;
            break;
        case KEY_LEFT:
            if (m_cursorX > 0) m_cursorX--;
            break;
        case KEY_RIGHT:
            if (m_cursorX < m_gridWidth - 1) m_cursorX++;
            break;
        
        case 'q':
        case 'Q':
            // Special signal to quit
            return ButtonPress{-2, -2}; 
        
        case ' ':
        case '\n':
        case KEY_ENTER:
            // "Press" the button at the cursor's location
            return ButtonPress{m_cursorX, m_cursorY};

        case ERR:
        default:
            // No input
            break;
    }

    // No press occurred
    return ButtonPress{-1, -1};
}

void TerminalGrid::shutdown() {
    endwin();
}

int TerminalGrid::getWidth() {
    return m_gridWidth;
}

int TerminalGrid::getHeight() {
    return m_gridHeight;
}