#ifndef COLORS_H
#define COLORS_H

#include <cstdint> // For uint32_t

/**
 * @namespace Colors
 * @brief Defines standard 24-bit (0xRRGGBB) hex color constants.
 */
namespace Colors {
    // Standard 8-bit RRGGBB hex colors
    constexpr uint32_t BLACK   = 0x000000;
    constexpr uint32_t WHITE   = 0xFFFFFF;

    constexpr uint32_t RED     = 0xFF0000;
    constexpr uint32_t GREEN   = 0x00FF00;
    constexpr uint32_t BLUE    = 0x0000FF;

    constexpr uint32_t YELLOW  = 0xFFFF00;
    constexpr uint32_t CYAN    = 0x00FFFF;
    constexpr uint32_t MAGENTA = 0xFF00FF;

    // Common extras
    constexpr uint32_t ORANGE  = 0xFFA500;
    constexpr uint32_t PURPLE  = 0x800080;
    constexpr uint32_t PINK    = 0xFFC0CB;

} // namespace Colors

#endif // COLORS_H