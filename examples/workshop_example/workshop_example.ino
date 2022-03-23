#include <steam_workshop_ledstrip.h>

// ** Change this number to be the number of LEDs on your strips
#define NUM_LEDS 6

// Different colors are made by mixing different amounts of
// Red, Green and Blue light.  The color wheel for light
// is different from mixing paint!
//
// Here are some RGB values for some common colors
#define RED     RGB(100,   0,   0)     // 100% red, 0% green, 0% blue
#define GREEN   RGB(  0, 100,   0)     // 0% red, 100% green, 0% blue
#define BLUE    RGB(  0,   0, 100)     // 0% red, 0% green, 100% blue
#define YELLOW  RGB(100, 100,   0)   // 100% red, 100% green, 0% blue
#define WHITE   RGB(100, 100, 100) // 100% of all colors
#define BLACK   RGB(  0,   0,   0)       // 0% of all colors (turns the LED off

// ** Can you figure out the values for these colors?
//#define LIGHTBLUE RGB(?, ?, ?)
//#define LIGHTPINK RGB(?, ?, ?)
//#define ORANGE RGB(?, ?, ?)
//#define CYAN RGB(?, ?, ?)
//#define PURPLE RGB(?, ?, ?)
//#define MAGENTA RGB(?, ?, ?)

// ** Make your own colors and see what happens!
//#define MYCOLOR1 RGB(?, ?, ?)
//#define MYCOLOR2 RGB(?, ?, ?)

// Put your main code here, to run repeatedly:
void loop() {

  // PRINT() shows a message in the Serial Monitor.
  // Open it under Tools -> Serial Monitor in the menu.
  PRINT("Showing colors");

  // SET(led, color) sets a pixel value to a color after SHOW() is called
  SET(1, RED);
  SET(2, BLUE);
  SET(3, GREEN);
  SET(4, BLACK);
  SET(5, WHITE);

  // SHOW() must be called for any changes with SET() to take effect.
  SHOW();

  // DELAY() waits the specified number of milliseconds
  // There are 1000 milliseconds in a second, so this call
  // waits 2 seconds before continuing
  DELAY(2000);

  PRINT("Turning off all LEDs on the strip");
  ALLOFF();
  DELAY(2000);

  // Make all LEDs cycle through the colors one at a time.
  PRINT("Showing Rainbow with 20ms between colors");
  RAINBOW(20);

  // PRINT("Rainbow Cycle with 10ms between colors");
  // RAINBOWCYCLE(10);

  // PRINT("Chase a light down the strip");
  // THEATERCHASE(GREEN, 100);

  // PRINT("Theater Chase 2 with delay of 100 ms between blinks");
  // THEATERCHASE2(GREEN, BLUE, 100);

  // PRINT("Theater Chase 3 with delay of 100 ms between blinks");
  // THEATERCHASE3(RED, WHITE, BLUE, 100);

  // PRINT("Theater Chase Rainbow with 20ms between colors");
  // THEATERCHASERAINBOW(20);


  // MYSTERY1(color)
  //   color - the color to use in the mystery effect
  // MYSTERY1(?)

  // MYSTERY2(color, wait)
  //   color - the color to use in the mystery effect
  //   wait - The number of milliseconds to wait between blinking the LEDs
  // MYSTERY2(?, ?);

  // Mystery function 3. What could it be?!?
  // MYSTERY3();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
//       YOU DO NOT NEED TO EDIT BELOW THIS COMMENT FOR THE WORKSHOP... 
//       MIGHT BREAK SOMETHING.
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


// Hook up the Digital input of the strip to pin D6 if PIN is set to 6
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// setup() is called once when the Arduino boots up (or the reset button is pressed)
void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
  delay(500);

  Serial.println("Initializing Neopixel");
  delay(500);
  strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  Serial.println("Turning brightness to 50");
  delay(500);
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}



// RAINBOW(wait)
// Make all LEDs on the strip move change colors at the same time.
//   wait - The number of milliseconds to wait between changing colors from 0 to 255
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, colorWheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// RAINBOWCYCLE(wait)
// Slightly different from RAINBOW(), this makes the rainbow equally distributed throughout
//  wait - The number of milliseconds to wait between changing colors
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on colorWheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, colorWheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// THEATERCHASE(color, wait)
// Theatre-style crawling lights.
//  color - The color to use for the LEDs
//  wait - The number of milliseconds to wait between turning the LEDs on and off.
void theaterChase(uint32_t color, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, color);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// THEATERCHASE2(color1, color2, wait)
// Theatre-style crawling lights with two colors
//   color1 - The color to use for the first LED in the pattern
//   color2 - The color to use for the second LED in the pattern
//   wait - The number of milliseconds to wait between turning the LEDs on and off.
void theaterChase2(uint32_t color1, uint32_t color2, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, color1);
        strip.setPixelColor(i + q + 1, color2);
      }
      strip.show();
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// THEATERCHASE2(color1, color2, color3, wait)
// Theatre-style crawling lights with tghree colors
//   color1 - The color to use for the first LED in the pattern
//   color2 - The color to use for the second LED in the pattern
//   color3 - The color to use for the third LED in the pattern
//   wait - The number of milliseconds to wait between turning the LEDs on and off.
void theaterChase3(uint32_t color1, uint32_t color2, uint32_t color3, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 4; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 4) {
        strip.setPixelColor(i + q, color1);
        strip.setPixelColor(i + q + 1, color2);
        strip.setPixelColor(i + q + 2, color3);
      }
      strip.show();
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 4) {
        strip.setPixelColor(i + q, 0);      // turn every fourth pixel off
      }
    }
  }
}

// THEATERCHASERAINBOW(wait)
// Theatre-style crawling lights with rainbow effect
//   wait - The number of milliseconds to wait between turning the LEDs on and off.
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the colorWheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, colorWheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// MYSTERY1(color)
// Mystery function?!?
//   color - the color to use in the mystery effect
void mystery1(uint32_t color) {
  strip.clear();
  strip.show();

  uint8_t r, g, b;
  uint8_t s = 0;
  uint8_t v = 0;
  uint16_t h = 0;
  unpackColor(color, r, g, b);
  RGBtoHSV(r, g, b, h, s, v);

  uint8_t wait = 500;
  uint8_t center_led = strip.numPixels() / 2;
  uint8_t num_loops = 50;

  // Blink the center LED with increasing intensity and frequency
  for (int i = 0; i < num_loops; i++) {
    strip.setPixelColor(center_led, 0);
    strip.show();
    delay((num_loops - i) * (wait / (num_loops)));

    // Make the intensity of the light increase on each loop
    uint8_t intensity =  i * (v / num_loops);
    Serial.println(intensity);
    strip.setPixelColor(center_led, HSVtoRGB(h, s, intensity));
    strip.show();
    delay(wait - (i * (wait / num_loops)));
  }

  // Fade in each LED starting from the center going out.
  wait = 2000;
  num_loops = 25;
  for (int i = 1; i < center_led; i++) {
    for (int j = 0; j < num_loops; j++) {
      uint8_t intensity = j * (100 / num_loops);
      strip.setPixelColor(center_led - i, HSVtoRGB(h, s, intensity));
      strip.setPixelColor(center_led + i, HSVtoRGB(h, s, intensity));
      strip.show();
      delay(wait / num_loops);
    }
  }

  // Make sure the entire strip is lit
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(center_led + i, color);
  }
  strip.show();
  delay(500);

  // Fade out each led starting from the center going outwards
  for (int i = 0; i < center_led; i++) {
    for (int j = 0; j < num_loops; j++) {
      uint8_t intensity = 100 - j * (100 / num_loops);
      strip.setPixelColor(center_led - i, HSVtoRGB(h, s, intensity));
      strip.setPixelColor(center_led + i, HSVtoRGB(h, s, intensity));
      strip.show();
      delay(wait / num_loops);
    }
    strip.setPixelColor(center_led - i, strip.Color(0, 0, 0));
    strip.setPixelColor(center_led + i, strip.Color(0, 0, 0));
  }

  strip.clear();
  strip.show();
  delay(1000);
}

// MYSTERY2(color, wait)
// Mystery function?!?
//   color - the color to use in the mystery effect
//   wait - The number of milliseconds to wait between turning the LEDs on and off.
void mystery2(uint32_t color, uint16_t wait) {
  strip.clear();
  strip.show();

  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t s = 0;
  uint8_t v = 0;
  uint16_t h = 0;

  unpackColor(color, r, g, b);
  RGBtoHSV(r, g, b, h, s, v);

  uint8_t min = 255;
  uint8_t divisions = (strip.numPixels() * 2) + (strip.numPixels() / 2);
  float one_unit = 3.14 / (float)divisions;
  float pos_on_unit_circle = 0;
  float prev_pos = 0;

  for (int i = 0; i < 10; i++) {
    for (int offset = 0; offset < strip.numPixels(); offset++) {

      // Advance the wave one unit on the unit circle.
      prev_pos = pos_on_unit_circle = prev_pos + one_unit;
      for (int i = 0; i < strip.numPixels(); i++) {

        // Use the cosine function to set the intensity to get a wave effect
        uint8_t intensity = (uint8_t)(abs((cos(pos_on_unit_circle) * (float)v)));

        if (intensity < min && intensity > 0) {
          min = intensity;
        }
        // Clamp the lowest intensity so there are no LEDs that are off.
        if (intensity == 0) {
          intensity = min / 2;
        }
        strip.setPixelColor((i + offset) % strip.numPixels(), HSVtoRGB(h, s, intensity));
        pos_on_unit_circle += one_unit;
      }
      strip.show();
      delay(wait);
    }
  }
}

void mystery3() {
  uint8_t wait = 100;
  for (int i = 0; i < 10; i++) {

    // Move the light one way
    for (int p = 0; p < strip.numPixels(); p++) {
      strip.clear();
      strip.setPixelColor(p, strip.Color(255, 0, 0));
      if (p > 0) {
        strip.setPixelColor(p - 1, strip.Color(127, 0, 0));
        if (p > 1) {
          strip.setPixelColor(p - 2, strip.Color(30, 0, 0));
        }
      }
      strip.show();
      delay(wait);
    }

    // Move the light the opposite way
    for (int p = strip.numPixels() - 2; p > 0; p--) {
      strip.clear();
      strip.setPixelColor(p, strip.Color(255, 0, 0));

      if (p < strip.numPixels() - 1) {
        strip.setPixelColor(p + 1, strip.Color(127, 0, 0));
        if (p < strip.numPixels() - 2) {
          strip.setPixelColor(p + 2, strip.Color(30, 0, 0));
        }
      }
      strip.show();
      delay(wait);
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// Internal methods used to implement effects
////////////////////////////////////////////////////////////////////////////

// Unpack the individual R, G, B values from a 32 bit color value.
void unpackColor(uint32_t packed_color, uint8_t& R, uint8_t& G, uint8_t& B) {
  R = (packed_color >> 16) & 0xff;
  G = (packed_color >> 8) & 0xff;
  B = packed_color & 0xff;
}

/*! \brief Convert RGB to HSV color space

  Converts a given set of RGB values `r', `g', `b' into HSV
  coordinates. The input RGB values are in the range [0, 1], and the
  output HSV values are in the ranges h = [0, 360], and s, v = [0,
  1], respectively.

  \param R Red component, used as input, range: [0, 255]
  \param G Green component, used as input, range: [0, 255]
  \param B Blue component, used as input, range: [0, 255]
  \param H Hue component, used as output, range: [0, 360]
  \param S Hue component, used as output, range: [0, 100]
  \param V Hue component, used as output, range: [0, 100]

*/
void RGBtoHSV(uint8_t R, uint8_t G, uint8_t B,  uint16_t& H, uint8_t& S, uint8_t& V) {
  float fR = ((float)R) / 255.0;
  float fG = ((float)G) / 255.0;
  float fB = ((float)B) / 255.0;
  float fH = 0.0;
  float fS = 0.0;
  float fV = 0.0;
  float fCMax = max(max(fR, fG), fB);
  float fCMin = min(min(fR, fG), fB);
  float fDelta = fCMax - fCMin;

  if (fDelta > 0) {
    if (fCMax == fR) {
      fH = 60 * (fmod(((fG - fB) / fDelta), 6));
    } else if (fCMax == fG) {
      fH = 60 * (((fB - fR) / fDelta) + 2);
    } else if (fCMax == fB) {
      fH = 60 * (((fR - fG) / fDelta) + 4);
    }

    if (fCMax > 0) {
      fS = fDelta / fCMax;
    } else {
      fS = 0;
    }

    fV = fCMax;
  } else {
    fH = 0;
    fS = 0;
    fV = fCMax;
  }

  if (fH < 0) {
    fH = 360 + fH;
  }

  H = (int)fH;
  S = (int)(100.0 * fS);
  V = (int)(100.0 * fV);
}

// Convert from HSV to RGB color space
uint32_t HSVtoRGB(float H, float S, float V) {
  if (H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0) {
    Serial.println("HSVtoRGB: The givem HSV values are not in valid range");
    return;
  }
  float s = S / 100;
  float v = V / 100;
  float C = s * v;
  float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
  float m = v - C;
  float r, g, b;
  if (H >= 0 && H < 60) {
    r = C, g = X, b = 0;
  }
  else if (H >= 60 && H < 120) {
    r = X, g = C, b = 0;
  }
  else if (H >= 120 && H < 180) {
    r = 0, g = C, b = X;
  }
  else if (H >= 180 && H < 240) {
    r = 0, g = X, b = C;
  }
  else if (H >= 240 && H < 300) {
    r = X, g = 0, b = C;
  }
  else {
    r = C, g = 0, b = X;
  }
  int R = (r + m) * 255;
  int G = (g + m) * 255;
  int B = (b + m) * 255;
  return strip.Color(R, G, B);
}


// colorWheel()
// A shorthand way to get a different color from one byte.
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t colorWheel(byte colorWheelPos) {
  colorWheelPos = 255 - colorWheelPos;
  if (colorWheelPos < 85) {
    return strip.Color(255 - colorWheelPos * 3, 0, colorWheelPos * 3);
  }
  if (colorWheelPos < 170) {
    colorWheelPos -= 85;
    return strip.Color(0, colorWheelPos * 3, 255 - colorWheelPos * 3);
  }
  colorWheelPos -= 170;
  return strip.Color(colorWheelPos * 3, 255 - colorWheelPos * 3, 0);
}
