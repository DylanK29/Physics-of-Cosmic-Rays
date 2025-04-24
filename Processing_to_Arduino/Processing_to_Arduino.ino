 /// @file    FirstLight.ino
/// @brief   Animate a white dot moving along a strip of LEDs
/// @example FirstLight.ino
 
 #include <FastLED.h>
 
 char val; // Data received from the serial port
 int ledPin = 7; // Set the pin to digital I/O 7
 int whiteLed = 0;

// How many leds are in the strip?
#define NUM_LEDS 8

#define DATA_PIN 7
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

 void setup() {
   delay(2000);
   FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
   pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
   Serial.begin(9600); // Start serial communication at 9600 bps
 }


 void loop() {
    
   if (Serial.available()) 
   { // If data is available to read,
     val = Serial.read(); // read it and store it in val
   }
   if (val == '1')  
   { // If 1 was received
     for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(100);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
     }
   } else {
     leds[whiteLed] = CRGB::Black;
   }
   delay(10); // Wait 10 milliseconds for next reading
}