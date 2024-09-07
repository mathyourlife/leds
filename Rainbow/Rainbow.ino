// Import the FastLED library so we can use it to control the lights.
#include <FastLED.h>

// Specify which digital IO port the data wire from the LED strip
// will be connected to.
#define LED_PIN  7

// Specify how many LEDs on the strip will be controlled.
#define NUM_LEDS 144

// Create a variable that will store the colors for the LEDs.
CRGB leds[NUM_LEDS];
uint8_t hue = 0;

void setup() {
    // Tell the FastLED library:
    //   * WS2812B - which type of LEDs will be controlled
    //   * LED_PIN - which pin to send out the data signal
    //   * RGB - the color order. It differs by type of LED strip
    //           and could be RGB, RBG, BRG, GBR, ...
    //   * leds - the variable that is storing all the colors
    //   * NUM_LEDS - the number of LEDs to control
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

    // clear all pixel data
    FastLED.clear(true);

    // Set the light brightness from 0-255.  If too bright, you
    // can permanently damage the arduino, so use a small number to start.
    FastLED.setBrightness(100);

    // Protect the Arduino from drawing too much current to power
    // the LEDs via the USB.
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
}

void loop() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i / 2), 255, 255);
    }
    EVERY_N_MILLISECONDS(25) {
        hue++; // hue will wrap around in the 0-255 range
    }

    // Send the color instructions to the LED strip.
    FastLED.show();
}
