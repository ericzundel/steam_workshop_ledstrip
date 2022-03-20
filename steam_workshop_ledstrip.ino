#include "steam_workshop_ledstrip.h"

#define NUM_LEDS 16


#define RED     RGB(100, 0, 0)     // 100% red, 0% green, 0% blue
#define GREEN   RGB(0, 100, 0)     // 0% red, 100% green, 0% blue
#define BLUE    RGB(0, 0, 100)     // 0% red, 0% green, 100% blue
#define YELLOW  RGB(100, 100, 0)   // 100% red, 100% green, 0% blue
#define WHITE   RGB(100, 100, 100) // 100% of all colors
#define BLACK   RGB(0, 0, 0)       // 0% of all colors (turns the LED off


void loop() {
  // put your main code here, to run repeatedly:
  // testMacros();
  // testUnpackColor();
  // testRGBtoHSV();
  testMysteries();
}

void testMysteries() {
   mystery1(YELLOW);
   delay(1000);

   mystery1(strip.Color(255, 75, 220));
   delay(1000);

   mystery1(BLUE);
   delay(1000);
  
}

void testRGBtoHSV() {
  uint8_t r, g, b, s, v = 0;
  uint16_t h;

  uint32_t color = BLUE;
  unpackColor(color, r, g, b);
  RGBtoHSV(r, g, b, h, s, v);
  Serial.print("BLUE to HSV: "); 
  Serial.print(h); Serial.print(",");
  Serial.print(s); Serial.print(",");
  Serial.println(v);
  strip.setPixelColor(0, HSVtoRGB(h, s, v));
  strip.show();
  delay(1000);

  color = RED;
  unpackColor(color, r, g, b);
  RGBtoHSV(r, g, b, h, s, v);
  Serial.print("RED to HSV: "); 
  Serial.print(h); Serial.print(",");
  Serial.print(s); Serial.print(",");
  Serial.println(v);
  strip.setPixelColor(0, HSVtoRGB(h, s, v));
   strip.show();
  delay(1000);

  color = YELLOW;
  unpackColor(color, r, g, b);
  RGBtoHSV(r, g, b, h, s, v);
  Serial.print("YELLOW to HSV: "); 
  Serial.print(h); Serial.print(",");
  Serial.print(s); Serial.print(",");
  Serial.println(v);
  strip.setPixelColor(0, HSVtoRGB(h, s, v));
  strip.show();

  delay(1000);
  strip.clear();
  strip.show();
}

void testUnpackColor() {
  uint8_t red, green, blue = 0;
  unpackColor(RED, red, green, blue);
  Serial.print("RED: "); 
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(","); 
  Serial.println(blue);

  unpackColor(GREEN, red, green, blue);
  Serial.print("GREEN: "); 
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(","); 
  Serial.println(blue);
  
  unpackColor(BLUE, red, green, blue);
  Serial.print("BLUE: "); 
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(","); 
  Serial.println(blue);
  
  unpackColor(YELLOW, red, green, blue);
  Serial.print("YELLOW: "); 
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(","); 
  Serial.println(blue);
  
  unpackColor(WHITE, red, green, blue);
  Serial.print("WHITE: "); 
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(","); 
  Serial.println(blue);
  
  unpackColor(BLACK, red, green, blue);
  Serial.print("BLACK: "); 
  Serial.print(red); Serial.print(",");
  Serial.print(green); Serial.print(","); 
  Serial.println(blue);
 
}

void testMacros() {
  PRINT("Showing colors");
  SET(1, RED);
  SET(2, BLUE);
  SET(3, GREEN);
  SET(4, BLACK);
  SET(5, WHITE);
  SHOW();
  DELAY(2000);

  PRINT("Turning off all LEDs on the strip");
  ALLOFF();
  // Wait 2 seconds before continuing
  DELAY(2000);

  // Make all LEDs cycle through the colors one at a time.
  PRINT("Showing Rainbow with 20ms between colors");
  RAINBOW(20);

  //PRINT("Rainbow Cycle with 10ms between colors");
  //RAINBOWCYCLE(10);
  THEATERCHASE(GREEN, 100);

  PRINT("Theater Chase 2 with delay of 100 ms between blinks");
  THEATERCHASE2(GREEN, BLUE, 100);

  PRINT("Theater Chase 3 with delay of 100 ms between blinks");
  THEATERCHASE3(RED, WHITE, BLUE, 100);

  PRINT("Theater Chase Rainbow with 20ms between colors");
  THEATERCHASERAINBOW(20);
}


/////////////////////////////////////////////////////////////////////////////
//     DO NOT EDIT BELOW THIS LINE
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


// RAINBOW:
// Make all LEDs on the strip move change colors at the same tim.
// wait - numbe rof milliseconds to wait between changing colors from 0 to 255
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


// Slightly different, this makes the rainbow equally distributed throughout
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

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with two colors
void theaterChase2(uint32_t c1, uint32_t c2, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c1);
        strip.setPixelColor(i + q + 1, c2);
      }
      strip.show();
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with three colors
void theaterChase3(uint32_t c1, uint32_t c2, uint32_t c3, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 4; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 4) {
        strip.setPixelColor(i + q, c1);
        strip.setPixelColor(i + q + 1, c2);
        strip.setPixelColor(i + q + 2, c3);
      }
      strip.show();
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 4) {
        strip.setPixelColor(i + q, 0);      // turn every fourth pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
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

/*! \brief Convert RGB to HSV color space
  
  Converts a given set of RGB values `r', `g', `b' into HSV
  coordinates. The input RGB values are in the range [0, 1], and the
  output HSV values are in the ranges h = [0, 360], and s, v = [0,
  1], respectively.
  
  \param R Red component, used as input, range: [0, 255]
  \param G Green component, used as input, range: [0, 255]
  \param B Blue component, used as input, range: [0, 255]
  \param H Hue component, used as output, range: [0, 360]
  \param S Hue component, used as output, range: [0, 1]
  \param V Hue component, used as output, range: [0, 1]
  
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
  
  if(fDelta > 0) {
    if(fCMax == fR) {
      fH = 60 * (fmod(((fG - fB) / fDelta), 6));
    } else if(fCMax == fG) {
      fH = 60 * (((fB - fR) / fDelta) + 2);
    } else if(fCMax == fB) {
      fH = 60 * (((fR - fG) / fDelta) + 4);
    }
    
    if(fCMax > 0) {
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
  
  if(fH < 0) {
    fH = 360 + fH;
  }

  H = (int)fH;
  S = (int)(100.0 * fS);
  V = (int)(100.0 * fV);
}

void unpackColor(uint32_t packed_color, uint8_t& R, uint8_t& G, uint8_t& B) {
  R = (packed_color>>16) & 0xff;
  G = (packed_color>>8) & 0xff;
  B = packed_color & 0xff; 
}

uint32_t HSVtoRGB(float H, float S,float V){
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        Serial.println("HSVtoRGB: The givem HSV values are not in valid range");
        return;
    }
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;
    return strip.Color(R, G, B);
}

// Mystery function?!?
// Explosion from the middle of the strip
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

  Serial.println("mystery1() part 1");
  for (int i=0; i< num_loops; i++) {
    strip.setPixelColor(center_led, 0);
    strip.show();
    delay((num_loops - i) *(wait/(num_loops)));
    uint8_t dimmer_value =  i*(v/num_loops);
    Serial.println(dimmer_value);
    strip.setPixelColor(center_led, HSVtoRGB(h, s, dimmer_value));
    strip.show();
    delay(wait - (i*(wait/num_loops)));
  }

  Serial.println("mystery1() part 2");
  wait = 2000;
  num_loops = 25;
  for(int i=1; i<center_led; i++){
    for (int j=0; j<num_loops; j++) {
      uint8_t dimmer_value = j*(100/num_loops);
      strip.setPixelColor(center_led-i, HSVtoRGB(h, s, dimmer_value));
      strip.setPixelColor(center_led+i, HSVtoRGB(h, s, dimmer_value));
      strip.show();
      delay(wait/num_loops);
    }
  }
  
  for (int i=0; i< strip.numPixels(); i++) {
     strip.setPixelColor(center_led+i, color);
  }
  strip.show();
  delay(500);

  Serial.println("mystery1() part 3");
  for(int i=0; i<center_led; i++) {
    for (int j=0; j<num_loops; j++) {
      uint8_t dimmer_value = 100-j*(100/num_loops);
      strip.setPixelColor(center_led-i, HSVtoRGB(h, s, dimmer_value));
      strip.setPixelColor(center_led+i, HSVtoRGB(h, s, dimmer_value));
      strip.show();
      delay(wait/num_loops);
    }
    strip.setPixelColor(center_led-i, strip.Color(0, 0, 0));
    strip.setPixelColor(center_led+i, strip.Color(0, 0, 0));
  }

  strip.clear();
  strip.show();
  delay(1000);
}


// Ripple a color
void mystery2() {
  
}
