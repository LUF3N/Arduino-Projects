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

//Pins
int p = 2;
int stat1;
int stat2;
int stat3;
int stat4;
int stat5;
int stat6;
int stat7;
int stat8;










void setup() {
  Serial.begin(9700);
  
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
  delay(1000);
}

void pinCheck() {
  stat1 = digitalRead(2);
  stat2 = digitalRead(3);
  stat3 = digitalRead(4);
  stat4 = digitalRead(5);
  stat5 = digitalRead(6);
  stat6 = digitalRead(7);
  stat7 = digitalRead(8);
  stat8 = digitalRead(9);

  
  Serial.println("------------Pin Stat------------");
  Serial.println(stat1);
  Serial.println(stat2);
  Serial.println(stat3);
  Serial.println(stat4);
  Serial.println(stat5);
  Serial.println(stat6);
  Serial.println(stat7);
  Serial.println(stat8);
  Serial.println("--------------------------------");
}

