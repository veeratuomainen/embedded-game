#include "rgb_lcd.h" //display library 
#include <EEPROM. h> 
 
rgb_lcd lcd; 
 
int score = 0; // Game score. High score is stored in EEPROM 
int randNumber; // Random number for determining game action 
int buttonPin = 3; //Signal pin (digital) for push-button 
const int analogInPin = A0; // Signal pin (analog) for rotation sensor 
bool state = true; 
const int colorR = 255; 
const int colorG = 0; 
const int colorB = 0; 
int sensorValue = 0; 
int newSensorValue; 
int highScore = 0; 
volatile bool buttonPressed = false; 
 
const int speakerPin = 7; // Signal pin (digital) for speaker 
const int numCorrectNotes = 4; // Number of notes for each tune 
const int numErrorNotes = 5; 
const int numHighScoreNotes = 12; 
 
int correctNotes[] = {523, 587, 659, 698}; // Frequency values for correct action notes 
int correctDurations[] = {200, 200, 200, 200}; // Duration values for correct action notes 
int errorNotes[] = {392, 349, 311, 277, 261}; // Frequency values for error notes 
int errorDurations[] = {200, 200, 200, 200, 200}; // Duration values for error notes 
int highScoreNotes[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093, 2349, 2637, 2794, 3136}; //Frequency values for high score notes 
int highScoreDurations[] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200}; // Duration values for high score notes 
 
void setup(){ 
  pinMode(buttonPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressedISR, RISING); // Attach an interrupt to the button pin 
  Serial.begin (9600); 
  Serial.println(""); 
  lcd.begin(16, 2); //Setting up display properties 
  lcd.setRGB(colorR, colorg, colorB); 
  pinMode (speakerPin, OUTPUT); 
  startup_interface(); 
  ADMUX = (1 << REFS0) ; 
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable the ADC and set the prescaler to 128 for a 16MHz clock 
  score = 0; 
  state = true; 
  Serial.print("Setup"); 
  buttonPressed = false; 
} 

void startup_interface() { //interface for palyer that gives game instructions 
  buttonPressed = false; 
  while (!buttonPressed) { 
    lcd.print ("Welcome to    ") : 
    lcd.setCursor(0,1); 
    lcd.print("bop-it game!  "); 
    delay (2000); 
    lcd.clear (); 
    lcd.setCursor(0,0); 
    lcd.print("Follow text"); 
    lcd.setCursor(0,1); 
    lcd.print("instructions"); 
    delay (2000); 
    lcd. clear(); 
    lcd.setCursor (0,0); 
    lcd.print("And do action"); 
    lcd.setCursor(0,1); 
    lcd.print("when instructed"); 
    delay (2000); 
    lcd.clear (); 
    lcd.setCursor(0,0); 
    lcd.print("You have 3 sec"); 
    lcd.setCursor(0,1); 
    lcd.print("for each action"); 
    delay (2000); 
    lcd.clear(); 
    lcd.setCursor(0,0); 
    lcd.print ("Press button to"); 
    lcd.setCursor(0,1); 
    lcd.print("start game"); 
    delay (2000); 
    lcd.clear(); 
    lcd.setCursor(0,0); 
    lcd.print ("Good luck!!!"); 
    delay (4000); 
    lcd.clear(); 
  }
}

void loop() {
  while (state) { 
    lcd.clear(); 
    randNumber = random(1, 3);
    buttonPressed = false; 
    lcd.clear();
    if (randNumber == 1) {
      lcd.clear(); 
      ADCSRA |= (1 << ADSC); // Start ADC conversion 
      while (ADCSRA & (1 << ADSC)); // Wait for the conversion to complete 
      sensorValue = ADCL | (ADCH << 8); // Read the ADC result from the registers 
      lcd.print("Push button!"); 
      delay (3000); //Time to push button 
      ADCSRA |= (1 << ADSC); // Start ADC conversion 
      while (ADCSRA & (1 << ADSC));
      newSensorValue = ADCL | (ADCH << 8); 
      if (sensorValue+3 <= newSensorValue | sensorValue-3 >= newSensorValue || !buttonPressed){ 
        lcd.clear(); 
        lcd.print ("Game over"); 
        playMelody(errorNotes, errorDurations, numErrorNotes); 
        delay(1000); 
        sensorValue = newSensorValue; 
        state = false; 
        gameover(); 
      }

      if (buttonPressed) { 
        lcd.clear(); 
        lcd.print("Well done!"); 
        playMelody(correctNotes, correctDurations, numCorrectNotes); 
        delay(1000); 
        score++;
      }
    } else if (randNumber == 2) { 
      lcd.clear(); 
      ADCSRA = (1 << ADSC); // Start ADC conversion 
      while (ADCSRA & (1 << ADSC)); // Wait for the conversion to complete 
      sensorValue = ADCL | (ADCH << 8); // Read the ADC result from the registers 
      lcd.print("Rotate sensor!"); 
      buttonPressed = false; 
      delay(3000);
      ADCSRA |= (1 << ADSC); // Start ADC conversion 
      while (ADCSRA & (1 << ADSC)); // Wait for the conversion to complete 
      newSensorValue = ADCL | (ADCH << 8); // Read the ADC result from the registers 
      if (buttonPressed || sensorValue-3 <= newSensorValue && sensorValue +3 >= newSensorValue) {
        lcd.clear(): 
        lcd.print("Game over"); 
        playMelody(errorNotes, errorDurations, numErrorNotes); 
        delay(3000); 
        gameOver(); 
      } 
      if (sensorValue+3 <= newSensorValue || sensorValue-3 >= newSensorValue) { 
        score++;
        lcd.clear();
        lcd.print("Well done!"); 
        playMelody(correctNotes, correctDurations, numCorrectNotes); 
        delay(2000); 
        sensorValue = newSensorValue; 
      } 
      newSensorValue = analogRead(analogInPin); 
    }
  }
}

void gameOver) { 
  buttonPressed = false; 
  state = false; 
  while(!state) { 
    if (score >= EEPROM.read(0)) { 
      EEPROM.write(0, score);
      lcd.clear();
      lcd.print ("New high score"); 
      playMelody(highScoreNotes, highScoreDurations, numHighScoreNotes); 
      delay (2000);
    }
    lcd.clear(); 
    delay(1000);
    lcd.print("Score: "); 
    lcd.print(score);
    lcd.setCursor(0,1); 
    lcd.print("High score: "); 
    EEPROM.get(0, highScore); 
    lcd.print(highScore); 
    delay (3000); 
    lcd.clear();
    lcd.print("Press button to "); 
    lcd.setCursor(0,1); 
    lcd.print("start a new game"); 
    delay (2000);
    if (buttonPressed) { 
      setup(); 
    }
  }
}

void buttonPressedISR() { // This function will be called when the button is pressed 
  buttonPressed = true; // Toggle the button state 
}

void playMelody(int notes[], int durations[], int numNotes) { 
  for (int i = 0; i < numNotes; i++) { 
    tone(speakerPin, notes(i], durations[i]); 
    delay(durations[i] * 1.3); // Add a slight delay between notes 
    noTone(speakerPin); 
  }
}
