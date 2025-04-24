#include <FastLED.h>

#define NUM_LEDS 144
#define DATA_PIN 7
#define DATA_PIN2 6
#define DATA_PIN3 5
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

// Define the pin numbers
const int inputPin = 2;    // Pin for the digital input (e.g., a button)

uint8_t pos = 0;

void setup() {
  // Initialize LED strips
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(leds2, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN3, GRB>(leds3, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Initialize the input pin
  pinMode(inputPin, INPUT);

  // Start serial communication
  Serial.begin(9600);
  
  // Clear all LEDs at startup
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Read the state of the input pin
  int inputState = digitalRead(inputPin);

  if(inputState > 0) {
    // Fade all LEDs slightly
    fadeToBlackBy(leds, NUM_LEDS, 64);
    fadeToBlackBy(leds2, NUM_LEDS, 64);
    fadeToBlackBy(leds3, NUM_LEDS, 64);
    
    // Add bright pixels at current positions (all strips use the same position)
    leds[pos] = CRGB::Red;
    leds2[pos] = CRGB::Blue;
    leds3[pos] = CRGB::Green;
    
    // Blur the entire strips
    blur1d(leds, NUM_LEDS, 172);
    blur1d(leds2, NUM_LEDS, 172);
    blur1d(leds3, NUM_LEDS, 172);
    
    // Show the updated LEDs
    FastLED.show();
    
    // Move the position of the dot (all strips move together)
    pos = (pos + 4) % NUM_LEDS;
    
    Serial.print("Position: ");
    Serial.println(pos);
    
    delay(20);
  } else {
    if(pos > 0) {// Fade all LEDs slightly
    fadeToBlackBy(leds, NUM_LEDS, 64);
    fadeToBlackBy(leds2, NUM_LEDS, 64);
    fadeToBlackBy(leds3, NUM_LEDS, 64);
    
    // Add bright pixels at current positions (all strips use the same position)
    leds[pos] = CRGB::Red;
    leds2[pos] = CRGB::Blue;
    leds3[pos] = CRGB::Green;
    
    // Blur the entire strips
    blur1d(leds, NUM_LEDS, 172);
    blur1d(leds2, NUM_LEDS, 172);
    blur1d(leds3, NUM_LEDS, 172);
    
    // Show the updated LEDs
    FastLED.show();
    
    // Move the position of the dot (all strips move together)
    pos = (pos + 4) % NUM_LEDS;
    
    Serial.print("Position: ");
    Serial.println(pos);
    
    delay(20);
    }
    else {
      FastLED.clear();
      FastLED.show();
      delay(100);
    }
  }
}