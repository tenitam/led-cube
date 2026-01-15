# 4x4x4 LED Cube — Simple Arduino Animations

This repository contains a minimal set of helper files to drive a 4x4x4 LED cube from an Arduino-compatible board. The code is small and intended as a learning/demo project for multiplexed LED cube animations.

Files
- `src/main.cpp` — Entry point: defines the cube state and pin mappings, initializes pins and runs animations in `loop()`.
- `src/animations.c` — Animation routines and multiplexing helpers (multiplex, running LEDs, outer ring, raindrops, etc.).
- `src/animations.h` — Header with function prototypes for the animations.

Hardware / Wiring
- The code assumes a 4x4 matrix per layer and four layer-enable pins. The cube state is indexed as `cube[layer][row][col]`.
- `PIN_LAYOUT[row][col]` in `main.cpp` maps each row/column to a microcontroller pin. Edit this matrix to match your wiring.
- `LAYER_LAYOUT[layer]` maps layer indices (0..3) to the pins used to enable/disable layers.
- Logic note: the code drives column pins LOW to illuminate LEDs and HIGH to turn them off — this is common when layers are driven as high-side switches or when using transistors. If your wiring uses the opposite polarity, invert the HIGH/LOW logic in `animations.c`.

Software / Build
Option A — PlatformIO (recommended)
1. Install PlatformIO in VS Code.
2. Open the `led_cube` folder as a project.
3. Build and upload using the PlatformIO toolbar or `platformio run --target upload`.

Option B — Arduino IDE
1. Copy `src/main.cpp`, `src/animations.c`, and `src/animations.h` into a new Arduino sketch folder (same folder).
2. Open the sketch in the Arduino IDE, select the correct board and port, then upload.

Usage
- Edit `main.cpp` to change which animation is run in `loop()` or to tune timing values.
- Update `PIN_LAYOUT` and `LAYER_LAYOUT` to match your wiring before powering hardware.
- Test pins without the cube first (use LEDs/resistors or a multimeter) to avoid accidental shorts.

License
MIT — see LICENSE file if added. Feel free to reuse and adapt for personal or educational projects.


