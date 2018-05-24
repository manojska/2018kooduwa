#include <math.h>
#include <FastLED.h>
const int rButton = 2;
const int gButton = 4;
const int bButton = 8;

int rButtonState = 0;
int gButtonState = 0;
int bButtonState = 0;

int sensorPin = A0;
int sensorValue = 0;

#define NUM_LEDS 10
#define LED_PIN 3
CRGB leds[NUM_LEDS];

//initial RGB values
int ledR = 0;
int ledG = 0;
int ledB = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  //initialize neopixels
  //FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811,LED_PIN, BRG>(leds, NUM_LEDS);
  
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rButton, INPUT);
  pinMode(gButton, INPUT);
  pinMode(bButton, INPUT);

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  sensorValue = round(analogRead(sensorPin) * 255.0/1023.0);
  
  rButtonState = digitalRead(rButton);
  gButtonState = digitalRead(gButton);
  bButtonState = digitalRead(bButton);
  
  if (rButtonState == HIGH) {
    ledR = sensorValue;
    printRGB();
  }
  else if (gButtonState == HIGH) {
    ledG = sensorValue;
    printRGB();
  }
  else if (bButtonState == HIGH) {
    ledB = sensorValue;
    printRGB();
  }
  /* else {
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW

  } */
    fill_solid(leds, NUM_LEDS, CRGB(ledR, ledG, ledB));
    //fill_solid(leds, NUM_LEDS, CRGB::Green);
    //delay(1000);
    FastLED.show();
}

void printRGB() {
  Serial.print("R:t"); Serial.print(ledR); Serial.print("\tG:"); Serial.print(ledG); Serial.print("\tB:"); Serial.println(ledB); 
}

