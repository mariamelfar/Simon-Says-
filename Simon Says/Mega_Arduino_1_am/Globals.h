#pragma once

// Global variables shared across all files
extern int gameMode;
extern int playerMode;
extern LiquidCrystal_I2C lcd;

void showPlayerSelect();
void resetGame();
void showGameSelect();
void awardMedal(int score, int maxPossible);
void flashLedAndTone(int idx);
void playLevelUpSound();
void gameOverSound();

// Single Mode functions
void SP_startMemoryGame();
void SP_memoryLoop();
void SP_showMemoryResult();
void SP_startReactionGame();
void SP_startReactRound();
void SP_reactionLoop();
void SP_showReactResult();
void SP_startCoordinationGame();
void SP_startCoordRound();
void SP_coordinationLoop();
void SP_showCoordResult();

// Multi Mode functions
void MP_startMemoryGame();
void MP_memoryLoop();
void MP_showMemoryResult();
void MP_startReactionGame();
void MP_startReactRound();
void MP_reactionLoop();
void MP_showReactResult();
void MP_startCoordinationGame();
void MP_startCoordRound();
void MP_coordinationLoop();
void MP_showCoordResult();
