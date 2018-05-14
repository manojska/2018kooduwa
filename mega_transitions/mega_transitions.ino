#include <FastLED.h>

/* for Arduino Mega
*  Level 0 - Loku Kooduwa
*  Leval 1 - midle
*  level 2 - baby
*  
*  
*/
#define LEVEL_0_VLEDS 0 // Level 0 virticle LEDS
#define LEVEL_0_HLEDS 0 // Level 0 Horizontal LEDS
#define LEVEL_1_LEDS 78 // Level 1 is middle Kooduwa
#define LEVEL_2_LEDS 13 // Level 2 is baby Kooduwa
#define SIDE_LENGTH 13 // legnth of level 1 side

CRGB level_0v[LEVEL_0_VLEDS]; // LED Array for level 0 verticle
CRGB level_0h[LEVEL_0_HLEDS]; // LED Array for level 0 horizontal

CRGB level_1[LEVEL_1_LEDS]; // LED Array for level 1
CRGB level_2[LEVEL_2_LEDS]; // LED Array for level 2



// CRGB leds[NUM_LEDS];
DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
 0,     0,  255,  0,   //Blue
50,    255,  0,  215,   //Yellow
100,   255, 0,  0,   //Red
150,   200, 200,  200,   //white
200,   253, 2,  106,   //bright yellow
255,   255,255,255 }; //full white

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL,2>(level_1, LEVEL_1_LEDS);
  FastLED.addLeds<NEOPIXEL,3>(level_2, LEVEL_2_LEDS);

  FastLED.addLeds<NEOPIXEL,4>(level_1, LEVEL_1_LEDS);
  FastLED.addLeds<NEOPIXEL,5>(level_2, LEVEL_2_LEDS);

  FastLED.addLeds<NEOPIXEL,6>(level_1, LEVEL_1_LEDS);
  FastLED.addLeds<NEOPIXEL,7>(level_2, LEVEL_2_LEDS);

  FastLED.addLeds<NEOPIXEL,8>(level_1, LEVEL_1_LEDS);
  FastLED.addLeds<NEOPIXEL,9>(level_2, LEVEL_2_LEDS);

  FastLED.addLeds<NEOPIXEL,10>(level_1, LEVEL_1_LEDS);
  FastLED.addLeds<NEOPIXEL,11>(level_2, LEVEL_2_LEDS);

  FastLED.addLeds<NEOPIXEL,12>(level_1, LEVEL_1_LEDS);
  FastLED.addLeds<NEOPIXEL,13>(level_2, LEVEL_2_LEDS);
  
  FastLED.addLeds<NEOPIXEL,44>(level_0v, LEVEL_0_VLEDS);
  FastLED.addLeds<NEOPIXEL,45>(level_0h, LEVEL_0_HLEDS);
  
}

void loop() {
  //FastLED.setBrightness(192);
   colorBoom(CRGB(192, 192, 192));
   colorBoom(CRGB::Red);
   colorBoom(CRGB::Green);
   colorBoom(CRGB::Blue);
  // spreadFromMiddle(CRGB::Red);
  colorBoom(CRGB(148, 211, 0));
  
  colorBoom(CRGB(255, 0, 140));
 
  for (byte x = 0; x < 10; x++) {
    colorConsume(CRGB::Red);
    delay(5000);
    colorConsume(CRGB::Blue);
    delay(5000);
    colorConsume(CRGB(148, 211, 0));
    delay(5000);
  }    
 
}


void colorConsume(CRGB new_color) {
  //set the new color from the bottom and dim the old color little by litle
  // first work on level2 next level 1
  int anime_delay = 20;
  uint8_t dim_level = 192;
  for (byte i =0; i < SIDE_LENGTH; i++) {
    level_1[i] = CRGB::White;
    for (byte j = i+1; j < SIDE_LENGTH; j++) {
      level_1[j].nscale8_video(dim_level);
      level_1[2 * SIDE_LENGTH -1 - j].nscale8_video(dim_level);
      level_1[2 * SIDE_LENGTH + j].nscale8_video(dim_level);
      level_1[4 * SIDE_LENGTH -1 - j].nscale8_video(dim_level);
      level_1[4 * SIDE_LENGTH + j].nscale8_video(dim_level);
      level_1[4 * SIDE_LENGTH - j].nscale8_video(dim_level);
    }
    FastLED.show(); delay(anime_delay);
    level_1[i] = new_color;
    level_1[2 * SIDE_LENGTH - 1 - i] = new_color;
    level_1[2 * SIDE_LENGTH + i] = new_color;
    level_1[4 * SIDE_LENGTH - 1 - i] = new_color;
    level_1[4 * SIDE_LENGTH + i] = new_color;
    level_1[6 * SIDE_LENGTH -1 - i] = new_color;
    FastLED.show(); delay(anime_delay);
  }
}

void colorBoom( CRGB new_color) {
  // fade current color and boom into next color
  // reduce current color to 75% for 100 times
  for (int steps =0; steps < 50; steps++) {
    for (int i = 0; i < LEVEL_2_LEDS; i++) {
        level_2[i].nscale8_video(192);
   }
  FastLED.show();
  delay(5); 
  }
  fill_solid(level_2, LEVEL_2_LEDS, new_color);
  FastLED.show();
  // now change color on leve 1 
 for (int steps =0; steps < 100; steps++) {
    for (int i = 0; i < LEVEL_1_LEDS; i++) {
        level_1[i].nscale8_video(192);
   }
  FastLED.show();
  delay(5); 
  }
  fill_solid(level_1, LEVEL_1_LEDS, new_color);
  FastLED.show();
  
  delay(3000);
}

