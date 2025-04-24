#include <FastLED.h>

#define NUM_LEDS 144

#define DATA_PIN 7
#define DATA_PIN2 6
#define DATA_PIN3 5
#define CLOCK_PIN 13

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

// Define the pin numbers
const int inputPin = 2;    // Pin for the digital input (e.g., a button)
const int ledPin = 7;
const int ledPin2 = 6;
const int ledPin3 = 5;

void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, DATA_PIN2, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, DATA_PIN3, RGB>(leds, NUM_LEDS);

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
  int inputState = 1; // digitalRead(inputPin);

  if(inputState>0){
  // Set the LED state to the same as the input state
    digitalWrite(ledPin, inputState);
    digitalWrite(ledPin2, inputState);
    digitalWrite(ledPin3, inputState);

  // Move a single white led 
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 3) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(.5);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;

      // Print the input state to the Serial Monitor
      Serial.print("Input state: ");
      Serial.println(inputState);
      delay(.5);
      digitalWrite(ledPin, 0);
      digitalWrite(ledPin2, 0);
      digitalWrite(ledPin3, 0);
   }
  }
}