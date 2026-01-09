#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PXL_PIN       13
#define NUMPIXELS 1

#define BTN_PIN 2

#define DELAYVAL 10

uint8_t base_colors[NUMPIXELS][3];

bool lights_on = true;

Adafruit_NeoPixel pixels(NUMPIXELS, PXL_PIN, NEO_GRB + NEO_KHZ800);

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

void button_fsm() {
  enum {
    BTN_UP,
    BTN_DOWN,
  };

  static int state = BTN_UP;

  int btn_read = digitalRead(BTN_PIN);

  switch (state) {
  case BTN_UP:
    if (btn_read == LOW) {
      lights_on = !lights_on;
      state = BTN_DOWN;
    }
    break;

  case BTN_DOWN:
    if (btn_read == HIGH) {
      state = BTN_UP;
    }
    break;
  }
}

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();

  setup_base_colors();

  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
  button_fsm();

  pixels.clear();
  static int r = 255, g = 128, b = 0;
  r = (r + 10) % 255;
  g = (g + 10) % 255;
  b = (b + 10) % 255;
  // TODO
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color_of(i) + pixels.Color(r, g, b));
  }

  pixels.setBrightness(lights_on ? 255 : 0);

  pixels.show();
  delay(DELAYVAL);
}