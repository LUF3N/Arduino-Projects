/*
#####################################################################################################
# Arduino Sound2Light by Steffen Hildebrand                                                         #
# You can edit marked variables ("editable") if you like to change color, speed or other stuff      #
# Have fun!                                                                                         #
#####################################################################################################
*/

//basic settings
//libraries you need to install
#include <Adafruit_NeoPixel.h>
//data pin for WS2812b LEDS (editable), must be digitial
#define PIN 13
//data pin for mircophone (editable), must be analog
#define APIN A0
//LED count (editable)
#define NOL 200
//set your LED brightness (editable)
#define BRIGHTNESS 255
//set count of "shots" (editable), as more you use as more laggy it get 
#define NRSHOTS 60


uint32_t shotColor;
uint32_t otherColor1;
uint32_t otherColor2;
uint32_t otherColor3;
int positionen[NRSHOTS];


//set your strip settings (editable), should work fine without changes
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NOL, PIN, NEO_GRB + NEO_KHZ800);


void initPositionen() {
  for (int i = 0; i < NRSHOTS; i++) positionen[i] = -1;
}

void setup() {
//set your "shot" colors, this right now is kind of orange yellow
  shotColor = strip.Color(255, 63, 0);
  otherColor1 = strip.Color(255, 83, 0);
  otherColor2 = strip.Color(255, 113, 0);
  otherColor3 = strip.Color(255, 123, 0);


  randomSeed(analogRead(1));
  initPositionen();
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
  initPositionen();
}


void alloff() {
  for (int i=0; i<NOL;i++) {
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}

void shotframe(int position) {
  strip.setPixelColor(position, shotColor);
  strip.setPixelColor(position -1, otherColor1);
  strip.setPixelColor(position -2, otherColor2);
  strip.setPixelColor(position -3, otherColor3);
}

void shots(){
  for (int i=0; i<NRSHOTS;i++) {
    if (positionen[i]!=-1)
    {
      shotframe(positionen[i]);
    } 
  }
}


void moveshot() {
  for (int i=0; i<NRSHOTS;i++) {
    if (positionen[i]>=NOL) {
      positionen[i]=-1;    
    }
    if (positionen[i]!=-1)
    {
      positionen[i] = positionen[i]+1;
    } 
    
  }
}

void startshot() {
  for (int i=0; i<NRSHOTS;i++) {
    if (positionen[i]==-1)
    {
      positionen[i]=0;
      break;
    }
  }
}

void loop() {
  int Sound = analogRead(APIN); 
  //you can change the "400" if your mic is using other data areas
  if (Sound > 400) { 
    startshot();
    
  }
  alloff();
  moveshot();
  shots();
  strip.show();
  //change the speed! if its still to slow just delete the delay... it will still be delayed because arduinos are sloowwwww
  delay(40); 
}
