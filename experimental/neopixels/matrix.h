#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN       13
#define WIDTH 6
#define HEIGHT 6

Adafruit_NeoMatrix* createMatrix() {
    // Check with Ayden if NEO_MATRIX_ZIGZAG is needed.
    // The question here is if the pixel order reverses between lines
    // Should be column major, since we're indexing [y][x]. The column elements are consecutive in memory
    return &Adafruit_NeoMatrix(WIDTH, HEIGHT, PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS);
}

void matrixDraw(Adafruit_NeoMatrix* matrix, uint32_t colors[HEIGHT][WIDTH]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            matrix->setPixelColor(y * WIDTH + x, colors[y][x]);
        }
    }
}