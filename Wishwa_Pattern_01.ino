#include "FastLED.h"

/*
Large Kudu Pins : 44, 45
Medium Kudu Pins: 2, 4, 6, 8, 10, 12
Small Kudu Pins : 3, 5, 7, 9, 11, 13
*/

// Lengths of physical LED strips
#define LRG_KUDU_VERTICAL_LINE_LEDS 27
#define NUM_LRG_KUDU_VERTICAL_LINES 3

#define LRG_KUDU_HORI_RING_LEDS     36
#define NUM_LRG_KUDU_HORI_RINGS     2

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
#define PATTERN_TIME     10000 // 10 seconds
#define TRANS_TIME       5000 // transition time
#define TRANS_STEPS_PER_SEC 5 // Number of times color changes per second during transition from one color to the next  

// Calculated values from above
#define TRANS_STEP_INTERVAL 1000/TRANS_STEPS_PER_SEC
#define TRANS_STEPS TRANS_STEPS_PER_SEC * TRANS_TIME/1000

// strip type
enum eStripType
{
    LARGE_HORI,
    LARGE_VERT,
    MEDIUM,
    BABY,
    MAX_STRIPS
};

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


// colors
StripColors a_colors [] =   { 
                                { {192, 192, 192}, {192, 192, 192}, {0, 255, 0}, {0, 0, 255} },
                                { {51, 102, 255}, {51, 102, 255}, {255, 80, 80}, {102, 153, 0} },
                                { {0, 255, 255}, {0, 255, 255}, {255, 0, 255}, {255, 255, 0} },
                                { {0, 153, 51}, {0, 153, 51}, {77, 255, 255}, {255, 51, 0} },
                                { {255, 51, 0}, {255, 51, 0}, {255, 255, 0}, {153, 255, 51} }
                            };

const int g_iNumPatterns = sizeof(a_colors)/sizeof(StripColors);

void setup()
{
    // Large Kudu vertical strip
    FastLED.addLeds<NEOPIXEL, 44>(a_largeKuduVertical, NUM_LRG_KUDU_VERTICAL_LEDS);

    // Large Kudu horizontal strip
    FastLED.addLeds<NEOPIXEL, 45>(a_largeKuduHorizontal, NUM_LRG_KUDU_HORI_LEDS);

    // Medium Kudu (6 pins: 2, 4, 6, 8, 10, 12)
    FastLED.addLeds<NEOPIXEL, 2>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 4>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 6>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 8>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 10>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 12>(a_mediumKudu, NUM_MEDIUM_KUDU_LEDS);        

    // Baby Kudu (6 pins: 2, 4, 6, 8, 10, 12)
    FastLED.addLeds<NEOPIXEL, 3>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 5>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 7>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 9>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 11>(a_babyKudu, NUM_BABY_KUDU_LEDS);
    FastLED.addLeds<NEOPIXEL, 13>(a_babyKudu, NUM_BABY_KUDU_LEDS);
}

void loop()
{
    int i = 0;
    int iLimit = g_iNumPatterns - 1;

    // init color
    showColorPattern(a_colors[i]);
    delay(PATTERN_TIME);

    while (i < iLimit)
    {
        smoothTransitionColor(a_colors[i], a_colors[i+1]);
        delay(PATTERN_TIME);
        ++i;
    }
}

void smoothTransitionColor(const StripColors& fromColor, StripColors& toColor)
{
    StripColors stepColor;
    stepColor.largeHori_ = getColorStep(fromColor.largeHori_, toColor.largeHori_, TRANS_STEPS);
    stepColor.largVert_ = getColorStep(fromColor.largVert_, toColor.largVert_, TRANS_STEPS);
    stepColor.medium_ = getColorStep(fromColor.medium_, toColor.medium_, TRANS_STEPS);
    stepColor.baby_ = getColorStep(fromColor.baby_, toColor.baby_, TRANS_STEPS);

    StripColors nextColor(fromColor);
    for (int i = 0; i < TRANS_STEPS; ++i)
    {
        nextColor += stepColor;
        showColorPattern(nextColor);
        delay(TRANS_STEP_INTERVAL);
    }
}

void showColorPattern(const StripColors& colors)
{
    // large Kudu's vertical lines
    for (int i = 0; i < NUM_LRG_KUDU_VERTICAL_LEDS; ++i)
    {
        a_largeKuduVertical[i] = colors.largVert_;
    }

    // large Kudu's horizontal rings
    for (int i = 0; i < NUM_LRG_KUDU_HORI_LEDS; ++i)
    {
        a_largeKuduHorizontal[i] = colors.largeHori_;
    }
    
    // medium kudus
    for (int i = 0; i < NUM_MEDIUM_KUDU_LEDS; ++i)
    {
        a_mediumKudu[i] = colors.medium_;
    }

    // baby kudus
    for (int i = 0; i < NUM_BABY_KUDU_LEDS; ++i)
    {
        a_babyKudu[i] = colors.baby_;
    }

    FastLED.show();
}

CRGB getColorStep(const CRGB& from, const CRGB& to, int iSteps )
{
    CRGB ret;
    ret.r = from.r + (to.r - from.r)/iSteps;
    ret.g = from.g + (to.g - from.g)/iSteps;
    ret.b = from.b + (to.b - from.b)/iSteps;
    return ret;
}

