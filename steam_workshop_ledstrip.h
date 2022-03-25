#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Defined in steam_workshop_ledstrip.ino
extern  Adafruit_NeoPixel strip;


// Define Reg, Green, Blue colors using 0-100 values for each pixel
// Example values:
//   0 == off
//  50 == half brightness
// 100 == full on
#define RGB(color1, color2, color3) \
  strip.Color(((color1)*255)/100, ((color2)*255.0)/100, ((color3)*255)/100)


// These macro definitions are designed to make it easier for students to work.
// The idea is to allow for more fun and fewer compiler errors.
// These are shorter to type, allow for some variation in case
// They can leave off semicolons
#define SET(led_number, color) strip.setPixelColor((led_number)-1, (color));

#define SHOW() strip.show();

#define ALLOFF() strip.clear(); strip.show();

#define DELAY(arg) delay(arg);
#define PRINT(arg) Serial.println(arg);

#define RAINBOW(t) rainbow(t)
void rainbow(uint8_t wait);

#define RAINBOWCYCLE(t) rainbowCycle(t);
#define rainbowcycle(t) rainbowCycle(t);
void rainbowCycle(uint8_t wait);

#define THEATERCHASE(c, t) theaterChase(c, t);
#define theaterchase(c, t) theaterChase(c, t);
void theaterChase(uint32_t c, uint8_t wait); 

#define THEATERCHASE2(c1, c2, t) theaterChase2(c1, c2, t);
#define theaterchase2(c1, c2, t) theaterChase2(c1, c2, t);
void theaterChase2(uint32_t c1, uint32_t c2, uint8_t wait);  
  
#define THEATERCHASE3(c1, c2, c3, t) theaterChase3(c1, c2, c3, t);
#define theaterchase3(c1, c2, c3, t) theaterChase3(c1, c2, c3, t);
void theaterChase3(uint32_t c1, uint32_t c2, uint32_t c3, uint8_t wait);  

#define THEATERCHASERAINBOW(t) theaterChaseRainbow(t);
#define theaterchaserainbow(t) theaterChaseRainbow(t);
void theaterChaseRainbow(uint8_t wait);

#define MYSTERY1(color) mystery1(color);
void mystery1(uint32_t color);

#define MYSTERY2(color, wait) mystery2(color, wait);
void mystery2(uint32_t color, uint16_t wait);

#define MYSTERY3() mystery3();
void mystery3();

// Internal functions
void unpackColor(uint32_t packed_color, uint8_t& R, uint8_t& G, uint8_t& B);
uint32_t HSVtoRGB(float H, float S,float V);
void RGBtoHSV(uint8_t R, uint8_t G, uint8_t B,  uint16_t& H, uint8_t& S, uint8_t& V);
