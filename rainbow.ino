
#include <FastLED.h>

#define IS_SIMULATION 

#define LED_PIN     2
#define NUM_ROWS    15
#define NUM_COLS    20
#define NUM_LEDS    (NUM_ROWS * NUM_COLS)
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

uint16_t XY(uint8_t x, uint8_t y) {
  uint16_t i;
  #ifdef IS_SIMULATION
    i = (y * NUM_COLS) + x;
  #else
    if (y & 0x01) {
      uint8_t reverseX = (NUM_COLS - 1) - x;
      i = (y * NUM_COLS) + reverseX;
    } else {
      i = (y * NUM_COLS) + x;
    }
  #endif
  return i;
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  static uint8_t startHue = 0;
  
  for (int x = 0; x < NUM_COLS; x++) {
    for (int y = 0; y < NUM_ROWS; y++) {
      leds[XY(x, y)] = CHSV(startHue + (x * 10) + (y * 10), 255, 255);
    }
  }

  FastLED.show();
  startHue++;
  delay(20);
}
