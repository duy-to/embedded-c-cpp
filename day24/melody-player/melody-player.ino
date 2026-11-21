#include "Button.h"
#define C4 262
#define G4 392
#define A4 440
enum PlayerState { PLAYER_STOPPED,
                   PLAYER_PLAYING };
PlayerState playerState = PLAYER_STOPPED;
int noteIndex = 0;
unsigned long noteStartTime = 0;
const int buttonPin = 0;
const int buzzerPin = 18;
unsigned long note[] = { C4, C4, G4, G4, A4, A4, G4 };
unsigned long timeMs[] = { 400, 400, 400, 400, 400, 400, 800 };
Button button = { buttonPin, 1, 1, 0, 50 };
int numberOfTone = sizeof(note) / sizeof(note[0]);
void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  setUpButton(&button);
}

void loop() {
  unsigned long now = millis();
  bool pressed = buttonPressed(&button);

  switch (playerState) {
    case PLAYER_STOPPED:
      if (pressed) {  // start
        playerState = PLAYER_PLAYING;
        tone(buzzerPin, note[noteIndex]);
        noteStartTime = now;
      }
      break;

    case PLAYER_PLAYING:
      if (pressed) {  // stop right away
        noTone(buzzerPin);
        playerState = PLAYER_STOPPED;
      } else if (now - noteStartTime >= timeMs[noteIndex]) {  // note finished?
        noteIndex = (noteIndex + 1) % numberOfTone;           // next note, wrap to 0
        tone(buzzerPin, note[noteIndex]);
        Serial.print("Note ");
        Serial.print(noteIndex);
        Serial.print(": ");
        Serial.print(note[noteIndex]);
        Serial.print(" Hz, ");
        Serial.print(timeMs[noteIndex]);
        Serial.println(" ms");
        noteStartTime = now;
      }
      break;
  }
}
