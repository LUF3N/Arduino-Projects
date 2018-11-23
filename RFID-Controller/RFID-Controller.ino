/* 
###################################################################################################################################################################
#      _____    ______   _____   _____        __  _____           _           _             _____                   _                    _   _                    #
#      |  __ \  |  ____| |_   _| |  __ \      / / |  __ \         | |         (_)           / ____|                 | |                  | | | |                  #
#      | |__) | | |__      | |   | |  | |    / /  | |__) |   ___  | |   __ _   _   ______  | |        ___    _ __   | |_   _ __    ___   | | | |   ___   _ __     #
#      |  _  /  |  __|     | |   | |  | |   / /   |  _  /   / _ \ | |  / _` | | | |______| | |       / _ \  | '_ \  | __| | '__|  / _ \  | | | |  / _ \ | '__|    #
#      | | \ \  | |       _| |_  | |__| |  / /    | | \ \  |  __/ | | | (_| | | |          | |____  | (_) | | | | | | |_  | |    | (_) | | | | | |  __/ | |       #
#      |_|  \_\ |_|      |_____| |_____/  /_/     |_|  \_\  \___| |_|  \__,_| |_|           \_____|  \___/  |_| |_|  \__| |_|     \___/  |_| |_|  \___| |_|       #
#                                                           with LED status monitor By Steffen Hildebrand (1.0)                                                   #
###################################################################################################################################################################
*/
//===Variablen und Defines===
// RFID-Cards (Admin Keys)
#define CARD1 2563480 //Steffen
#define CARD2 2340590 //Beschriftet C2
#define CARD3 1
#define CARD4 1
#define CARD5 1

// RFID-Reader
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
float code;

// LED-Monitor
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 8, NEO_GRB + NEO_KHZ800);
int realLed = 0;

//Selection
int countActions = 1;

//Activation
boolean action1 = false;
boolean action2 = false;
boolean action3 = false;
boolean action4 = false;
boolean action5 = false;
boolean action6 = false;
boolean action7 = false;
boolean action8 = false;
boolean action9 = false;

//Actions
boolean publicMode = false;
boolean adminKey = false;
int p = 0; //For Pin toggle off

//===Setup und Loop===
void setup() {
  //RFID
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  //pin define
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  //reset data pins to off
  for(p=0; p<=7; p++) {
    digitalWrite(p, LOW);
    Serial.println(p);
  }
  
  //turn first LED on at start
  strip.begin();
  strip.setPixelColor(0, 0, 0, 100);
  strip.show(); 
  delay(500);

}

void loop() {
     ledTable();
     RFIDcompare();
     strip.show();
}



//===Funktionen===
void RFIDcheck() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    //Serial.println("PICC_IsNewCardPresent returned"); 
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  code=0;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    code=((code+mfrc522.uid.uidByte[i])*10);
  }
  Serial.print("RFID-Tag der genutzten Karte: ");
  Serial.println(code);
}

void RFIDcompare() {
  RFIDcheck();
  if (code==CARD1 or code==CARD2 or code==CARD3 or code==CARD4 or code==CARD5) {
    Serial.println("Der genutzte Tag hat Admin Berechtigungen!");
    adminKey = true;
    RFIDtime();
  }
  if (publicMode==true && code!=0) {
    Serial.println("Der genutzte Tag hat keine Admin Berechtigungen!");
    adminKey = false;
    RFIDtime();
  }
}

void RFIDtime() {
    code = 0;
    delay(500);
    mfrc522.PCD_AntennaOff();
    delay(50);
    RFIDcheck();
    mfrc522.PCD_AntennaOn();
    Serial.print("Vorhalte Dauer: ");
    if (mfrc522.PICC_IsNewCardPresent()) {
      Serial.println("Lang");
      activation();
    }
    else {
      Serial.println("Kurz");
      selector();
      strip.show();
      delay(500);
    }
  }

void selector() {
  countActions++;
    if (countActions==10) {
    countActions = 1;
  }
  realLed = countActions-1;
  strip.setPixelColor(realLed, 0, 0, 100);
  //strip.setPixelColor(realLed-1, 0, 0, 0);
  Serial.print("LED Nummer: ");
  Serial.println(realLed);
}

void activation() {
  if (countActions==1) {
    if (action1 == false) {
      action1 = true;
      digitalWrite(0, HIGH);
    }
    else {
      action1 = false;
      digitalWrite(0, LOW);
    }
  }

  
  if (countActions==2) {
    if (action2 == false) {
      action2 = true;
      digitalWrite(1, HIGH);
    }
    else {
      action2 = false;
      digitalWrite(1, LOW);
    }
  }

  
  if (countActions==3) {
    if (action3 == false) {
      action3 = true;
      digitalWrite(2, HIGH);
    }
    else {
      action3 = false;
      digitalWrite(2, LOW);
    }
  }

  
  if (countActions==4) {
    if (action4 == false) {
      action4 = true;
      digitalWrite(3, HIGH);
    }
    else {
      action4 = false;
      digitalWrite(3, LOW);
    }
  }

  
  if (countActions==5) {
    if (action5 == false) {
      action5 = true;
      action6 = false;
      action7 = false;
      action8 = false;
      digitalWrite(4, HIGH);
    }
    else {
      action5 = false;
      digitalWrite(4, LOW);
    }
  }

  
  if (countActions==6) {
    if (action6 == false) {
      action6 = true;
      action5 = false;
      action7 = false;
      action8 = false;
      digitalWrite(5, HIGH);
    }
    else {
      action6 = false;
      digitalWrite(5, LOW);
    }
  }

  
  if (countActions==7) {
    if (action7 == false) {
      action7 = true;
      action5 = false;
      action6 = false;
      action8 = false;
      digitalWrite(6, HIGH);
    }
    else {
      action7 = false;
      digitalWrite(6, LOW);
    }
  }

  
  if (countActions==8) {
    if (action8 == false) {
      action8 = true;
      action5 = false;
      action6 = false;
      action7 = false;
      digitalWrite(7, HIGH);
    }
    else {
      action8 = false;
      digitalWrite(7, LOW);
    }
  }

  
  if (countActions==9 && adminKey == true) {  //publicmode (aka NFC Mode)
    if (action9 == false) {
      action9 = true;
      publicMode=true;
      Serial.println("Publicmode wurde aktiviert! Er kann nur mit einem Adminkey deaktiviert werden!");      
    }
    else {
      action9 = false;
      publicMode=false;
      Serial.println("Publicmode wurde deaktiviert!");    
    }
  }
}

void ledTable() {
  if (action1 == true) strip.setPixelColor(0, 0, 100, 0); else strip.setPixelColor(0, 0, 0, 0);
  if (action2 == true) strip.setPixelColor(1, 0, 100, 0); else strip.setPixelColor(1, 0, 0, 0);
  if (action3 == true) strip.setPixelColor(2, 0, 100, 0); else strip.setPixelColor(2, 0, 0, 0);
  if (action4 == true) strip.setPixelColor(3, 0, 100, 0); else strip.setPixelColor(3, 0, 0, 0);
  if (action5 == true) strip.setPixelColor(4, 20, 100, 20); else strip.setPixelColor(4, 0, 0, 0);
  if (action6 == true) strip.setPixelColor(5, 20, 100, 20); else strip.setPixelColor(5, 0, 0, 0);
  if (action7 == true) strip.setPixelColor(6, 20, 100, 20); else strip.setPixelColor(6, 0, 0, 0);
  if (action8 == true) strip.setPixelColor(7, 20, 100, 20); else strip.setPixelColor(7, 0, 0, 0);
  if (action9 == true) strip.setPixelColor(8, 33, 122, 6); else strip.setPixelColor(8, 0, 0, 0);
}

