//#include <Servo.h>
#include <Wire.h>
#include <ezBuzzer.h>
//#include "Pitches.h"
#include "Screen.h"

//pin inputs
//#define CLK  8
//#define OE   9
//#define LAT 10
//#define A   A0
//#define B   A1
//#define C   A2
int joy_yellow = A3;
int joy_orange = A4;
//int servoPin = 11;
//int buzzerPin = 13;
//ezBuzzer buzzer(buzzerPin);

//rgb matrix uses: A0, A1, A2, A3, (A4?), 2, 3, 4, 5, 6, 7, 8, 9

//Servo myservo;
int position=20;
int speed=99;
int destination = 20;
int reached = 1;

int tempo=114;

//int notes = sizeof(melody) / sizeof(melody[0]) / 2;
//int wholenote = (60000 * 4) / tempo;
//int divider = 0, noteDuration = 0;

int i = 0;
int t1 = 0;

void setup() {
  Serial.begin(9600);
//  myservo.attach(servoPin);
  pinMode(joy_yellow, INPUT_PULLUP);
  pinMode(joy_orange, INPUT_PULLUP);
  initScreen();

}
 
void loop() {
  int screenDelay = 70;
  int t2 = millis();
  int tDelta = t2 - t1;
  int joy_left = !digitalRead(joy_yellow);
  int joy_right = !digitalRead(joy_orange);
  
  if (tDelta > screenDelay) {
    switch(gameState) {
    case INIT:
      if (joy_left || joy_right) {
        drawInitialScreen();
        gameState = GAME;
        clearNotes();
      }
      break;
    case GAME:
      int pos = -joy_left + 1 + joy_right;
      Serial.println(pos);
      gameLoop(pos);
      break;
    }
    t1 = t2; 
  }
  
//  buzzer.loop();
//
//  if (buzzer.getState() == BUZZER_IDLE) {
//      int length = sizeof(noteDurations) / sizeof(int);
//      buzzer.playMelody(melody, noteDurations, length); // playing
//    }
   
//  // Screen Inputs

  // Joystick Inputs
  
  //Joystick Input Display on Serial Monitor
//  Serial.print("left: ");
//  Serial.print(joy_left);
//  Serial.print("\t");
//  Serial.print("right: ");
//  Serial.print(joy_right);
//  Serial.println("\t");
//  Serial.println(position);

  //Servo Rotation
 
// if (joy_right && reached && destination<20){
//    destination += 10;
//    reached = 0;
//    
//  }
//  else if (joy_left && reached && destination>0){
//    
//    destination-=10;
//    reached = 0;
//  }
//
//  if (position>destination){
//    myservo.writeMicroseconds(1000);
//    position-=1;
//  }
//  else if (position<destination){
//    myservo.writeMicroseconds(2000);
//    position+=1;
//  }
//  else{
//    reached = 1;
//    myservo.writeMicroseconds(1500);
//  }
  
  
}
