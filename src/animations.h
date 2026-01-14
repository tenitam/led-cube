#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <Arduino.h>

void multiPlex(int cube[4][4][4], const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4], int duration);
void multiPlexOnce(int cube[4][4][4], const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4], int wait);
void updateLayer(int layers[4], int len, const int LAYER_LAYOUT[4], bool state);
void runningLeds(int delayTime, const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4]);
void outerLoop(const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4]);
void rainDrops(const int LAYER_LAYOUT[4], const int PIN_LAYOUT[4][4], int cube[4][4][4], int duration);

#endif
