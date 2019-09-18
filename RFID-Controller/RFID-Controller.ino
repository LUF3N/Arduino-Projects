//RFID-Controller by Steffen Hildebrand
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
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
float code;

// LED-Monitor
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, 8, NEO_GRB + NEO_KHZ800);
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
boolean action9 = false; //public mode

//Actions
boolean publicMode = false;
boolean adminKey = false;
int p = 0; //For Pin toggle off

//Sleeptimer
int sleepTime = 500;
int sleepTimer = 0;
boolean isSleeping = false;

//===Setup und Loop===
void setup() {
  //RFID
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  //pin define
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);

  //reset data pins to off
  for(p=22; p<=7; p++) {
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
     SleepCheck();
}



//===Funktionen===

void SleepCheck() {
  if (code == 0 && isSleeping == false) {
    sleepTimer++;
    Serial.println(sleepTimer);
  }
  if (code != 0) {
    sleepTimer = 0;
    isSleeping = false;
    Serial.println(code);
    Serial.print("isSleeping=");
    Serial.println(isSleeping);
    Serial.println("sleeptimer reset");
    
  }
  if (sleepTimer >= sleepTime && isSleeping == false) {
    Serial.println("now sleeping");
    isSleeping = true;
  }
}

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
    SleepCheck();
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
    strip.setPixelColor(8, 0, 0, 0);
  }
  realLed = countActions-1;
  strip.setPixelColor(realLed, 0, 0, 100);
  strip.setPixelColor(realLed-1, 0, 0, 0);
  Serial.print("LED Nummer: ");
  Serial.println(realLed);
}

void activation() {
  if (countActions==1) {
    if (action1 == false) {
      action1 = true;
      digitalWrite(22, HIGH);
    }
    else {
      action1 = false;
      digitalWrite(22, LOW);
    }
  }

  
  if (countActions==2) {
    if (action2 == false) {
      action2 = true;
      digitalWrite(23, HIGH);
    }
    else {
      action2 = false;
      digitalWrite(23, LOW);
    }
  }

  
  if (countActions==3) {
    if (action3 == false) {
      action3 = true;
      digitalWrite(24, HIGH);
    }
    else {
      action3 = false;
      digitalWrite(24, LOW);
    }
  }

  
  if (countActions==4) {
    if (action4 == false) {
      action4 = true;
      digitalWrite(25, HIGH);
    }
    else {
      action4 = false;
      digitalWrite(25, LOW);
    }
  }

  
  if (countActions==5) {
    if (action5 == false) {
      action5 = true;
      action6 = false;
      action7 = false;
      action8 = false;
      digitalWrite(26, HIGH);
      digitalWrite(27, LOW);
      digitalWrite(28, LOW);
      digitalWrite(29, LOW);
    }
    else {
      action5 = false;
      digitalWrite(26, LOW);
    }
  }

  
  if (countActions==6) {
    if (action6 == false) {
      action6 = true;
      action5 = false;
      action7 = false;
      action8 = false;
      digitalWrite(27, HIGH);
      digitalWrite(28, LOW);
      digitalWrite(29, LOW);
      digitalWrite(26, LOW);
    }
    else {
      action6 = false;
      digitalWrite(27, LOW);
    }
  }

  
  if (countActions==7) {
    if (action7 == false) {
      action7 = true;
      action5 = false;
      action6 = false;
      action8 = false;
      digitalWrite(28, HIGH);
      digitalWrite(26, LOW);
      digitalWrite(27, LOW);
      digitalWrite(29, LOW);
    }
    else {
      action7 = false;
      digitalWrite(28, LOW);
    }
  }

  
  if (countActions==8) {
    if (action8 == false) {
      action8 = true;
      action5 = false;
      action6 = false;
      action7 = false;
      digitalWrite(29, HIGH);
      digitalWrite(26, LOW);
      digitalWrite(27, LOW);
      digitalWrite(28, LOW);
    }
    else {
      action8 = false;
      digitalWrite(29, LOW);
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
  if (isSleeping==false) {
      if (action1 == true) strip.setPixelColor(17, 0, 100, 0); else strip.setPixelColor(17, 0, 0, 0);
      if (action2 == true) strip.setPixelColor(16, 0, 100, 0); else strip.setPixelColor(16, 0, 0, 0);
      if (action3 == true) strip.setPixelColor(15, 0, 100, 0); else strip.setPixelColor(15, 0, 0, 0);
      if (action4 == true) strip.setPixelColor(14, 0, 100, 0); else strip.setPixelColor(14, 0, 0, 0);
      if (action5 == true) strip.setPixelColor(13, 255, 83, 0); else strip.setPixelColor(13, 0, 0, 0);
      if (action6 == true) strip.setPixelColor(12, 255, 83, 0); else strip.setPixelColor(12, 0, 0, 0);
      if (action7 == true) strip.setPixelColor(11, 255, 83, 0); else strip.setPixelColor(11, 0, 0, 0);
      if (action8 == true) strip.setPixelColor(10, 255, 83, 0); else strip.setPixelColor(10, 0, 0, 0);
      if (action9 == true) strip.setPixelColor(9, 255, 0, 0); else strip.setPixelColor(9, 0, 0, 0); 
  }
  if (isSleeping==true) {   
      strip.setPixelColor(17, 0, 0, 0);
      strip.setPixelColor(16, 0, 0, 0);
      strip.setPixelColor(15, 0, 0, 0);
      strip.setPixelColor(14, 0, 0, 0);
      strip.setPixelColor(13, 0, 0, 0);
      strip.setPixelColor(12, 0, 0, 0);
      strip.setPixelColor(11, 0, 0, 0);
      strip.setPixelColor(10, 0, 0, 0);
      strip.setPixelColor(9, 0, 0, 0);
      strip.setPixelColor(8, 0, 0, 0);
      strip.setPixelColor(7, 0, 0, 0);
      strip.setPixelColor(6, 0, 0, 0);
      strip.setPixelColor(5, 0, 0, 0);
      strip.setPixelColor(4, 0, 0, 0);
      strip.setPixelColor(3, 0, 0, 0);
      strip.setPixelColor(2, 0, 0, 0);
      strip.setPixelColor(1, 0, 0, 0);
      strip.setPixelColor(0, 0, 0, 0);
  }
}

