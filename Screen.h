#include <RGBmatrixPanel.h>
#include <Fonts/TomThumb.h>

#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
enum State{INIT, GAME, LOSS};
extern State gameState;


void initScreen();
void drawInitialScreen();
void rainLoop();
void gameLoop(int pos);
void clearNotes();
void clearScreen();
void customRect(int x1, int y1, int x2, int y2, uint32_t c);
