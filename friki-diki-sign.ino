/***
 * Friki Diki LED Bar Sign
 * 
 * The pattern for our bar sign is fairly simple; it consists of two components:
 * 1. A sine wave with a hue gradient between peaks and valleys (where the second color is a hue offset of the main color)
 * 2. A linear hue shift that bounces from HUE_MIN to HUE_MAX (because the blue color range isn't as pretty)
 */
#include <Adafruit_NeoPixel.h>
#define PIN 1
#define NUM_LEDS 14
#define BRIGHTNESS 255
#define SECOND_HUE_OFFSET 10000
#define HUE_MIN 0
#define HUE_MAX 45000
#define HUE_STEP 1


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

uint64_t step = 0;
uint16_t hue_step = HUE_MIN;
int8_t hue_stepper = HUE_STEP;
float bMult[] = {0.4, 0.5, 0.6, 0.7, 0.9, 1.0, 1.0, 1.0, 1.0, 0.9, 0.7, 0.6, 0.5, 0.4}; // Brightness correction since we're illuminating a circle

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for (int x = 0; x < NUM_LEDS; x++) {
    float y = SECOND_HUE_OFFSET*sin(x/2.0+step*0.015)+SECOND_HUE_OFFSET;
    setPixelHSV(x, hue_step - y, 255, 255);
  }
  strip.show();
  step++;
  hue_step = hue_step + hue_stepper;
  if (hue_step <= HUE_MIN) { hue_stepper = HUE_STEP; }
  if (hue_step >= HUE_MAX) { hue_stepper = -HUE_STEP; }
  delay(15);
}

void setPixelHSV(uint16_t n, uint16_t hue, uint8_t sat, float val) {
  strip.setPixelColor(n, strip.gamma32(strip.ColorHSV(hue, sat, val*bMult[n])));
}
