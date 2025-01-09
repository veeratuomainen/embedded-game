#include <Wire.h>
#include <DFRobot_ADS1115.h>
#include "rgb_lcd.h"  //display library
#include <TimerOne.h>

rgb_lcd lcd;

int score = 0; 
int randNumber;
int buttonPin = 3;  //pitää vielä katsoa onko hyvä pinni
const int analogInPin = A0;
bool onko = true;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
int sensorValue = 0; 
int newSensorValue;

void setup(){
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("");
  lcd.begin(16, 2); //Setting up display properties  
  lcd.setRGB(colorR, colorG, colorB);
  startup_interface();
  
}

void startup_interface() {
  
    int val = digitalRead(buttonPin);
    lcd.print("   Welcome to   "); 
    lcd.setCursor(0,1);
    lcd.print("   bop-it game! ");
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Follow voice");
    lcd.setCursor(0,1);
    lcd.print("instructions");
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("And do action");
    lcd.setCursor(0,1);
    lcd.print("when instructed");
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press button to");
    lcd.setCursor(0,1);
    lcd.print("start the game");
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Good luck!!!");
    delay(100);
    lcd.clear();
    
}

void loop() {
  while (onko) {
    lcd.clear();
    randNumber = random(1, 3);
    lcd.print(randNumber);
    delay(1000);
    lcd.clear();
    if (randNumber == 1) {
      lcd.clear();
      lcd.print("Push button!");
      int val = digitalRead(buttonPin);
      if (val == HIGH) {
        lcd.clear();
        lcd.print("Yksi piste");
        delay(3000);
        score++;
      } // <-- Added missing curly brace here
    } else if (randNumber == 2) { // <-- Moved "else if" here
      lcd.clear();
      lcd.print("Rotate sensor!");
      newSensorValue = analogRead(analogInPin);
      Serial.print(newSensorValue);
      if (sensorValue != newSensorValue) {  //pitää vielä toteuttaa riittävä puskuri koska arvo ei pysy aivan samana, vaikka sensoria ei käännetä
        score++;
        lcd.clear();
        lcd.print("Hienosti kaannetty");
        delay(2000);
        sensorValue = newSensorValue;
      }
    }
  }
}