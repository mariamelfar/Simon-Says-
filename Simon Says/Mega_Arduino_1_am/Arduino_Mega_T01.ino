int gameMode = 0;
int playerMode = 0;   // 1 = Single-player, 2 = Two-player

void setup() {
  Serial.begin(9600);

  // LCD init
  lcd.init();
  lcd.backlight();

  // Hardware init
  initLEDs();
  initButtons();

  // Start with welcome screen and player selection
  showWelcomeScreen();

  //random setup
  randomSeed(analogRead(A0));
}

void loop() {
  // Reset button (pin 13) always takes priority
  if (digitalRead(resetButton) == LOW) {
    resetGame();
    delay(200);  // debounce
    return;
  }

  // 1) Player selection stage
  if (playerMode == 0) {
    handlePlayerSelection();  //Select Single or 2-Player Mode 
    return;
  }

  // 2) Game mode selection stage
  if (gameMode == 0) {
    handleGameSelection();   //Select Game Mode
    return;
  }

  // 3) In-game loop: call the appropriate mode handler
  if (playerMode == 1) {
    switch (gameMode) {
      case 1: SP_memoryLoop();      break;
      case 2: SP_reactionLoop();    break;
      case 3: SP_coordinationLoop();break;
    }
  } else if (playerMode == 2) {
    switch (gameMode) {
      case 1: MP_memoryLoop();      break;
      case 2: MP_reactionLoop();    break;
      case 3: MP_coordinationLoop();break;
    }
  }
}

void resetGame() {
  // Turn off LEDs
  turnOffAllLEDs();

  // Reset state
  gameMode = 0;
  playerMode = 0;

  // Go back to welcome screen
  showWelcomeScreen();
}
