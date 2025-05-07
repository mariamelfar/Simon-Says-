#pragma once
#include "Constants.h"
#include "Globals.h"

void initLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void flashLedAndTone(int idx) {
  digitalWrite(ledPins[idx], HIGH);
  tone(buzzer, gameTones[idx]);
  delay(300);
  digitalWrite(ledPins[idx], LOW);
  noTone(buzzer);
}

void turnOffAllLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void playLevelUpSound() {
  tone(buzzer, NOTE_E4);
  delay(150);
  tone(buzzer, NOTE_G4);
  delay(150);
  tone(buzzer, NOTE_E5);
  delay(150);
  tone(buzzer, NOTE_C5);
  delay(150);
  tone(buzzer, NOTE_D5);
  delay(150);
  tone(buzzer, NOTE_G5);
  delay(150);
  noTone(buzzer);
}

void gameOverSound() {
  tone(buzzer, NOTE_DS5);
  delay(300);
  tone(buzzer, NOTE_D5);
  delay(300);
  tone(buzzer, NOTE_CS5);
  delay(300);
  for (byte i = 0; i < 10; i++) {
    for (int pitch = -10; pitch <= 10; pitch++) {
      tone(buzzer, NOTE_C5 + pitch);
      delay(5);
    }
  }
  noTone(buzzer);
}