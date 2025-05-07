#pragma once
#include "Globals.h"
#include "LCD_Display.h"
#include "LED_Control.h"

// Memory Game variables
int MP_sequence[MAX_SEQUENCE];
int MP_memStep, MP_memInputP1, MP_memInputP2;
bool MP_activeP1, MP_activeP2, MP_doneP1, MP_doneP2;
int MP_scoreP1, MP_scoreP2;

// Reaction Game variables
int MP_reactSeq[REACT_ROUNDS][REACT_LENGTH];
int MP_reactRound, MP_reactStepP1, MP_reactStepP2;
unsigned long MP_reactStartTime, MP_finishTimeP1, MP_finishTimeP2;
int MP_reactScoreP1, MP_reactScoreP2;
bool MP_doneReactP1, MP_doneReactP2;

// Coordination Game variables
int MP_coordSeq[COORD_ROUNDS][COORD_MAX_LEN];
int MP_coordLen[COORD_ROUNDS] = { 2, 3, 4, 5, 6, 7 };
int MP_coordRound, MP_coordStepP1, MP_coordStepP2;
unsigned long MP_coordStartTime;
int MP_coordScoreP1, MP_coordScoreP2;
bool MP_coordDoneP1, MP_coordDoneP2;

// Memory Game functions
void MP_playMemorySequence(){
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Level "); lcd.print(MP_memStep);
  lcd.setCursor(0, 1); lcd.print("Watch the sequence...");
  delay(500);
  
  for (int i = 0; i < MP_memStep; i++) {
    flashLedAndTone(MP_sequence[i]);
    delay(400);
  }
    lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Your turn!");
  lcd.setCursor(0, 1); lcd.print("P1 & P2: Repeat it!");
}
  
void MP_startMemoryGame() {
  MP_memStep = 1;
  MP_memInputP1 = MP_memInputP2 = 0;
  MP_activeP1 = MP_activeP2 = true;
  MP_doneP1 = MP_doneP2 = false;
  MP_scoreP1 = MP_scoreP2 = 0;
  for (int i = 0; i < MAX_SEQUENCE; i++) MP_sequence[i] = random(NUM_LEDS);
  MP_playMemorySequence();
}

void MP_memoryLoop() {
  //Player 1
  for (int i = 0; i < NUM_LEDS; i++) {
    if (MP_activeP1 && !MP_doneP1 && digitalRead(p1Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i != MP_sequence[MP_memInputP1]) {
        MP_activeP1 = false; MP_scoreP1--;
        lcd.clear(); lcd.setCursor(0, 1);
        lcd.print("P1 out on Lvl "); lcd.print(MP_memStep);
        delay(1500);
      } else {
        MP_scoreP1++;
        MP_memInputP1++;
        if (MP_memInputP1 >= MP_memStep) MP_doneP1 = true;
      }
      break;
    }
    //Player 2 
    if (MP_activeP2 && !MP_doneP2 && digitalRead(p2Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i != MP_sequence[MP_memInputP2]) {
        MP_activeP2 = false; 
        MP_scoreP2--;
        lcd.clear(); 
        lcd.setCursor(0, 1);
        lcd.print("P2 out on Lvl "); 
        lcd.print(MP_memStep);
        delay(1500);
      } else {
        MP_scoreP2++;
        if (++MP_memInputP2 >= MP_memStep) MP_doneP2 = true;
      }
      break;
    }
  }

  // end if both out or max level reached
  if (!MP_activeP1 && !MP_activeP2 && MP_memStep == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("        Both of U      ");
    lcd.print("  LOSSSSSSSSERRRRRRSSS  ");
    delay(3000);
    resetGame();
    return;
  }
  if ((!MP_activeP1 && !MP_activeP2) || MP_memStep > MAX_SEQUENCE) {
    MP_showMemoryResult();
    resetGame();
    return;
  }

  // advance to next level if both done/out
  if ((MP_doneP1 || !MP_activeP1) && (MP_doneP2 || !MP_activeP2)) {
    MP_memStep++;
    MP_memInputP1 = MP_memInputP2 = 0;
    MP_doneP1 = MP_doneP2 = false;
    delay(800);
    playLevelUpSound();
    MP_playMemorySequence();
  }
}

void MP_showMemoryResult() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("P1: "); lcd.print(MP_scoreP1);
  lcd.setCursor(0, 1); lcd.print("P2: "); lcd.print(MP_scoreP2);
  lcd.setCursor(0, 2);
  if (MP_scoreP1 == 0 && MP_scoreP2 == 0) lcd.print("P1 & P2 LOSERRRR");
  else if (MP_scoreP1 > MP_scoreP2)       lcd.print("P1 WINS! :)");
  else if (MP_scoreP2 > MP_scoreP1)       lcd.print("P2 WINS! :)");
  else                                    lcd.print("It's a tie! :)");
  delay(5000);
}

// Reaction Game functions
void MP_startReactionGame() {
  MP_reactScoreP1 = MP_reactScoreP2 = 0;
  MP_reactRound = 0;
  for (int r = 0; r < REACT_ROUNDS; r++)
    for (int s = 0; s < REACT_LENGTH; s++)
      MP_reactSeq[r][s] = random(NUM_LEDS);
  MP_startReactRound();
}

void MP_startReactRound() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Round "); lcd.print(MP_reactRound + 1);
  lcd.setCursor(0, 1); lcd.print("Watch the sequence...");
  delay(500);
  
  for (int i = 0; i < REACT_LENGTH; i++) {
    flashLedAndTone(MP_reactSeq[MP_reactRound][i]);
    delay(400);
  }
  
  MP_reactStepP1 = MP_reactStepP2 = 0;
  MP_doneReactP1 = MP_doneReactP2 = false;
  MP_reactStartTime = millis();
  MP_finishTimeP1 = MP_finishTimeP2 = 0;
  
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Repeat it fast!");
}

void MP_reactionLoop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (!MP_doneReactP1 && digitalRead(p1Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i == MP_reactSeq[MP_reactRound][MP_reactStepP1]) MP_reactScoreP1++;
      else MP_reactScoreP1--;
      if (++MP_reactStepP1 >= REACT_LENGTH) {
        MP_doneReactP1 = true;
        MP_finishTimeP1 = millis() - MP_reactStartTime;
      }
      break;
    }
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    if (!MP_doneReactP2 && digitalRead(p2Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i == MP_reactSeq[MP_reactRound][MP_reactStepP2]) MP_reactScoreP2++;
      else MP_reactScoreP2--;
      if (++MP_reactStepP2 >= REACT_LENGTH) {
        MP_doneReactP2 = true;
        MP_finishTimeP2 = millis() - MP_reactStartTime;
      }
      break;
    }
  }
  
  if (MP_doneReactP1 && MP_doneReactP2) {
    if (MP_finishTimeP1 < MP_finishTimeP2) MP_reactScoreP1++;
    else if (MP_finishTimeP2 < MP_finishTimeP1) MP_reactScoreP2++;
    
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("Round "); lcd.print(MP_reactRound + 1);
    lcd.setCursor(0, 1); lcd.print("P1:"); lcd.print(MP_finishTimeP1); lcd.print("ms");
    lcd.setCursor(10,1); lcd.print("P2:"); lcd.print(MP_finishTimeP2); lcd.print("ms");
    lcd.setCursor(0, 2);
    if (MP_finishTimeP1 < MP_finishTimeP2) lcd.print("Faster: P1");
    else if (MP_finishTimeP2 < MP_finishTimeP1) lcd.print("Faster: P2");
    else lcd.print("Tie!");
    lcd.setCursor(0, 3);
    lcd.print("S1:"); lcd.print(MP_reactScoreP1);
    lcd.print(" S2:"); lcd.print(MP_reactScoreP2);
    
    MP_reactRound++;
    if (MP_reactRound < REACT_ROUNDS) {
      delay(3000);
      MP_startReactRound();
    } else {
      MP_showReactResult();
      resetGame();
    }
  }
}

void MP_showReactResult() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Final Scores");
  lcd.setCursor(0, 1); lcd.print("P1:"); lcd.print(MP_reactScoreP1);
  lcd.setCursor(0, 2); lcd.print("P2:"); lcd.print(MP_reactScoreP2);
  lcd.setCursor(0, 3);
  if (MP_reactScoreP1 > MP_reactScoreP2) lcd.print("Winner: P1");
  else if (MP_reactScoreP2 > MP_reactScoreP1) lcd.print("Winner: P2");
  else lcd.print("Tie!");
  delay(5000);
}

// Coordination Game functions
void MP_startCoordinationGame() {
  MP_coordScoreP1 = MP_coordScoreP2 = 0;
  MP_coordRound = 0;
  for (int r = 0; r < COORD_ROUNDS; r++) {
    for (int i = 0; i < MP_coordLen[r]; i++) {
      MP_coordSeq[r][i] = random(NUM_LEDS);
    }
  }
  MP_startCoordRound();
}

void MP_startCoordRound() {
  MP_coordStepP1 = MP_coordStepP2 = 0;
  MP_coordDoneP1 = MP_coordDoneP2 = false;
  MP_coordStartTime = millis();

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Round "); lcd.print(MP_coordRound + 1);
  lcd.setCursor(0, 1); lcd.print("Length: "); lcd.print(MP_coordLen[MP_coordRound]);
  delay(1000);

  for (int i = 0; i < MP_coordLen[MP_coordRound]; i++) {
    flashLedAndTone(MP_coordSeq[MP_coordRound][i]);
    delay(400);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Replicate sequence!");
}

void MP_coordinationLoop() {
  unsigned long elapsed = millis() - MP_coordStartTime;
  lcd.setCursor(0, 3);
  lcd.print("T: "); lcd.print(elapsed); lcd.print(" ms");

  // P1 input
  for (int i = 0; i < NUM_LEDS; i++) {
    if (!MP_coordDoneP1 && digitalRead(p1Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i != MP_coordSeq[MP_coordRound][MP_coordStepP1]) MP_coordDoneP1 = true;
      else if (++MP_coordStepP1 >= MP_coordLen[MP_coordRound]) MP_coordDoneP1 = true;
      break;
    }
  }
  // P2 input
  for (int i = 0; i < NUM_LEDS; i++) {
    if (!MP_coordDoneP2 && digitalRead(p2Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i != MP_coordSeq[MP_coordRound][MP_coordStepP2]) MP_coordDoneP2 = true;
      else if (++MP_coordStepP2 >= MP_coordLen[MP_coordRound]) MP_coordDoneP2 = true;
      break;
    }
  }
  // Timeout
  if (elapsed > MP_coordLen[MP_coordRound] * 2000UL) {
    MP_coordDoneP1 = MP_coordDoneP2 = true;
  }

  // Round end
  if (MP_coordDoneP1 && MP_coordDoneP2) {
    if (MP_coordStepP1 == MP_coordLen[MP_coordRound]) MP_coordScoreP1 += 5;
    if (MP_coordStepP2 == MP_coordLen[MP_coordRound]) MP_coordScoreP2 += 5;

    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("Round "); lcd.print(MP_coordRound + 1);
    lcd.setCursor(0, 1); lcd.print("P1:"); lcd.print((MP_coordStepP1 == MP_coordLen[MP_coordRound]) ? 5 : 0);
    lcd.setCursor(10,1); lcd.print("P2:"); lcd.print((MP_coordStepP2 == MP_coordLen[MP_coordRound]) ? 5 : 0);
    lcd.setCursor(0, 2);
    if (MP_coordStepP1 == MP_coordLen[MP_coordRound] && MP_coordStepP2 != MP_coordLen[MP_coordRound]) lcd.print("Winner: P1");
    else if (MP_coordStepP2 == MP_coordLen[MP_coordRound] && MP_coordStepP1 != MP_coordLen[MP_coordRound]) lcd.print("Winner: P2");
    else lcd.print("Tie!");
    
    MP_coordRound++;
    if (MP_coordRound < COORD_ROUNDS) {
      delay(3000);
      MP_startCoordRound();
    } else {
      MP_showCoordResult();
      resetGame();
    }
  }
}

void MP_showCoordResult() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Coord Scores");
  lcd.setCursor(0, 1); lcd.print("P1: "); lcd.print(MP_coordScoreP1);
  lcd.setCursor(0, 2); lcd.print("P2: "); lcd.print(MP_coordScoreP2);
  lcd.setCursor(0, 3);
  if (MP_coordScoreP1 > MP_coordScoreP2) lcd.print("Overall: P1");
  else if (MP_coordScoreP2 > MP_coordScoreP1) lcd.print("Overall: P2");
  else lcd.print("Overall: Tie");
  delay(5000);
}