#ifndef GAME_INTERFACES_H
#define GAME_INTERFACES_H

#include <cstdint> // For uint32_t

/**
 * @struct ButtonPress
 * @brief A simple struct to represent a button press at a specific (x, y) coordinate.
 *
 * x = -1 indicates no button was pressed this frame.
 * x = -2 is a special signal used by the terminal to request QUIT.
 */
struct ButtonPress {
    int x = -1;
    int y = -1;
    
    // Default constructor (uses member initializers above).
    ButtonPress() = default;

    // Construct with explicit x,y coordinates.
    ButtonPress(int x_, int y_) : x(x_), y(y_) {}
};

/**
 * @class GridInterface
 * @brief A unified interface for a grid of button-lights.
 *
 * This new abstraction combines both display and input,
 * as the hardware (a button matrix) treats them as
 * two features of the same (x, y) coordinate.
 */
class GridInterface {
public:
    virtual ~GridInterface() {}

    /**
     * @brief Initialize the grid.
     * @return 0 on success, -1 on failure.
     */
    virtual int init() = 0;

    /**
    * @brief Clear the entire grid (set all pixels to black).
    */
    virtual void clear() = 0;

    /**
     * @brief Set the color of a single pixel/light.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param color The 0xRRGGBB color to set.
     */
    virtual void drawPixel(int x, int y, uint32_t color) = 0;

    /**
     * @brief Refresh the display to show any changes.
     */
    virtual void refresh() = 0;

    /**
     * @brief Read the current input.
     * @return A ButtonPress struct. If no button is pressed,
     * x and y will be -1.
     */
    virtual ButtonPress readInput() = 0;

    /**
     * @brief Shut down and clean up the grid.
     */
    virtual void shutdown() = 0;

    /**
     * @brief Get the width of the grid.
     */
    virtual int getWidth() = 0;

    /**
     * @brief Get the height of the grid.
     */
    virtual int getHeight() = 0;
};

#endif // GAME_INTERFACES_H