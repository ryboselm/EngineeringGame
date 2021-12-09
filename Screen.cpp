#include "Screen.h"
#include "Pitches.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
bool rain[32][8];
int tick = 0;
int note[32];
int buzzerPin = 13;

State gameState = INIT;
int score = 0;

// Initializing screen
void initScreen() {
  Serial.begin(9600);
  srand(time(0));
  matrix.begin();
  matrix.setRotation(1);
  matrix.setTextSize(1  );   // size 1 == 8 pixels high
  drawInitialScreen();
 
}

void drawInitialScreen() {
  score = 0;
  matrix.setFont(&TomThumb);
  matrix.fillRect(0, 0, 16, 32, matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 6);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('S');
  matrix.setCursor(4, 6);
  matrix.setTextColor(matrix.Color333(7,7,0));
  matrix.print('T');
  matrix.setCursor(7, 6);
  matrix.setTextColor(matrix.Color333(0,7,0));
  matrix.print('A');
  matrix.setCursor(10, 6);
  matrix.setTextColor(matrix.Color333(0,7,7));
  matrix.print('R');
  matrix.setCursor(13, 6);
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('T');
}

void drawScore(){
  matrix.setFont(&TomThumb);
  matrix.fillRect(0, 0, 16, 32, matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 6);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('S');
  matrix.setCursor(4, 6);
  matrix.setTextColor(matrix.Color333(7,7,0));
  matrix.print('C');
  matrix.setCursor(7, 6);
  matrix.setTextColor(matrix.Color333(0,7,0));
  matrix.print('O');
  matrix.setCursor(10, 6);
  matrix.setTextColor(matrix.Color333(0,7,7));
  matrix.print('R');
  matrix.setCursor(13, 6);
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('E');
  
  matrix.setTextColor(matrix.Color333(7,7,7));
  char buffer[3];
  itoa(score,buffer,10);
  int len = sizeof(buffer);
  for (int i=0; i<len; i++){
    matrix.setCursor(3+4*i,15);
    matrix.print(buffer[i]);
  }
  
  
}

// This ticks backward (just so rand() kicks in properly; don't ask why
void rainLoop() {
  delay(100);
//  Serial.println(freeMemory());
//  Serial.println(rainTick);
  if (tick == 0) {
    int x = rand() % 3;
    while (x < 8) {
      rain[7][x] = true;
      x += rand() % 1 + 1;
    }
    tick = rand() % 4 + 4;
  }
  tick--;
//
  matrix.fillRect(0, 0, 16, 32, matrix.Color333(0, 0, 0));
//  for (int row = 31; row >= 0 ; row--) {
//    for (int col = 0; col < 16; col++) {
//     Serial.print("loop: ");
//      Serial.print(row + ", ");
//      Serial.println(col);
//
//      if (rain[row][col] != 0) {
//        matrix.drawLine(col, row, col, row + 1, matrix.Color333(0,0,7));
//        if (row < 32) {
//          rain[row + 1][col] = true; 
//        }
//        rain[row][col] = false;
//      }
//    }
//  }
}

void clearNotes() {
  for (int i = 0; i < 32; i++) {
    note[i] = 0;  
  }
}
int melodycounter =0;
void gameLoop(int pos) {
  
  int x[6] = {1, 4, 6, 9, 11, 14};
  if (tick >= 32/noteDurations[melodycounter]) {
    note[7] = rand() % 3 + 1;
    tick = 0;
  }
//
  matrix.drawLine(5, 0, 5, 29, matrix.Color333(7, 7, 7));
  matrix.drawLine(10, 0, 10, 29, matrix.Color333(7, 7, 7));
  tick++;

  uint32_t bumperColor = matrix.Color333(0,4,7);
  
  for (int row = 31; row >= 0 ; row--) {
//      Serial.print(row);
//      Serial.print(", ");
//      Serial.println(col);
    if (note[row] != 0) {
      int col = note[row] - 1;
      int r = ((col % 3) == 0) * 7;
      int g = ((col % 3) == 1) * 7;
      int b = ((col % 3) == 2) * 7;
      matrix.drawLine(x[2 * (col % 3)], row, x[2 * (col % 3) + 1], row, matrix.Color333(r,g,b));
      matrix.drawLine(x[2 * (col % 3)], max(row - 1, 0), x[2 * (col % 3) + 1],  max(row - 1, 0), matrix.Color333(0,0,0));
      if (row < 30) {
        note[row + 1] = col + 1;
      }
      else {
        //tone
        tone(buzzerPin, melody[melodycounter], 800/noteDurations[melodycounter%sizeof(melody)]);
        Serial.println(melodycounter);
        melodycounter++;
        if (melodycounter>=sizeof(melody)/sizeof(int)){
          melodycounter = 0;
        }
        if (pos == col) {
          note[row] = 0;
          bumperColor = matrix.Color333(7, 7, 0);
          score++;
        }
        else {
          noTone(buzzerPin);
          melodycounter = 0;
          drawScore();
          delay(3000);
          gameState = INIT;
          drawInitialScreen();
          delay(2000);
          clearNotes();
          return;
        }
      }
      note[row] = 0;
    }
  }
  customRect(x[pos * 2], 30, x[pos * 2 + 1], 31, bumperColor);
  // Clearing the old bumper
  if (pos != 0) {
    customRect(x[0], 30, x[1], 31, matrix.Color333(0,0,0));
  }
  if (pos != 1) {
    customRect(x[2], 30, x[3], 31, matrix.Color333(0,0,0));
  }
  if (pos != 2) {
    customRect(x[4], 30, x[5], 31, matrix.Color333(0,0,0));
  }
}

//Cause lord knows why the rectangle function aint working
void customRect(int x1, int y1, int x2, int y2, uint32_t c) {
  for (int i = x1; i <= x2; i++) {
    matrix.drawLine(i, y1, i, y2, c);
  }
}
