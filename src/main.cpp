#include <Arduino.h>
#include "animations.c"

int cube[4][4][4] = {0};



const int PIN_LAYOUT[4][4] = {
  { A0, 8, 6, 5 },
  { 9, A1, 7, 4 },
  { A5, A2, 1, 3 },
  { A4, A3, 0, 2 }
};

const int LAYER_LAYOUT[4] = { 13, 12, 11, 10 };



// put function declarations here:
// int myFunction(int, int);

void setup() {
  // Set pin modes
  for (int i = 0; i < 4; i++) {
    pinMode(LAYER_LAYOUT[i], OUTPUT);
    for (int j = 0; j < 4; j++) {
      pinMode(PIN_LAYOUT[i][j], OUTPUT);
      digitalWrite(PIN_LAYOUT[i][j], HIGH);
    }
  }
}

void loop() {
  // runningLeds(100, LAYER_LAYOUT, PIN_LAYOUT);
  // outerLoop(LAYER_LAYOUT, PIN_LAYOUT);
  // combinedLoop(LAYER_LAYOUT, PIN_LAYOUT);
  rainDrops(LAYER_LAYOUT, PIN_LAYOUT, cube, 20);
  // runningLeds(100, LAYER_LAYOUT, PIN_LAYOUT);
  // outerLoop(LAYER_LAYOUT, PIN_LAYOUT);

}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }