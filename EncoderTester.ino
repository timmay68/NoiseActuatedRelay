#include "Arduino.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RotaryEncoder rotaryEncoder(2, 3); // create a RotaryEncoder object and specify the pins



int switchPin = 12;                        // button pin
int switchState = HIGH;                    // button value

int pinA = 2;                              // Rotary encoder Pin A
int pinB = 3;                              // Rotary encoder Pin B
int pinAstateCurrent = LOW;                // Current state of Pin A
int pinAStateLast = pinAstateCurrent;      // Last read value of Pin A


void setup() {
  Serial.begin (9600);                     // Initialise the serial monitor

  pinMode (switchPin, INPUT_PULLUP);       // Enable the switchPin as input with a PULLUP resistor

  //attachInterrupt(switchPin, threshold_isr, CHANGE);
  
  pinMode (pinA, INPUT);                   // Set PinA as input
  pinMode (pinB, INPUT);                   // Set PinB as input
      lcd.init();
    lcd.backlight();
  
  
}

void loop() {

  // BUTTON
  switchState = digitalRead(switchPin);    // Read the digital value of the switch (LOW/HIGH)

  // If the switch is pressed (LOW), print message
  if (switchState == LOW) {
      lcd.println("Switch pressed");
  }
  

  // ROTATION DIRECTION
  pinAstateCurrent = digitalRead(pinA);    // Read the current state of Pin A
  
  // If there is a minimal movement of 1 step
  if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) {
    
    if (digitalRead(pinB) == HIGH) {      // If Pin B is HIGH
      lcd.println("Left");             // Print on screen
    } else {
      lcd.println("Right");            // Print on screen
    }
    
  }
  
  pinAStateLast = pinAstateCurrent;        // Store the latest read value in the currect state variable
  
}
