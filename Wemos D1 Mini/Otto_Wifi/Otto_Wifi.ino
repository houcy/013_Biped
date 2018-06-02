#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
const char* ssid = "Telstra00F027";
const char* pass =  "yrtqbgr9fann";
//----------------------------------------------------------------
//-- Basic Otto´s setup
//-- You can add functions, gestures or sounds in loop
//-- https://github.com/OttoDIY
//-- CC BY SA (http://ottodiy.com)
//-- 04 December 2016
//-- Adapted Pablo García pabloeweb@gmail.com 01 May 2017
//-----------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
Otto Otto;  //This is Otto!
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         ---------------
        |     O   O     |
        |---------------|
  YR 3==> |               | <== YL 2
         ---------------
            ||     ||
  RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
#define PIN_YL D5 //servo[2]
#define PIN_YR D6 //servo[3]
#define PIN_RL D7 //servo[4]
#define PIN_RR D8 //servo[5]
#define USTrigger D2 //Trigger on D2
#define USEcho D3 //Echo on Trigger D3
/*SOUNDS******************
   S_connection  S_disconnection  S_buttonPushed S_mode1 S_mode2 S_mode3 S_surprise S_OhOoh  S_OhOoh2  S_cuddly
   S_sleeping  S_happy S_superHappy S_happy_short S_sad S_confused S_fart1 S_fart2  S_fart3
*/
/*MOVEMENTS LIST**************
   dir=1---> FORWARD/LEFT
   dir=-1---> BACKWARD/RIGTH
   T : amount of movement. HIGHER VALUE SLOWER MOVEMENT usually 1000 (from 600 to 1400)
   h: height of mov. around 20
     jump(steps=1, int T = 2000);
     walk(steps, T, dir);
     turn(steps, T, dir);
     bend (steps, T, dir); //usually steps =1, T=2000
     shakeLeg (steps, T, dir);
     updown(steps, T, HEIGHT);
     swing(steps, T, HEIGHT);
     tiptoeSwing(steps, T, HEIGHT);
     jitter(steps, T, HEIGHT); (small T)
     ascendingTurn(steps, T, HEIGHT);
     moonwalker(steps, T, HEIGHT,dir);
     crusaito(steps, T, HEIGHT,dir);
     flapping(steps, T, HEIGHT,dir);
  /*GESTURES LIST***************
  OttoHappy OttoSuperHappy  OttoSad   OttoSleeping  OttoFart  OttoConfused OttoLove  OttoAngry
  OttoFretful OttoMagic  OttoWave  OttoVictory  OttoFail*/
///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
bool obstacleDetected = false;
int distance = 0;

void handleFWD() {
  Serial.println("FWD");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.walk(2, 1000, 1); //2 steps FORWARD

}
void handleBACK() {
  Serial.println("BACK");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.walk(2, 1000, -1); 

}
void handleRIGHT() {
  Serial.println("RIGHT");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.turn(2,1000,1);

}
void handleLEFT() {
  Serial.println("LEFT");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.turn(2,1000,-1);

}
void handleMOON() {
  Serial.println("Ooowwwww");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.moonwalker(3, 1000, 25, 1);

}

void handleHOME() {
  Serial.println("Ooowwwww");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.home();

}
void handleUPDOWN() {
  Serial.println("Ooowwwww");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.updown(1, 2000, 22);

}
void handleBEND() {
  Serial.println("Ooowwwww");
  String message;
  message += "{ \"success\": ";
  message += "1 }";
  server.send(200, "text/plain", message );
  Otto.bend (1, 2000, 1);

}

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/fwd", handleFWD);
  server.on("/back", handleBACK);
  server.on("/right", handleRIGHT);
  server.on("/left", handleLEFT);
  server.on("/moon", handleMOON);
  server.on("/home", handleHOME);
  server.on("/updown", handleUPDOWN);
  server.on("/bend", handleBEND);
  server.begin(); //Start the server

  //Set the servo pins
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true);
  Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
}
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
//--Uncomment lines or add you own-------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {

  server.handleClient();
  //comment uncomment if you need the clock displayed on the serial monitor
  //digitalClockDisplay();
  delay(100);
  //OBSTACLE MODE ON!!!!
  //obstacleMode();
  //          Otto.walk(2,1000,1); //2 steps FORWARD
  //          Otto.walk(2,1000,-1); //2 steps BACKSWARD
  //          //Otto.playGesture(OttoFretful);
  //          Otto.home();
  //          //Otto.sing(S_sleeping);
  //          delay(1000);
  //          Otto.turn(2,1000,1);//2 steps turning RIGHT
  //          delay(50);
  //          Otto.turn(2,1000,-1);//2 steps turning Left
  //          delay(50);
  //          Otto.moonwalker(3, 1000, 25, 1);
  //          Otto.home();
  //          Otto.bend (1, 2000, 1);
  //          Otto.home();
  //          Otto.ascendingTurn(1, 2000, 22);
  //          Otto.home();
  //          Otto.updown(1, 2000, 22);
  //          Otto.home();
  //
}

///////////////////////////////////////////////////////////////////
//-- Function to avoid obstacles
void obstacleMode() {
  distance = Otto.getDistance();
  if (distance < 15) {
    Otto.sing(S_surprise);
    Otto.walk(2, 1300, -1);
    Otto.turn(3, 1000, -1);
    delay(50);
  }
  else {
    Otto.walk(2, 1000, 1);
  }
}

