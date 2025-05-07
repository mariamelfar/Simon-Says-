#pragma once
#include "Globals.h"
#include "Single_Mode.h"
#include "Multi_Mode.h"
#include "LCD_Display.h"

//Pull_UP for Buttons
void initButtons(void) {
    // — Player 1 buttons on PORTD —  
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        DDRD  &= ~(1 << p1Buttons[i]);  // input
        PORTD |=  (1 << p1Buttons[i]);  // pull-up on
    }

    // — Player 2 buttons on PORTB —  
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        DDRB  &= ~(1 << p2Buttons[i]);
        PORTB |=  (1 << p2Buttons[i]);
    }

    // — Reset button on PORTB —  
    DDRB  &= ~(1 << RESET_BTN);
    PORTB |=  (1 << RESET_BTN);
}

//Select Player Mode (Single or 2-Players)
void handlePlayerSelection(void) {
    // — Single-player: P1 red button (p1Buttons[0] on PORTD) pressed?
    if (!(PIND & (1 << p1Buttons[0]))) {
        playerMode = 1;     // Single_Player
        showGameSelect();
    }
    // — Multiplayer: P1 blue (p1Buttons[1] on PORTD) OR P2 blue (p2Buttons[1] on PORTB)
    else if (!(PIND & (1 << p1Buttons[1])) 
          || !(PINB & (1 << p2Buttons[1]))) {
        playerMode = 2;     // Multiplayer
        showGameSelect();
    }
}

// choose game mode 
void handleGameSelection(void) {
    for (uint8_t c = 0; c < 3; c++) {
        // read buttons (pressed = LOW because of pull-ups)
        bool p1Pressed = !(PIND & (1 << p1Buttons[c]));
        bool p2Pressed = !(PINB & (1 << p2Buttons[c]));

        // single-player: P1 only
        // 2-player: either P2 or P1
        if ((playerMode == 1 && p1Pressed) ||
            (playerMode == 2 && (p2Pressed || p1Pressed)))
        {
            _delay_ms(50);  // simple debounce

            gameMode = c + 1;  
            lcdClear();

            if (playerMode == 1) {
                if      (gameMode == 1) SP_startMemoryGame();
                else if (gameMode == 2) SP_startReactionGame();
                else if (gameMode == 3) SP_startCoordinationGame();
            } else {  // playerMode == 2
                if      (gameMode == 1) MP_startMemoryGame();
                else if (gameMode == 2) MP_startReactionGame();
                else if (gameMode == 3) MP_startCoordinationGame();
            }

            break;  // stop checking other buttons this cycle
        }
    }
}
