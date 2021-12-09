#include <Servo.h>
#include <Wire.h>
#include <ezBuzzer.h>
#include "pitches.h"
#include <RGBmatrixPanel.h>



//pin inputs
int joy_yellow = 10;
int joy_orange = 11;
int servoPin = 12;
int buzzerPin = 13;
ezBuzzer buzzer(buzzerPin);

//rgb matrix uses: A0, A1, A2, A3, (A4?), 2, 3, 4, 5, 6, 7, 8, 9

Servo myservo;
int position=20;
int speed=99;
int destination = 20;
int reached = 1;

int tempo=114;

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

int i = 0;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  matrix.begin();
  drawInitialScreen();
  Serial.begin(9600);
  myservo.attach(servoPin);
  pinMode(joy_yellow, INPUT_PULLUP);
  pinMode(joy_orange, INPUT_PULLUP);

  
  
//  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
//
//    // calculates the duration of each note
//    divider = melody[thisNote + 1];
//    if (divider > 0) {
//      // regular note, just proceed
//      noteDuration = (wholenote) / divider;
//    } else if (divider < 0) {
//      // dotted notes are represented with negative durations!!
//      noteDuration = (wholenote) / abs(divider);
//      noteDuration *= 1.5; // increases the duration in half for dotted notes
//    }
//
//    // we only play the note for 90% of the duration, leaving 10% as a pause
//    tone(buzzer, melody[thisNote], noteDuration * 0.9);
//
//    // Wait for the specief duration before playing the next note.
//    delay(noteDuration);
//
//    // stop the waveform generation before the next note.
//    noTone(buzzer);
//  }

}
 
void loop() {
  buzzer.loop();

  if (buzzer.getState() == BUZZER_IDLE) {
      int length = sizeof(noteDurations) / sizeof(int);
      buzzer.playMelody(melody, noteDurations, length); // playing
    }
   
  // Screen Inputs
  drawPanel();
  
  // Joystick Inputs
  int joy_left = !digitalRead(joy_yellow);
  int joy_right = !digitalRead(joy_orange);
  
  //Joystick Input Display on Serial Monitor
  Serial.print("left: ");
  Serial.print(joy_left);
  Serial.print("\t");
  Serial.print("right: ");
  Serial.print(joy_right);
  Serial.println("\t");
  //Serial.println(position);

  //Servo Rotation
 
 if (joy_right && reached && destination<20){
    destination += 10;
    reached = 0;
    
  }
  else if (joy_left && reached && destination>0){
    
    destination-=10;
    reached = 0;
  }

  if (position>destination){
    myservo.writeMicroseconds(1000);
    position-=1;
  }
  else if (position<destination){
    myservo.writeMicroseconds(2000);
    position+=1;
  }
  else{
    reached = 1;
    myservo.writeMicroseconds(1500);
  }
  
  
}


void drawInitialScreen() {
  matrix.setRotation(1);
  matrix.setCursor(1, 0);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('1');
  matrix.setTextColor(matrix.Color333(7,4,0));
  matrix.print('6');
}
void drawPanel() {
}
  
