//LED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

//Include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

bool alreadyPlayed1 = false;

bool alreadyPressedTalk = false;
// bool alreadyPlayed = false;

//Button define
#define BUTTONA_PIN 5
#define BUTTONB_PIN 2

//These are the pins used for the breakout example
#define BREAKOUT_RESET 9  // VS1053 reset pin (output)
#define BREAKOUT_CS 10    // VS1053 chip select pin (output)
#define BREAKOUT_DCS 8    // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET -1  // VS1053 reset pin (unused!)
#define SHIELD_CS 7      // VS1053 chip select pin (output)
#define SHIELD_DCS 6     // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4  // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3  // VS1053 Data request, ideally an Interrupt pin

//STATE MACHINE
enum State { base,
             call,
             talk };

State state = base;

//display
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
char *welcome = "    0-800-STRESS-LINE    ";

//player
Adafruit_VS1053_FilePlayer musicPlayer =
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

/////////SETUP

void setup() {

  Serial.begin(9600);

  //display
  alpha4.begin(0x70);  // pass in the address
  alpha4.clear();
  alpha4.writeDisplay();

  //button
  pinMode(BUTTONA_PIN, INPUT_PULLUP);
  pinMode(BUTTONB_PIN, INPUT_PULLUP);

  Serial.println("Adafruit VS1053 Simple Test");

  if (!musicPlayer.begin()) {  // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1)
      ;  // don't do anything more
  }

  // list files
  printDirectory(SD.open("/"), 0);

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20, 20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}

/////////LOOP
void loop() {

  switch (state) {
    case base:
      loopBase();
      break;
    case call:
      loopCall();
      break;
    case talk:
      loopTalk();
      break;
  }

  // // File is playing in the background
  // if (musicPlayer.stopped()) {
  //   Serial.println("Done playing music");
  //   while (1) {
  //     delay(10);  // we're done! do nothing...
  //   }
  // }
  // if (Serial.available()) {
  //   char c = Serial.read();

  //   // if we get an 's' on the serial console, stop!
  //   if (c == 's') {
  //     musicPlayer.stopPlaying();
  //   }

  //   // if we get an 'p' on the serial console, pause/unpause!
  //   if (c == 'p') {
  //     if (! musicPlayer.paused()) {
  //       Serial.println("Paused");
  //       musicPlayer.pausePlaying(true);
  //     } else {
  //       Serial.println("Resumed");
  //       musicPlayer.pausePlaying(false);
  //     }
  //   }
  // }

  // delay(100);
}

bool buttonAPressed() {
  static bool buttonA = HIGH;

  //button
  bool buttonAState = digitalRead(BUTTONA_PIN);
  if (buttonAState != buttonA) {
    buttonA = buttonAState;
    Serial.print("button A changed ");
    Serial.println(buttonA);
    delay(20);  //evite le rebond

    if (buttonA == LOW) {
      return true;
    }
  }
  return false;
}

bool buttonBPressed() {
  static bool buttonB = HIGH;
  //button
  bool buttonBState = digitalRead(BUTTONB_PIN);
  if (buttonBState != buttonB) {
    buttonB = buttonBState;
    Serial.print("button B changed ");
    Serial.println(buttonB);
    delay(20);  //evite le rebond

    if (buttonB == LOW) {
      return true;
    }
  }
  return false;
}

/// File listing helper
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      //Serial.println("**nomorefiles**");
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
