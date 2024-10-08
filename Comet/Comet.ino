// Import the FastLED library so we can use it to control the lights.
#include <FastLED.h>

// Specify which digital IO port the data wire from the LED strip
// will be connected to.
#define LED_PIN     7

// Specify how many LEDs on the strip will be controlled.
// Max 637 for arduino uno memory
#define NUM_LEDS    637

// Specify the color order of the LEDs. It differs by type of LED strip
// and could be RGB, RBG, BRG, GBR, ...
// Use ThreeLightTest to determine the correct order.
#define COLOR_ORDER GRB

// LED chipset type.
#define CHIPSET     WS2812B

// Set the light brightness from 0-255.  If too bright, you
// can permanently damage the arduino, so use a small number to start.
#define BRIGHTNESS  50

// Set power limits to prevent damaging the Vout pin if powering the
// lights from the arduino. 5V 400mA are safe defaults for the Arduino.
// Higher values can be used if powering the lights from an external
// power supply.
#define MAX_VOLTS   5
#define MAX_CURRENT_MILLIAMPS 400


#define DIRECTION_OUT true
#define DIRECTION_IN  false

// Create a variable that will store the colors for the LEDs.
CRGB leds[NUM_LEDS];

// How quickly the comet tail dims out. Larger values dim the tail
// faster and make it shorter. Suggested range 200-1000
#define DIMMING  750

void setup() {
    // Configure the FastLED library to the LED strip.
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

    // clear all pixel data
    FastLED.clear(true);

    FastLED.setBrightness(BRIGHTNESS);

    FastLED.setMaxPowerInVoltsAndMilliamps(MAX_VOLTS, MAX_CURRENT_MILLIAMPS);
}

void loop() {
    static uint8_t location[2] = {NUM_LEDS / 4, NUM_LEDS / 3};
    static uint8_t speed[2] = {1, 1};
    static bool direction[2] = {DIRECTION_IN, DIRECTION_OUT};
    static int from, to;

    EVERY_N_MILLISECONDS(10) {
        // TODO: add variability to the fading by pixel.
        fadeToBlackBy(leds, NUM_LEDS, 30);
        for (int i = 0; i < 2; i++) {
            if (direction[i]) {
                if (location[i] + speed[i] >= NUM_LEDS) {
                    direction[i] = DIRECTION_IN;
                }
            } else {
                if (location[i] - speed[i] < 0) {
                    direction[i] = DIRECTION_OUT;
                }
            }

            if( random8() < 2) {
                direction[i] = !direction[i];
            }

            from = location[i];
            if (direction[i]) {
                location[i] += speed[i];
            } else {
                location[i] -= speed[i];
            }

            // For speeds greater than 1, color in all the pixels
            // between the last position and the new position.
            if (location[i] > from) {
                to = location[i];
            } else {
                to = from;
                from = location[i];
            }
            for (int i = from; i <= to; i++) {
                leds[i] = CRGB::White;
            }
        }
    }

    // Send the color instructions to the LED strip.
    FastLED.show();
}
