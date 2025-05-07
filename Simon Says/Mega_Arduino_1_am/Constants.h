#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

// ---- Game constants ----
#define NUM_LEDS       4
#define MAX_SEQUENCE  15
#define REACT_ROUNDS  10
#define REACT_LENGTH   3
#define COORD_ROUNDS   6
#define COORD_MAX_LEN  7

// ---- AVR pin mappings ----
// LEDs (A4→PC4, A3→PC3, A2→PC2, A1→PC1)
#define LED_RED     PC4 
#define LED_BLUE    PC3
#define LED_GREEN   PC2
#define LED_YELLOW  PC1

// P1 buttons (D2→PD2, D3→PD3, D4→PD4, D5→PD5)
#define P1_BTN_RED     PD2
#define P1_BTN_BLUE    PD3
#define P1_BTN_GREEN   PD4
#define P1_BTN_YELLOW  PD5

// P2 buttons (D12→PB4, D11→PB3, D10→PB2, D9→PB1)
#define P2_BTN_RED     PB4
#define P2_BTN_BLUE    PB3
#define P2_BTN_GREEN   PB2
#define P2_BTN_YELLOW  PB1

// Buzzer & reset
#define BUZZER_PIN   PD7  // D7
#define RESET_BTN    PB5  // D13

// ---- Pin arrays ----
static const uint8_t ledPins[NUM_LEDS] = {
    LED_RED, LED_BLUE, LED_GREEN, LED_YELLOW
};
static const uint8_t p1Buttons[NUM_LEDS] = {
    P1_BTN_RED, P1_BTN_BLUE, P1_BTN_GREEN, P1_BTN_YELLOW
};
static const uint8_t p2Buttons[NUM_LEDS] = {
    P2_BTN_RED, P2_BTN_BLUE, P2_BTN_GREEN, P2_BTN_YELLOW
};

// ---- Game tones ----
static const uint16_t gameTones[] = {
    NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5
};

#endif  // CONFIG_H
