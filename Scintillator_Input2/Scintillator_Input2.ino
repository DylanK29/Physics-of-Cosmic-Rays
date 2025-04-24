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

// Define the pin numbers
const int inputPin = 2;    // Pin for the digital input (e.g., a button)
const int ledPin = 7;
const int ledPin2 = 6;
const int ledPin3 = 5;

uint8_t pos = 0;
uint8_t pos2 = 0;
uint8_t pos3 = 0;
bool toggle = false;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(leds2, NUM_LEDS2);
  FastLED.addLeds<WS2812B, DATA_PIN3, GRB>(leds3, NUM_LEDS3);
  FastLED.setBrightness(BRIGHTNESS);

  // Initialize the input pin and the LED pin
  pinMode(inputPin, INPUT);   // Set the input pin as INPUT
  pinMode(ledPin, OUTPUT);    // Set the LED pin as OUTPUT
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Start serial communication
  Serial.begin(9600);         // Initialize serial communication at 9600 baud rate
}

void loop() {
  // Read the state of the input pin
  int inputState = 1; //digitalRead(inputPin);

  if(inputState>0){
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 4) {
    // Set the LED state to the same as the input state
    digitalWrite(ledPin, inputState);
    digitalWrite(ledPin2, inputState);
    digitalWrite(ledPin3, inputState);
  
    // Add a bright pixel that moves
    leds[pos] = CRGB::Red;
    leds2[pos2] = CRGB::Blue;
    leds3[pos3] = CRGB::Green;
    // Blur the entire strip
    blur1d(leds, NUM_LEDS, 172);
    blur1d(leds2, NUM_LEDS, 172);
    blur1d(leds3, NUM_LEDS, 172);
    fadeToBlackBy(leds, NUM_LEDS, 64);
    fadeToBlackBy(leds2, NUM_LEDS, 64);
    fadeToBlackBy(leds3, NUM_LEDS, 64);
    FastLED.show();
    // Move the position of the dot
    if (toggle) {
      pos = (pos + 5) % NUM_LEDS;
    }
    toggle = !toggle;
  
    if (toggle) {
      pos2 = (pos + 5) % NUM_LEDS2;
    }
    toggle = !toggle;
  
    if (toggle) {
      pos3 = (pos + 5) % NUM_LEDS3;
    }
    toggle = !toggle;
    }
    // Print the input state to the Serial Monitor
    Serial.print("Input state: ");
    Serial.println(inputState);
    delay(.5);
    digitalWrite(ledPin, 0);
    digitalWrite(ledPin2, 0);
    digitalWrite(ledPin3, 0);
  }
}
