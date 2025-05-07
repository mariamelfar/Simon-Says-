#pragma once
#include "Globals.h"
#include "Single_Mode.h"
#include "Multi_Mode.h"
#include "LCD_Display.h"

//Pull_UP for Buttons
void initButtons() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(p1Buttons[i], INPUT_PULLUP); //internal pull-up resistor
    pinMode(p2Buttons[i], INPUT_PULLUP);
  }
  pinMode(resetButton, INPUT_PULLUP);
}

//Select Player Mode (Single or 2-Players)
void handlePlayerSelection() {
  if (digitalRead(p1Buttons[0]) == LOW) { // Red button - single player (P1 only)
    playerMode = 1; //Single_Player
    showGameSelect();
  } else if (digitalRead(p1Buttons[1]) == LOW || digitalRead(p2Buttons[1]) == LOW ){ // Blue button - multiplayer (P1 - P2)
    playerMode = 2;
    showGameSelect();
  }
}

// choose game mode 
void handleGameSelection() { 
  for (int c = 0; c < 3; c++) {
    if ((playerMode == 1 && digitalRead(p1Buttons[c]) == LOW) || (playerMode == 2 && digitalRead(p2Buttons[c]) == LOW) || (playerMode == 2 && digitalRead(p1Buttons[c]) == LOW)) //0: P1: Single -> Red || P2: 2-player -> Red || P1: 2-player -> Red   
    {
      delay(50); // debounce (for noise)
        gameMode = c + 1; //1: Red, 2: Blue, 3: Green
        lcd.clear();

        if (playerMode == 1)  //Single
        {
          if (gameMode == 1) SP_startMemoryGame(); //1st iteration: Memory 
          else if (gameMode == 2) SP_startReactionGame();  //2nd: Reaction Fast
          else if (gameMode == 3) SP_startCoordinationGame();  //3rd: Coordination
        } 
        
        else if (playerMode == 2) //2-players 
        {
          if (gameMode == 1) MP_startMemoryGame();
          else if (gameMode == 2) MP_startReactionGame();
          else if (gameMode == 3) MP_startCoordinationGame();
        }
    }
  }
}