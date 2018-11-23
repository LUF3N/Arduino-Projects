/* 
###################################################################################################################################################################
#      _____    ______   _____   _____        __  _____           _           _             _____                   _                    _   _                    #
#      |  __ \  |  ____| |_   _| |  __ \      / / |  __ \         | |         (_)           / ____|                 | |                  | | | |                  #
#      | |__) | | |__      | |   | |  | |    / /  | |__) |   ___  | |   __ _   _   ______  | |        ___    _ __   | |_   _ __    ___   | | | |   ___   _ __     #
#      |  _  /  |  __|     | |   | |  | |   / /   |  _  /   / _ \ | |  / _` | | | |______| | |       / _ \  | '_ \  | __| | '__|  / _ \  | | | |  / _ \ | '__|    #
#      | | \ \  | |       _| |_  | |__| |  / /    | | \ \  |  __/ | | | (_| | | |          | |____  | (_) | | | | | | |_  | |    | (_) | | | | | |  __/ | |       #
#      |_|  \_\ |_|      |_____| |_____/  /_/     |_|  \_\  \___| |_|  \__,_| |_|           \_____|  \___/  |_| |_|  \__| |_|     \___/  |_| |_|  \___| |_|       #
#                                                           with LED status monitor By Steffen Hildebrand (0.6)                                                   #
###################################################################################################################################################################
*/

// RFID-Cards
#define CARD1 1121830
#define CARD2 1
#define CARD3 1
#define CARD4 1
#define CARD5 1

// RFID-Reader
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// LED-Monitor
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 8, NEO_GRB + NEO_KHZ800);

// RELAI
int selectstatus = 0;
int relaicount = 0;
float code;

#define RELAI_1 6
#define RELAI_2 7 
#define RELAI_3 8 
#define RELAI_4 9
#define RELAI_5 10
#define RELAI_6 11
#define RELAI_7 12
#define RELAI_8 13

int relai_1_toggle = 0;
int relai_2_toggle = 0;
int relai_3_toggle = 0;
int relai_4_toggle = 0;
int relai_5_toggle = 0;
int relai_6_toggle = 0;
int relai_7_toggle = 0;
int relai_8_toggle = 0;

// LEDs
int LED_0_blue_toggle = 0;
int LED_1_blue_toggle = 0;
int LED_2_blue_toggle = 0;
int LED_3_blue_toggle = 0;
int LED_4_blue_toggle = 0;
int LED_5_blue_toggle = 0;
int LED_6_blue_toggle = 0;
int LED_7_blue_toggle = 0;

int LED_0_green_toggle = 0;
int LED_1_green_toggle = 0;
int LED_2_green_toggle = 0;
int LED_3_green_toggle = 0;
int LED_4_green_toggle = 0;
int LED_5_green_toggle = 0;
int LED_6_green_toggle = 0;
int LED_7_green_toggle = 0;

int sleeptimer = 0;
int UNTILSLEEP = 3000;





// Functions
                                                                                                                                  
void RELAIpindefine() { 
  for (int RELAI = 0; RELAI <= 7; RELAI++) {
    pinMode(RELAI, OUTPUT);
  }
}


void RELAIturnoff() {
  for (int RELAI = 0; RELAI <= 7; RELAI++) {
    digitalWrite(RELAI, HIGH);
  }
}

void RFIDcheck() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    //erial.println("PICC_IsNewCardPresent returned"); 
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  code=0;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    code=((code+mfrc522.uid.uidByte[i])*10);
  }
}




void RFIDtime() {
  RFIDcheck();
  if (code==CARD1 or code==CARD2 or code==CARD3 or code==CARD4 or code==CARD5) {
    code = 0;
    delay(500);
    mfrc522.PCD_AntennaOff();
    delay(50);
    RFIDcheck();
    mfrc522.PCD_AntennaOn();
    if (mfrc522.PICC_IsNewCardPresent()) {
      selectstatus = 1;
      delay(1000);
    }
    else {
      selectstatus=2;
      delay(500);
    }
  }
}

void LEDdraw() {
  strip.setPixelColor(0, 0, LED_0_green_toggle, LED_0_blue_toggle);
  strip.setPixelColor(1, 0, LED_1_green_toggle, LED_1_blue_toggle);
  strip.setPixelColor(2, 0, LED_2_green_toggle, LED_2_blue_toggle);
  strip.setPixelColor(3, 0, LED_3_green_toggle, LED_3_blue_toggle);
  strip.setPixelColor(4, 0, LED_4_green_toggle, LED_4_blue_toggle);
  strip.setPixelColor(5, 0, LED_5_green_toggle, LED_5_blue_toggle);
  strip.setPixelColor(6, 0, LED_6_green_toggle, LED_6_blue_toggle);
  strip.setPixelColor(7, 0, LED_7_green_toggle, LED_7_blue_toggle);
  strip.show();
}

void RELAIselect() {
  if (selectstatus==2) {
    selectstatus=0;

    if (relaicount==0) {
      LED_7_blue_toggle = 0;
      LED_0_blue_toggle = 120;
    }
    if (relaicount==1) {
      LED_0_blue_toggle = 0;
      LED_1_blue_toggle = 120;
    }
    if (relaicount==2) {
      LED_1_blue_toggle = 0;
      LED_2_blue_toggle = 120;
    }
    if (relaicount==3) {
      LED_2_blue_toggle = 0;
      LED_3_blue_toggle = 120;
    }
    if (relaicount==4) {
      LED_3_blue_toggle = 0;
      LED_4_blue_toggle = 120;
    }
    if (relaicount==5) {
      LED_4_blue_toggle = 0;
      LED_5_blue_toggle = 120;
    }
    if (relaicount==6) {
      LED_5_blue_toggle = 0;
      LED_6_blue_toggle = 120;
    }
    if (relaicount==7) {
      LED_6_blue_toggle = 0;
      LED_7_blue_toggle = 120;
    } 
    relaicount++;
    if (relaicount>=9) {
      relaicount=0;
    }
  }
  
  
  if (selectstatus==1) {
    selectstatus=0;

    if (relaicount==1) {
      if (relai_1_toggle==0) {
        LED_0_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_1_toggle=1;
        }
        else {
          LED_0_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_1_toggle=0;
        }
    }
    if (relaicount==2) {
      if (relai_2_toggle==0) {
        LED_1_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_2_toggle=1;
        }
        else {
          LED_1_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_2_toggle=0;
        }
    }
    if (relaicount==3) {
      if (relai_3_toggle==0) {
        LED_2_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_3_toggle=1;
        }
        else {
          LED_2_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_3_toggle=0;
        }
    }
    if (relaicount==4) {
      if (relai_4_toggle==0) {
        LED_3_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_4_toggle=1;
        }
        else {
          LED_3_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_4_toggle=0;
        }
    }
    if (relaicount==5) {
      if (relai_5_toggle==0) {
        LED_4_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_5_toggle=5;
        }
        else {
          LED_4_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_5_toggle=0;
        }
    }
    if (relaicount==6) {
      if (relai_6_toggle==0) {
        LED_5_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_6_toggle=1;
        }
        else {
          LED_5_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_6_toggle=0;
        }
    }
    if (relaicount==7) {
      if (relai_7_toggle==0) {
        LED_6_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_7_toggle=1;
        }
        else {
          LED_6_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_7_toggle=0;
        }
    }
    if (relaicount==8) {
      if (relai_8_toggle==0) {
        LED_7_green_toggle = 120;
        Serial.println(relaicount + "ON");
        relai_8_toggle=1;
        }
        else {
          LED_7_green_toggle = 0;
          Serial.println(relaicount + "OFF");
          relai_8_toggle=0;
        }
    } 
  }
  LEDdraw();
}

// Setup
void setup() {

  //RFID
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  //pin define
  RELAIpindefine();
  
  //turn off at start
  strip.begin();
  strip.show();
  RELAIturnoff();  
}



  void loop() {
     RFIDtime();
     RELAIselect();
     //LEDdraw();
  }

