#pragma once

// Memory Game variables
int sequence[MAX_SEQUENCE];
int memStep, memInputP1;
bool activeP1, doneP1;
int scoreP1;

// Reaction Game variables
int reactSeq[REACT_ROUNDS][REACT_LENGTH];
int reactRound, reactStepP1;
unsigned long reactStartTime, finishTimeP1;
int reactScoreP1;
bool doneReactP1;

// Coordination Game variables
int coordSeq[COORD_ROUNDS][COORD_MAX_LEN];
int coordLen[COORD_ROUNDS] = { 2, 3, 4, 5, 6, 7 };
int coordRound, coordStepP1;
unsigned long coordStartTime;
int coordScoreP1;
bool coordDoneP1;


// Memory Game functions

void playMemorySequence() {  
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Level "); lcd.print(memStep);
  lcd.setCursor(0, 1); lcd.print("Watch & remember...");
  delay(500);
  
  for (int i = 0; i < memStep; i++) {
    flashLedAndTone(sequence[i]);
    delay(400);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Your turn!");
  lcd.setCursor(0, 1); lcd.print("Repeat the sequence");
}

void SP_startMemoryGame() {
  memStep = 1;
  memInputP1 = 0;
  activeP1 = true;
  doneP1 = false;
  scoreP1 = 0;
  for (int i = 0; i < MAX_SEQUENCE; i++) sequence[i] = random(NUM_LEDS);
  playMemorySequence();
}


void SP_memoryLoop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (activeP1 && !doneP1 && digitalRead(p1Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i != sequence[memInputP1]) {
        activeP1 = false;
        lcd.clear(); lcd.setCursor(0, 1);
        lcd.print("Failed on Lvl "); lcd.print(memStep);
        gameOverSound();
        delay(1500);
      } else {
        scoreP1++; 
        memInputP1++;
        if (memInputP1 >= memStep) doneP1 = true;
      }
      break;
    }
  }

  if (!activeP1 || memStep > MAX_SEQUENCE) {
    SP_showMemoryResult();
    resetGame();
    return;
  }
  if (doneP1) {
    memStep++;
    memInputP1 = 0;
    doneP1 = false;
    delay(800);
    playLevelUpSound();
    playMemorySequence();
  }
}

void SP_showMemoryResult() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Memory Test Complete");
  lcd.setCursor(0, 1); lcd.print("Your score: "); lcd.print(scoreP1);
  awardMedal(scoreP1, MAX_SEQUENCE);
  delay(5000);
}

// Reaction Game functions
void SP_startReactionGame() {
  reactScoreP1 = 0;
  reactRound = 0;
  for (int r = 0; r < REACT_ROUNDS; r++)
    for (int s = 0; s < REACT_LENGTH; s++)
      reactSeq[r][s] = random(NUM_LEDS);
  
  SP_startReactRound();
}

void SP_startReactRound() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Round "); lcd.print(reactRound + 1);
  lcd.setCursor(0, 1); lcd.print("Watch the sequence...");
  delay(500);
  
  for (int i = 0; i < REACT_LENGTH; i++) {
    flashLedAndTone(reactSeq[reactRound][i]);
    delay(400);
  }
  
  reactStepP1 = 0;
  doneReactP1 = false;
  reactStartTime = millis();
  finishTimeP1 = 0;
  
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Repeat it fast!");
}

void SP_reactionLoop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (!doneReactP1 && digitalRead(p1Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i == reactSeq[reactRound][reactStepP1]) reactScoreP1++;
      else reactScoreP1--;
      if (++reactStepP1 >= REACT_LENGTH) {
        doneReactP1 = true;
        finishTimeP1 = millis() - reactStartTime;
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print("Time: "); lcd.print(finishTimeP1); lcd.print("ms");
        lcd.setCursor(0, 1); lcd.print("Score: "); lcd.print(reactScoreP1);
        reactRound++;
        if (reactRound < REACT_ROUNDS) {
          delay(800);
          SP_startReactRound();
        } else {
          SP_showReactResult();
          resetGame();
        }
      }
      break;
    }
  }
}

void SP_showReactResult() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Reaction Test Done");
  lcd.setCursor(0, 1); lcd.print("Final Score: "); lcd.print(reactScoreP1);
  awardMedal(reactScoreP1, REACT_ROUNDS * 2);
  delay(5000);
}

// Coordination Game functions
void SP_startCoordinationGame() {
  coordScoreP1 = 0;
  coordRound = 0;
  for (int r = 0; r < COORD_ROUNDS; r++) {
    for (int i = 0; i < coordLen[r]; i++) {
      coordSeq[r][i] = random(NUM_LEDS);
    }
  }
  SP_startCoordRound();
}

void SP_startCoordRound() {
  coordStepP1 = 0;
  coordDoneP1 = false;
  coordStartTime = millis();

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Round "); lcd.print(coordRound + 1);
  lcd.setCursor(0, 1); lcd.print("Length: "); lcd.print(coordLen[coordRound]);
  delay(1000);

  for (int i = 0; i < coordLen[coordRound]; i++) {
    flashLedAndTone(coordSeq[coordRound][i]);
    delay(400);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Replicate sequence!");
}

void SP_coordinationLoop() {
  unsigned long elapsed = millis() - coordStartTime;
  lcd.setCursor(0, 3);
  lcd.print("Time: "); lcd.print(elapsed); lcd.print("ms");

  for (int i = 0; i < NUM_LEDS; i++) {
    if (!coordDoneP1 && digitalRead(p1Buttons[i]) == LOW) {
      delay(200); flashLedAndTone(i);
      if (i != coordSeq[coordRound][coordStepP1]) {
        coordDoneP1 = true;
      } else if (++coordStepP1 >= coordLen[coordRound]) {
        coordDoneP1 = true;
        coordScoreP1 += 5;
      }
      break;
    }
  }

  if (coordDoneP1 || elapsed > coordLen[coordRound] * 2000UL) {
    coordRound++;
    if (coordRound < COORD_ROUNDS) {
      delay(800);
      SP_startCoordRound();
    } else {
      SP_showCoordResult();
      resetGame();
    }
  }
}

void SP_showCoordResult() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Coordination Test");
  lcd.setCursor(0, 1); lcd.print("Final Score: "); lcd.print(coordScoreP1);
  awardMedal(coordScoreP1, COORD_ROUNDS * 5);
  delay(5000);
}