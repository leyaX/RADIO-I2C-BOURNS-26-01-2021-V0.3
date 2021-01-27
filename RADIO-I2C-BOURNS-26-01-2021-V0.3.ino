//
// RADIO I2C with NiXiE's tubes 
//     2020-2021 - Ya -

#include <Arduino.h>
#include <Wire.h>
#include <TEA5767N.h>                             // https://github.com/mroger/TEA5767
#include <EEPROM.h>
#include <ClockButton.h>
#include "BCD.h"
#include "display.h"
#include "radio.h"

// ---- BOURNS POTENTIOMETER
 #define ADC1 A0
 unsigned int sensorValue = 0;
 unsigned long previousMillis=0 ;
 unsigned long interval = 2000L;

// ---- BUTTON SET
 #define inputPin1   11
 bool SET = 1;                                    //    MODE :: MANUAL: 0 || AUTO: 1
 unsigned long nowMillis = 0;
ClockButton button1(inputPin1, false);

// ---- Exponential Moving Average (EMA) \ 
      ---- algorithm adding simple low-pass software 
  
 float EMA_a = 0.06;      //initialization of EMA alpha
 int EMA_S = 0;           //initialization of EMA S

 volatile byte ledState = LOW;

// -------------------------------- SETUP --------------------------------------------------- //

void setup() 
{
  // NIXIE
  pinMode(NX_LATCH, OUTPUT);
  pinMode(NX_DATA, OUTPUT);
  pinMode(NX_CLOCK, OUTPUT);
  Wire.begin();

  EMA_S = analogRead(ADC1);                           // BOURNS POTENTIOMETER

  if ( SET == 1) {                                    // MODE AUTO 
    FREQ = EEPROM.get(address,currFreq);
    updateDisplay(FREQ);
    radioStart();                                     // START THE RADIO
  } 

  // BUTTON
  pinMode(inputPin1, INPUT );                         
  digitalWrite(inputPin1, HIGH);                      

  // LED
  pinMode(ledPin, OUTPUT);
  
}                                                     //  ~ SETUP

//
// ------------------------- LOOP -----------------------------
void loop() 
{
  nowMillis = millis();
  button1.checkButton(nowMillis);

  if ( SET == 0 ) {
    digitalWrite(ledPin, ledState);
  } else {
    digitalWrite(ledPin, !ledState);
    }

  if (button1.isButtonPressedReleased1S()) {             // MODE SET (AUTO or MANUAL)
    SET = !SET;
    delay(50);
    digitalWrite(ledPin, !ledState);
    if (SET == 1) { 
      stationIndex = EEPROM.get(addressStationIndex, stationIndex);
      loadStations(stationIndex);
    }
  }
  
  else if (button1.isButtonPressedAndReleased()) {
    if (SET == 1) {
        if (stationIndex < 23 )  {   
          stationIndex = EEPROM.get(addressStationIndex ,stationIndex);
          stationIndex++;
        } else {
          stationIndex = 0;
        }
      
    loadStations(stationIndex);

    } else {                                              
        if (SET == 0) {
          EEPROM.put(address, FREQ);                      // SAVE STATION TO EPROOM
          flashLed();
        } 
      }
  }
  
  if (SET == 0) {
    digitalWrite(ledPin, LOW);
    
    sensorValue = analogRead(ADC1);
    EMA_S = (EMA_a * sensorValue) + ((1-EMA_a) * EMA_S);
    FREQ = constrain(( (EMA_S - 0.0) * (108.4 - 88.0) / (1023 - 0.0) + 88.0) * 10 , 880, 1088);
    updateDisplay(FREQ);

    if ( ( currFreq != FREQ) && ( millis() - previousMillis >= 4000L) ) {
      currFreq = FREQ ;
      radioStart();
      previousMillis = millis();
    }

 }                                
}  //  ~ LOOP
