#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN       13
#define NUMPIXELS 2

uint8_t base_colors[NUMPIXELS][3];

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

void setup_base_colors() {
  for (int i = 0; i < NUMPIXELS; i++) {
    base_colors[i][0] = 0;
    base_colors[i][1] = 255;
    base_colors[i][2] = 255;
  }
}

uint32_t color_of(int pixel) {
  uint8_t r = base_colors[pixel][0];
  uint8_t g = base_colors[pixel][1];
  uint8_t b = base_colors[pixel][2];
  return pixels.Color(r, g, b);
}

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();

  setup_base_colors();
}

void loop() {
  pixels.clear();
  static int r = 255, g = 128, b = 0;
  r = (r + 10) % 255;
  g = (g + 10) % 255;
  b = (b + 10) % 255;
  // TODO
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color_of(i) + pixels.Color(r, g, b));
  }

  pixels.show();
  delay(DELAYVAL);
}