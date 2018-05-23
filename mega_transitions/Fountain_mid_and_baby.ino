#include "FastLED.h"

/*
Large Kudu Pins : 44, 45
Medium Kudu Pins: 2, 4, 6, 8, 10, 12
Small Kudu Pins : 3, 5, 7, 9, 11, 13
*/

// Lengths of physical LED strips
#define LRG_KUDU_VERTICAL_LINE_LEDS 27
#define NUM_LRG_KUDU_VERTICAL_LINES 3

#define LRG_KUDU_HORI_RING_LEDS     35
#define NUM_LRG_KUDU_HORI_RINGS     2

#define LEN_MED_KUDU_V_LINE         13

// Lengths of virtual LED strips
#define NUM_LRG_KUDU_VERTICAL_LEDS  LRG_KUDU_VERTICAL_LINE_LEDS * NUM_LRG_KUDU_VERTICAL_LINES
#define NUM_LRG_KUDU_HORI_LEDS      LRG_KUDU_HORI_RING_LEDS * NUM_LRG_KUDU_HORI_RINGS
#define NUM_MEDIUM_KUDU_LEDS        78

#define NUM_BABY_KUDU_LEDS          13

// create arrays
CRGB a_largeKuduVertical[NUM_LRG_KUDU_VERTICAL_LEDS];
CRGB a_largeKuduHorizontal[NUM_LRG_KUDU_HORI_LEDS];
CRGB a_mediumKudu[NUM_MEDIUM_KUDU_LEDS];
CRGB a_babyKudu[NUM_BABY_KUDU_LEDS];

// Timers
#define PATTERN_TIME     5000
#define TRANS_TIME       3000 // transition time
#define TRANS_STEPS      10 // number of steps in transition
#define TRANS_STEP_TIME  TRANS_TIME/TRANS_STEPS

class StripColors
{
    public:
        StripColors(CRGB largeH, CRGB largeV, CRGB medium, CRGB baby)
        : largeHori_(largeH), largVert_(largeV), medium_(medium), baby_(baby)
        {
        }

        StripColors() {}

        StripColors(const StripColors& rsh)
        {
            largeHori_ = rsh.largeHori_;
            largVert_ = rsh.largVert_;
            medium_ = rsh.medium_;
            baby_ = rsh.baby_;
        }

        StripColors& operator=(const StripColors& ref)
        {
            largeHori_ = ref.largeHori_;
            largVert_ = ref.largVert_;
            medium_ = ref.medium_;
            baby_ = ref.baby_;
            
            return *this;            
        }

        StripColors& operator+=(const StripColors& addon)
        {
            largeHori_ += addon.largeHori_;
            largVert_ += addon.largVert_;
            medium_ += addon.medium_;
            baby_ += addon.baby_;
            
            return *this;
        }        

    CRGB largeHori_;
    CRGB largVert_;
    CRGB medium_;
    CRGB baby_;
};


CRGB a_clrs [] = {
    {154, 196, 3},
    {3, 140, 186},
    {189, 0, 145},
    {94, 199, 2},
    {2, 82, 186},
    {189, 0, 85},
    {20, 199, 0},
    {0, 11, 166},
    {153, 0, 15},
    {107, 1, 153},
    {166, 120, 5},
    {4, 140, 97},
    {3, 0, 153},
    {166, 8, 3},
    {2, 143, 2},
    {2, 156, 156},
    {166, 5, 163},
    {143, 141, 3},
    {30, 158, 47},
    {54, 34, 166},
    {143, 41, 28},
    {102, 163, 27},
    {30, 105, 166},
    {143, 24, 93}/*,

    {191, 0, 10},
    {22, 176, 2},
    {197, 3, 219},
    {214, 3, 189},
    {230, 53, 4},
    {4, 255, 121},
    {7, 0, 204},
    {219, 0, 0},
    {3, 212, 7},
    {184, 46, 0},
    {0, 184, 46},
    {46, 0, 184},
    {111, 2, 212},
    {230, 116, 2},
    {5, 219, 112},
    {214, 11, 0},
    {3, 212, 17},
    {17, 204, 0},

    {255, 232, 25},
    {25, 71, 255},
    {255, 25, 152},
    {160, 26, 255},
    {255, 26, 72},
    {89, 186, 20},
    {94, 255, 19},
    {180, 19, 255},
    {207, 12, 45},
    {224, 19, 255},
    {255, 19, 35},
    {50, 255, 19},
    {255, 151, 23},
    {23, 232, 255},
    {189, 15, 140}*/
};

const int gi_NumColors = sizeof(a_clrs)/sizeof(CRGB);

// --------------------------------------------------------------------------------
void setup()
{
    // Large Kudu vertical strip
    FastLED.addLeds<WS2811, 44, RBG>(a_largeKuduVertical, NUM_LRG_KUDU_VERTICAL_LEDS);

    // Large Kudu horizontal strip
    FastLED.addLeds<WS2811, 45, RBG>(a_largeKuduHorizontal, NUM_LRG_KUDU_HORI_LEDS);

    // Medium Kudu (6 pins: 2, 4, 6, 8, 10, 12)
    FastLED.addLeds<WS2811, 2, RBG>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<WS2811, 4, RBG>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<WS2811, 6, RBG>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<WS2811, 8, RBG>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<WS2811, 10, RBG>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<WS2811, 12, RBG>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);        

    // Baby Kudu (6 pins: 2, 4, 6, 8, 10, 12)
    FastLED.addLeds<WS2811, 3, RBG>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<WS2811, 5, RBG>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<WS2811, 7, RBG>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<WS2811, 9, RBG>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<WS2811, 11, RBG>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<WS2811, 13, RBG>(a_babyKudu, NUM_BABY_KUDU_LEDS);
}

// --------------------------------------------------------------------------------
void loop()
{
    transition3by3();
}

void transition3by3()
{
  byte i = 2;
  while(i < gi_NumColors)
  {
        showColorPattern(StripColors(a_clrs[i-2], a_clrs[i-2], a_clrs[i-1], a_clrs[i]));
        delay(PATTERN_TIME);

        fountainEffectMediumKudu(CRGB(192, 192, 192));
        fountainEffectBabyKudu(CRGB(192, 192, 192));
        delay(PATTERN_TIME);
        i += 3;
  }
}


// --------------------------------------------------------------------------------
void fountainEffectMediumKudu(const CRGB& effectColor_)
{
    CRGB originalColor = a_mediumKudu[0];

    // move to the new color
    for (byte i = 0; i < LEN_MED_KUDU_V_LINE; ++i)
    {
        a_mediumKudu[i] = effectColor_; // 0 - 12
        a_mediumKudu[i + 2 * LEN_MED_KUDU_V_LINE] = effectColor_; // 26 - 38
        a_mediumKudu[i + 4 * LEN_MED_KUDU_V_LINE] = effectColor_; // 52 - 64

        a_mediumKudu[2 * LEN_MED_KUDU_V_LINE - i - 1] = effectColor_; // 25 - 13
        a_mediumKudu[4 * LEN_MED_KUDU_V_LINE - i - 1] = effectColor_; // 51 - 39
        a_mediumKudu[6 * LEN_MED_KUDU_V_LINE - i - 1] = effectColor_; // 77 - 65

        FastLED.show();
        delay(200);
    }
    
    delay(300);

    // restore the original color
    // We have to do this in the opposite direction
    for (byte i = LEN_MED_KUDU_V_LINE - 1; i >= 0; --i)
    {
        a_mediumKudu[i] = originalColor; // 12 - 0
        a_mediumKudu[2 * LEN_MED_KUDU_V_LINE + i] = originalColor; // 38 - 26
        a_mediumKudu[4 * LEN_MED_KUDU_V_LINE + i] = originalColor; // 64 - 52

        a_mediumKudu[2 * LEN_MED_KUDU_V_LINE - i - 1] = originalColor; // 13 - 25
        a_mediumKudu[4 * LEN_MED_KUDU_V_LINE - i - 1] = originalColor; // 39 - 51
        a_mediumKudu[6 * LEN_MED_KUDU_V_LINE - i - 1] = originalColor; // 65 - 77

        FastLED.show();
        delay(200);
    }
}

// --------------------------------------------------------------------------------
void fountainEffectBabyKudu(const CRGB& effectColor_)
{
    CRGB originalColor = a_babyKudu[0];

    // move to the new color
    for (byte i = 0; i < 13; ++i)
    {
        a_babyKudu[i] = effectColor_; // 0 - 12
        FastLED.show();
        delay(200);
    }

    delay(300);

    // restore the original color
    // We have to do this in the opposite direction
    for (byte i = 12; i >= 0; --i)
    {
        a_babyKudu[i] = originalColor; // 12 - 0
        FastLED.show();
        delay(200);
    }
}

// --------------------------------------------------------------------------------
void showColorPattern(const StripColors& colors)
{
    fill_solid(a_largeKuduVertical, NUM_LRG_KUDU_VERTICAL_LEDS, colors.largVert_);
    fill_solid(a_largeKuduHorizontal, NUM_LRG_KUDU_HORI_LEDS, colors.largeHori_);
    fill_solid(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS, colors.medium_);
    fill_solid(a_babyKudu, NUM_BABY_KUDU_LEDS, colors.baby_);

    FastLED.show();
}

