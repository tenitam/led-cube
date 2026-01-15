// main.cpp
// Entry point for the 4x4x4 LED cube project.
//
// Notes:
// - This file defines the cube state array and the pin mappings used by the
//   animation helper functions in animations.c.
// - PIN_LAYOUT maps [row][col] -> Arduino pin number. Rows and columns refer
//   to the LED matrix within each layer. Analog pins (A0, A1, ...) can be used
//   with digitalWrite/pinMode on Arduino-compatible boards.
// - LAYER_LAYOUT maps layer index (0..3) -> Arduino pin controlling that layer.
// - The code in animations.c assumes that writing LOW turns an LED on and HIGH
//   turns it off. Adjust wiring or logic if your hardware is different.

#include <Arduino.h>
#include "animations.c"

// The cube state: cube[layer][row][col]. 1 = on, 0 = off. Initialized to all off.
int cube[4][4][4] = {0};

// PIN_LAYOUT[row][col] -> Arduino pin for that column in the given row.
// Update these values to match your wiring.
const int PIN_LAYOUT[4][4] = {
  { A0, 8, 6, 5 },
  { 9, A1, 7, 4 },
  { A5, A2, 1, 3 },
  { A4, A3, 0, 2 }
};

// LAYER_LAYOUT[layer] -> Arduino pin used to enable/disable each layer.
const int LAYER_LAYOUT[4] = { 13, 12, 11, 10 };

void setup() {
  // Configure layer and column pins as outputs and set columns to the OFF state
  // (HIGH) so LEDs are off until animations explicitly drive them LOW.
  for (int i = 0; i < 4; i++) {
    pinMode(LAYER_LAYOUT[i], OUTPUT);
    for (int j = 0; j < 4; j++) {
      pinMode(PIN_LAYOUT[i][j], OUTPUT);
      digitalWrite(PIN_LAYOUT[i][j], HIGH);
    }
  }
}

void loop() {
  // Run the raindrops animation. The last parameter controls how long each
  // multiplex refresh lasts (in milliseconds per step). Increase the value to
  // slow the animation, decrease to speed it up.
  rainDrops(LAYER_LAYOUT, PIN_LAYOUT, cube, 20);

  // Other animations are available; uncomment to try them. They currently
  // run a visible sequence and return, so you can call them in loop() as
  // needed to switch effects.

  // runningLeds(100, LAYER_LAYOUT, PIN_LAYOUT);
  // outerLoop(LAYER_LAYOUT, PIN_LAYOUT);
}
