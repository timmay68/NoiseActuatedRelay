
//Listens to room noise on analogue mic.If the roomNoiseLevel is  > ThresholdLevel it actuates the  relay
//Otherwise it sets the set to the relay to off and loops.
//Rotary should adjust the thresholdLevel

// Hardware setup:
// Attach a rotary encoder with output pins to D2 and D3.
// The common contact should be attached to ground.

#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RotaryEncoder encoder(2, 3); // create a RotaryEncoder object and specify the pins so as to adjust thresholdLevel

//Set relayPin Definition
const int relayPin = 8;    
//Set soundPin Definition
int soundPin = A0;
//Set roomNoiseLevel
int roomNoiseLevel = 0;
//Set digitalSoundPin
int digitalSoundPin = 7;

int thresholdLevel = 900;   //value is between 0 - 1023

// Define the pins used for the encoder
const int rotaryPin1 = 2; // CLK pin
const int rotaryPin2 = 3; // DT pin  
int rotaryCounter = 0;
// Define the initial position
//int rotaryPosition = (thresholdLevel);
#define ROTARYSTEPS 20
#define ROTARYMIN roomNoiseLevel +20   //So that turning it down too far does not set off relay
#define ROTARYMAX 1000  //max value

// Last known rotary position.
int lastPos = -1;

// SETUP    
void setup() 
{

    encoder.setPosition(thresholdLevel); // or enter a value between 0 - 1023
    pinMode (relayPin, OUTPUT);
    digitalWrite (relayPin, HIGH); //ensure the relay is off on start
    pinMode(rotaryPin1, INPUT_PULLUP);
    pinMode(rotaryPin2, INPUT_PULLUP);
	
	  //attachInterrupt(rotaryPin1, threshold_isr, CHANGE);
    
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Set Up Completed");
    delay (5000);
    lcd.clear(); //clear screen

}

// LOOP  
void loop() 
{
 
 //encoder
 encoder.tick();
  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition() * ROTARYSTEPS;
  //Set encoder pos to min if found to be < rotarymin
  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;
  //Set encoder pos to Max if found to be > rotarymax
  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  } 

  if (lastPos != newPos) {
    lastPos = newPos;
    delay(50); // debounce the encoder
  //Print the new position/current threshold
  lcd.clear(); //clear screen
  lcd.setCursor(0,0);
  lcd.print("Threshold:");
  lcd.setCursor(12, 0);
  lcd.print(newPos);
  }

//Start Polling
     // Continuously poll for a noise that > roomNoiseLevel
    roomNoiseLevel = analogRead(soundPin);  //read the value of the soundPin

  if (roomNoiseLevel > thresholdLevel)
  {
    lcd.clear(); //clear screen
    lcd.setCursor(0,0);
    lcd.print("Executing!"); //msg to screen line 1
    lcd.setCursor(0,1);
    lcd.print(roomNoiseLevel); // Print roomNoiseLevel //msg to screen line 2
    digitalWrite (relayPin, LOW); //execute relay
    delay(5000); //holding test switch down for 5 secs
    digitalWrite (relayPin, HIGH); //release switch 
    lcd.clear(); //clear screen
    //Serial.print("Disarming.");
    lcd.setCursor(0,0);
    lcd.print("Disarming..."); //msg to screen line 1
    lcd.setCursor(0, 1);
    lcd.print("Listening"); //msg to screen line 2
    delay(2000);
  }
  else {
    digitalWrite (relayPin, HIGH); //ensure the relay is off
    //delay(3000); 
    //lcd.print(roomNoiseLevel); // Print roomNoiseLevel
    lcd.setCursor(0, 1);
    lcd.print("Noise Level:");
    lcd.setCursor(13, 1);
    lcd.print(roomNoiseLevel); // Print roomNoiseLevel
  }
}//end loop


//start isr
void threshold_isr() {
//  when all ISR content/functions are left in the loop the rotary encoder works and it adjusts the thresholdLevel.  It does not work when put here in ISR and attach.. is activated in SetUp
  
}//end ISR 



