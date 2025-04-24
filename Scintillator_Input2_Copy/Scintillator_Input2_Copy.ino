// UIDescription: This example shows how to blur a strip of LEDs. It uses the blur1d function to blur the strip and fadeToBlackBy to dim the strip. A bright pixel moves along the strip.
// Author: Zach Vorhies

#include <FastLED.h>

#define NUM_LEDS 144
#define NUM_LEDS2 144
#define NUM_LEDS3 144
#define DATA_PIN 7  // Change this to match your LED strip's data pin
#define DATA_PIN2 6
#define DATA_PIN3 5
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
uint8_t pos = 0;
uint8_t pos2 = 0;
uint8_t pos3 = 0;
bool toggle = false;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(leds2, NUM_LEDS2);
  FastLED.addLeds<WS2812B, DATA_PIN3, GRB>(leds3, NUM_LEDS3);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Add a bright pixel that moves
  leds[pos] = CRGB::Red;
  
  
  // Blur the entire strip
  blur1d(leds, NUM_LEDS, 172);
  
  
  fadeToBlackBy(leds, NUM_LEDS, 64);
  
  
  FastLED.show();
  // Move the position of the dot
  if (toggle) {
    pos = (pos + 4) % NUM_LEDS;
  }
  toggle = !toggle;
  delay(5);


  leds2[pos2] = CRGB::Blue;
  blur1d(leds2, NUM_LEDS, 172);
  fadeToBlackBy(leds2, NUM_LEDS, 64);
  FastLED.show();
  if (toggle) {
    pos2 = (pos2 + 4) % NUM_LEDS2;
  }
  toggle = !toggle;
  delay(5);



  leds3[pos3] = CRGB::Green;
  blur1d(leds3, NUM_LEDS, 172);
  fadeToBlackBy(leds3, NUM_LEDS, 64);
  FastLED.show();
  if (toggle) {
    pos3 = (pos3 + 4) % NUM_LEDS3;
  }
  toggle = !toggle;
  delay(.2);
}
