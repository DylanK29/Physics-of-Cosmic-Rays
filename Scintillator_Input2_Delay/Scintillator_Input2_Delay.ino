#include <FastLED.h>

#define NUM_LEDS 144
#define DATA_PIN 7  // Change this to match your LED strip's data pin
#define DATA_PIN2 6
#define DATA_PIN3 5
#define BRIGHTNESS 255

// Define delays for each strip (in positions)
#define STRIP2_DELAY 48  // Strip 2 starts 48 positions behind strip 1
#define STRIP3_DELAY 96  // Strip 3 starts 96 positions behind strip 1

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

uint8_t pos = 0;
uint8_t pos2 = 0;
uint8_t pos3 = 0;
bool toggle = false;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(leds2, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN3, GRB>(leds3, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  // Initialize positions with the staggered delays
  pos = 0;
  pos2 = NUM_LEDS - STRIP2_DELAY;  // Start at a negative position (will wrap around)
  pos3 = NUM_LEDS - STRIP3_DELAY;  // Start at a negative position (will wrap around)
}

void loop() {
  // Fade all LEDs slightly
  fadeToBlackBy(leds, NUM_LEDS, 64);
  fadeToBlackBy(leds2, NUM_LEDS, 64);
  fadeToBlackBy(leds3, NUM_LEDS, 64);
  
  // Add bright pixels that move
  leds[pos] = CRGB::Red;
  leds2[pos2] = CRGB::Blue;
  leds3[pos3] = CRGB::Green;
  
  // Blur the entire strips
  blur1d(leds, NUM_LEDS, 172);
  blur1d(leds2, NUM_LEDS, 172);
  blur1d(leds3, NUM_LEDS, 172);
  
  FastLED.show();
  
  
  if (toggle) {
    // Move all positions by 4 LEDs
    pos = (pos + 5) % NUM_LEDS;
    pos2 = (pos2 + 5) % NUM_LEDS;
    pos3 = (pos3 + 5) % NUM_LEDS;
  }
  toggle = !toggle;
  
  delay(.5);  
}