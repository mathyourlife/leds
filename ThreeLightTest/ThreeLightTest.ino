// Import the FastLED library so we can use it to control the lights.
#include <FastLED.h>

// Specify which digital IO port the data wire from the LED strip
// will be connected to.
#define LED_PIN     7

// Specify how many LEDs on the strip will be controlled.
#define NUM_LEDS    10

// Specify the light brightness from 0-255.  If too bright, you
// can permanently damage the arduino, so use a small number to start.
#define BRIGHTNESS  100

// Specify the color order of the LEDs. It differs by type of LED strip
// and could be RGB, RBG, BRG, GBR, ...
// Use ThreeLightTest to determine the correct order.
#define COLOR_ORDER GRB

// LED chipset type.
#define CHIPSET     WS2812B

// Create a variable that will store the colors for the LEDs.
CRGB leds[NUM_LEDS];

void setup() {
    // Configure the FastLED library to the LED strip.
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);

    // clear all pixel data
    FastLED.clear(true);

    // Set the brightness
    FastLED.setBrightness(BRIGHTNESS);

    // Protect the Arduino from drawing too much current to power
    // the LEDs via the USB.
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
}

void loop() {
    // Set the first LED to red.
    leds[0] = CRGB::Red;

    // Set the second LED to green.
    leds[1] = CRGB::Green;

    // Set the third LED to blue.
    leds[2] = CRGB::Blue;

    // Send the color instructions to the LED strip.
    FastLED.show();
}
