#pragma once
#include <LiquidCrystal_I2C.h>
#include "Globals.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

void showWelcomeScreen() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(" Welcome to our Game!");
  lcd.setCursor(0, 1); lcd.print(" Get Ready to Play!");
  lcd.setCursor(0, 2); lcd.print("Powered by the Team:");
  lcd.setCursor(0, 3); lcd.print("  Pixel Pioneers :)");
  delay(3000);
  showPlayerSelect();
}

void showPlayerSelect() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Select Player Mode:");
  lcd.setCursor(0, 0); lcd.print("How many players?");
  lcd.setCursor(0, 2); lcd.print("Red=1P | Blue=2P");
  lcd.setCursor(0, 3); lcd.print("Waiting for input...");
  delay(2000);
}

void showGameSelect() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Choose Game Mode:");
  lcd.setCursor(0, 1); lcd.print("R: Memory Race");
  lcd.setCursor(0, 2); lcd.print("B: Fast Reaction");
  lcd.setCursor(0, 3); lcd.print("G: Coordination");
  delay(2000);
}



void awardMedal(int score, int maxPossible) {
  float percentage = (float)score / maxPossible;
  
  lcd.setCursor(0, 2);
  if (percentage >= 0.8) {
    lcd.print("GOLD MEDAL!Excellent");
  } else if (percentage >= 0.6) {
    lcd.print("SILVER MEDAL! Great!");
  } else if (percentage >= 0.4) {
    lcd.print("BRONZE MEDAL! Good!");
  } else {
    lcd.print("Keep practicing!");
  }
  
  lcd.setCursor(0, 3);
  lcd.print("You scored "); 
  lcd.print((int)(percentage * 100)); 
  lcd.print("%");
}