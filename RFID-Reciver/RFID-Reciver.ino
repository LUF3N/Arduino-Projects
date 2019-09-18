//RFID-Reciver by Steffen Hildebrand
//===Variablen und Defines===
#include <Adafruit_NeoPixel.h>

//Pins
boolean state1;
boolean state2;
boolean state3;
boolean state4;
boolean state5;
boolean state6;
boolean state7;
boolean state8;

//segments
int segmentStart1 = 0;
int segmentStart2 = 4;
int segmentStart3 = 8;
int segmentStart4 = 12;
int segmentFullCount = 15;

//efects
int randomR;
int randomG;
int randomB;
int standartDelay = 50;

//adafruit
Adafruit_NeoPixel strip = Adafruit_NeoPixel(segmentFullCount+1, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop() {
  pinCheck();
  effectSelector();
}

void randomGen () {
  Serial.println("New colors!");
  randomR = random(0, 255);
  randomG = random(0, 255);
  randomB = random(0, 255);
}




//===funtions===
void pinCheck() {
  state1 = digitalRead(2);
  state2 = digitalRead(3);
  state3 = digitalRead(4);
  state4 = digitalRead(5);
  state5 = digitalRead(6);
  state6 = digitalRead(7);
  state7 = digitalRead(8);
  state8 = digitalRead(9);

  Serial.println("------------Pin Stat------------");
  //segment
  Serial.println(state1);
  Serial.println(state2);
  Serial.println(state3);
  Serial.println(state4);
  //effects
  Serial.println(state5);
  Serial.println(state6);
  Serial.println(state7);
  Serial.println(state8);
  Serial.println("--------------------------------");
}
void effectSelector() {
  if (state5) effectOne();
  else if (state6) effectTwo();
  else if (state7) effectThree();
  else if (state8) effectFour();
}
void effectOne() {
  randomGen();
  if (state1) {
      for (int i=segmentStart1; i <= segmentStart2-1; i++){
        strip.setPixelColor(i, randomR, randomG, randomB);
        delay(standartDelay);
    }
    strip.show();
  }
  else {
      for (int i=segmentStart1; i <= segmentStart2-1; i++){
        strip.setPixelColor(i, 0, 0, 0);
        delay(standartDelay);
    }
    strip.show();
  }
  
  if (state2) {
      for (int i=segmentStart2; i <= segmentStart3-1; i++){
       strip.setPixelColor(i, randomR, randomG, randomB);
       delay(standartDelay);
    }
    strip.show();
  }
  else {
      for (int i=segmentStart2; i <= segmentStart3-1; i++){
        strip.setPixelColor(i, 0, 0, 0);
        delay(standartDelay);
    }
    strip.show();
  }
  
  if (state3) {
      for (int i=segmentStart3; i <= segmentStart4-1; i++){
        strip.setPixelColor(i, randomR, randomG, randomB);
        delay(standartDelay);
    }
    strip.show();
  }
  else {
      for (int i=segmentStart3; i <= segmentStart4-1; i++){
        strip.setPixelColor(i, 0, 0, 0);
        delay(standartDelay);
    }
    strip.show();
  }
  
  if (state4) {
      for (int i=segmentStart4; i <= segmentFullCount; i++){
       strip.setPixelColor(i, randomR, randomG, randomB);
       delay(standartDelay);
    }
    strip.show();
  }
  else {
      for (int i=segmentStart4; i <= segmentFullCount; i++){
        strip.setPixelColor(i, 0, 0, 0);
        delay(standartDelay);
    }
    strip.show();
  }
}

void effectTwo() {
  randomGen();
  if (state1) {
      for (int i=segmentStart1; i <= segmentStart2-1; i++){
        strip.setPixelColor(i, randomR, randomG, randomB);
        strip.show();
        delay(standartDelay);
    }
  }
  else {
      for (int i=segmentStart1; i <= segmentStart2-1; i++){
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(standartDelay);
    }
  }
  
  if (state2) {
      for (int i=segmentStart2; i <= segmentStart3-1; i++){
       strip.setPixelColor(i, randomR, randomG, randomB);
       strip.show();
       delay(standartDelay);
    }
  }
  else {
      for (int i=segmentStart2; i <= segmentStart3-1; i++){
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(standartDelay);
    }
  }
  
  if (state3) {
      for (int i=segmentStart3; i <= segmentStart4-1; i++){
        strip.setPixelColor(i, randomR, randomG, randomB);
        strip.show();
        delay(standartDelay);
    }
  }
  else {
      for (int i=segmentStart3; i <= segmentStart4-1; i++){
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(standartDelay);
    }
  }
  
  if (state4) {
      for (int i=segmentStart4; i <= segmentFullCount; i++){
       strip.setPixelColor(i, randomR, randomG, randomB);
       strip.show();
       delay(standartDelay);
    }
  }
  else {
      for (int i=segmentStart4; i <= segmentFullCount; i++){
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(standartDelay);
    }
  }
}

void effectThree() {
  
}  


void effectFour() {
  
}



























