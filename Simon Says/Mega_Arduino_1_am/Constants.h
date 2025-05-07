#pragma once

// Game constants
#define NUM_LEDS       4
#define MAX_SEQUENCE  15     // Memory Race
#define REACT_ROUNDS  10     // Fastest Reaction
#define REACT_LENGTH   3
#define COORD_ROUNDS   6     // Coordination Test
#define COORD_MAX_LEN  7

// Hardware pins
const int ledPins[NUM_LEDS] = {A4, A3, A2, A1};  // LED pins: A1=red, A0=blue, 7=green, A2=yellow
const int p1Buttons[NUM_LEDS] = { 2, 3, 4, 5 };  // Player 1 buttons: red, blue, green, yellow
const int p2Buttons[NUM_LEDS] = { 12, 11, 10, 9 }; // Player 2 buttons: red, blue, green, yellow
const int buzzer = 7;
const int resetButton = 13;

// Game tones
const int gameTones[] = { NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5 };