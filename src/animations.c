// animations.c
// LED cube animation helper functions for a 4x4x4 LED cube.
//
// Conventions:
// - cube is a 4x4x4 int array: cube[layer][row][col], where 1 = LED on, 0 = LED off.
// - LAYER_LAYOUT is an array of 4 Arduino pin numbers mapping layer index -> pin.
// - PIN_LAYOUT is a 4x4 array mapping row and column to Arduino pin numbers: PIN_LAYOUT[row][col].
// - Many boards/drivers invert logic; this code writes LOW to turn an LED on and HIGH to turn it off.
// - Delay values are in milliseconds.

#include "animations.h"
#include <Arduino.h>

// Repeatedly multiplex the whole cube for the given duration (ms).
// Uses multiPlexOnce internally with a small brightness delay to create persistence of vision.
// Parameters:
// - cube: 4x4x4 array of LED states.
// - LAYER_LAYOUT: layer-to-pin mapping.
// - PIN_LAYOUT: row/col-to-pin mapping.
// - duration: total time to run the multiplexing (in ms).
void multiPlex(int cube[4][4][4], const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4], int duration) {
    int brightnessDelay = 1; // Adjust this value to control brightness
    for (int i = 0; i < duration/brightnessDelay; i++) {
        multiPlexOnce(cube, LAYER_LAYOUT, PIN_LAYOUT, brightnessDelay);
    }
}

// Perform a single pass through each layer, setting column pins according to cube values,
// enabling the layer pin briefly, then disabling it.
// Parameters:
// - wait: time in ms to hold each layer active.
void multiPlexOnce(int cube[4][4][4], const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4], int wait) {
    for (int layer = 0; layer < 4; layer++) {      
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (cube[layer][row][col] == 1) {
                    digitalWrite(PIN_LAYOUT[row][col], LOW);
                } else {
                    digitalWrite(PIN_LAYOUT[row][col], HIGH);
                }
            }
        }
        digitalWrite(LAYER_LAYOUT[layer], HIGH);
        delay(wait); 
        digitalWrite(LAYER_LAYOUT[layer], LOW);
    }
}

// Set or clear multiple layer pins at once.
// - layers: array of layer indices to update (e.g. {0,1}).
// - len: number of entries in layers.
// - state: true => HIGH, false => LOW.
void updateLayer(int layers[4], int len, const int LAYER_LAYOUT[4], bool state) {
    for (int i = 0; i < len; i++) {
        digitalWrite(LAYER_LAYOUT[layers[i]], state ? HIGH : LOW);
    }
}

// Simple running LED animation that lights each LED in a row/column order per layer.
// - delayTime: Delay between LED activations (in ms).
void runningLeds(int delayTime, const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4]) {
    for (int k = 0; k < 4; k++) { // For each layer
        digitalWrite(LAYER_LAYOUT[k], HIGH);
        for (int i = 0; i < 4; i++) { // For each row in the layer
            for (int j = 0; j < 4; j++) { // For each LED in the row
                digitalWrite(PIN_LAYOUT[i][j], LOW);
                delay(delayTime);
                digitalWrite(PIN_LAYOUT[i][j], HIGH);
            }
        }
        digitalWrite(LAYER_LAYOUT[k], LOW);
    }
}

// Light the outer ring of LEDs in sequence across all layers. Useful for border animations.
void outerLoop(const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4]) {
    const int OUTER_PINS[12] = {PIN_LAYOUT[0][0], PIN_LAYOUT[0][1], PIN_LAYOUT[0][2], PIN_LAYOUT[0][3],
                               PIN_LAYOUT[1][3], PIN_LAYOUT[2][3], PIN_LAYOUT[3][3],
                               PIN_LAYOUT[3][2], PIN_LAYOUT[3][1], PIN_LAYOUT[3][0],
                               PIN_LAYOUT[2][0], PIN_LAYOUT[1][0]};

    // digitalWrite(LAYER_LAYOUT[0], HIGH);
    int layers[4] = {0, 1, 2, 3};
    updateLayer(layers, 4, LAYER_LAYOUT, true);
    for (int i = 0; i < 12; i++) {
        digitalWrite(OUTER_PINS[i], LOW);
        delay(100);
        digitalWrite(OUTER_PINS[i], HIGH);
    }
}

// Combined animation that runs outer and inner rings with simple layer swapping.
// Note: relies on updateLayer to enable/disable groups of layers.
void combinedLoop(const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4]) {
    const int OUTER_PINS[12] = {PIN_LAYOUT[0][0], PIN_LAYOUT[0][1], PIN_LAYOUT[0][2], PIN_LAYOUT[0][3],
                               PIN_LAYOUT[1][3], PIN_LAYOUT[2][3], PIN_LAYOUT[3][3],
                               PIN_LAYOUT[3][2], PIN_LAYOUT[3][1], PIN_LAYOUT[3][0],
                               
                               PIN_LAYOUT[2][0], PIN_LAYOUT[1][0]};
    const int INNER_PINS[4] = {PIN_LAYOUT[1][1], PIN_LAYOUT[1][2],
                               PIN_LAYOUT[2][2], PIN_LAYOUT[2][1]};

    // digitalWrite(LAYER_LAYOUT[0], HIGH);
    int layers[2] = {0, 1};
    updateLayer(layers, 2, LAYER_LAYOUT, true);
    for (int i = 0; i < 12; i++) {
        int difference = 6;
        if (i > 6) {difference = -6;}

        digitalWrite(OUTER_PINS[i], LOW);
        digitalWrite(INNER_PINS[(int)(i/3)], LOW);

        int layers1[2] = {2, 3};
        updateLayer(layers, 2, LAYER_LAYOUT, false);
        updateLayer(layers1, 2, LAYER_LAYOUT, true);

        digitalWrite(OUTER_PINS[i+difference], LOW);
        digitalWrite(INNER_PINS[(int)((i+difference)/3)], LOW);

        delay(100);

        updateLayer(layers1, 2, LAYER_LAYOUT, false);
        updateLayer(layers, 2, LAYER_LAYOUT, true);

        digitalWrite(OUTER_PINS[i], HIGH);
        digitalWrite(INNER_PINS[(int)(i/3)], HIGH);

        updateLayer(layers, 2, LAYER_LAYOUT, false);
        updateLayer(layers1, 2, LAYER_LAYOUT, true);

        digitalWrite(OUTER_PINS[i+difference], HIGH);
        digitalWrite(INNER_PINS[(int)((i+difference)/3)], HIGH);
    }
}

// Simulate raindrops falling through the cube by shifting values down through layers.
// - cube is modified in-place to move LEDs from upper layers downwards.
// - duration is forwarded to multiPlex to refresh the display between steps.
void rainDrops(const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4], int cube[4][4][4], int duration) {
    // Implementation of rainDrops animation
    for (int layer = 3; layer >= 0; layer--) {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (layer == 0) {
                    cube[layer][row][col] = 0;
                    continue;
                }

                cube[layer][row][col] = cube[layer - 1][row][col];
                // cube[layer - 1][row][col] = 0;
            }
        }
        if (layer == 0 && random()%1 == 0) {
            cube[layer][random()%4][random()%4] = 1;
            continue;
        }
        multiPlex(cube, LAYER_LAYOUT, PIN_LAYOUT, duration);

    }
}