// src/main.c
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "config.h"
#include "globals.h"
#include "LED_DISPLAY.h"
#include "Button_Input.h"
#include "LCD_Display.h"
#include "Single_Mode.h"
#include "Multi_Mode.h"

void setup() {
    usartInit(9600);
    lcdInit();
    lcdBacklightOn();
    initLEDs();
    initButtons();
    showWelcomeScreen();
}

void loop() {
    // Reset button priority
    if (!(PINB & (1 << RESET_BTN))) {
        resetGame();
        _delay_ms(200);
        return;
    }

    // Player select
    if (playerMode == 0) {
        handlePlayerSelection();
        return;
    }

    // Game select
    if (gameMode == 0) {
        handleGameSelection();
        return;
    }

    // In-game
    if (playerMode == 1) {
        switch (gameMode) {
            case 1: SP_memoryLoop();       break;
            case 2: SP_reactionLoop();     break;
            case 3: SP_coordinationLoop(); break;
        }
    } else {
        switch (gameMode) {
            case 1: MP_memoryLoop();       break;
            case 2: MP_reactionLoop();     break;
            case 3: MP_coordinationLoop(); break;
        }
    }
}
