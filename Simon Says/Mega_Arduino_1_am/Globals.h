#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

// ---- Shared state ----
// Use the smallest type you need (uint8_t over int) on AVR
extern uint8_t gameMode;
extern uint8_t playerMode;

void showPlayerSelect();
void resetGame();
void showGameSelect();
void awardMedal(int score, int maxPossible);
void flashLedAndTone(int idx);
void playLevelUpSound();
void gameOverSound();

// — Single-player mode APIs —
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

// — Two-player mode APIs —
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

#endif  // GLOBALS_H
