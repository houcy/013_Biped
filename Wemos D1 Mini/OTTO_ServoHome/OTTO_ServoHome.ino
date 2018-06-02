//----------------------------------------------------------------
// Code to put all 4 servos in home position (90 degrees)
//  - Adapted for Wemos D1
//-----------------------------------------------------------------
#include <Servo.h> 
#include <EEPROM.h>
#include <Otto.h>

Otto Otto;  //This is Otto!

//---------------------------------------------------------
//-- First step: Configure the pins where the servos are attached
/*
          --------------- 
         |     O   O     | o)) BZ D4
         |---------------|
YR D6==> |               | <== YL D5
          --------------- 
             ||     ||
RR D8==>   -----   ------  <== RL D7
          |-----   ------|
*/
  #define PIN_YL D5       // servo[0] Body left
  #define PIN_YR D6       // servo[1] Body right
  #define PIN_RL D7       // servo[2] Foot left
  #define PIN_RR D8       // servo[3] Foot right
  #define NOISESENSOR -1  // Not used
  #define BUZZER      D4  // Bzz bzz

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  //Set the servo pins
  bool load_calibration = true;
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,load_calibration, NOISESENSOR, BUZZER);
  Otto.sing(S_connection); //Otto wake up!
}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  Otto.home();
}
