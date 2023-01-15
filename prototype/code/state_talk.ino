unsigned long countDown = 0;
unsigned long lastMs = 0;

enum StoryState { NONE,
                  STORY1,
                  STORY2,
                  STORY3,
                  STORY4,
                  STORY5,
                  STORY6,
                  STORY7 };

StoryState storyState = NONE;

void setupTalk() {

  countDown = 90 * 1000l;  //Milliseconds --> 90 seconds --> l pour valeur long
  lastMs = millis();

  Serial.println("setup talk");

  //PLAY FIRST QUESTION
  Serial.println(F("Playing track 003"));
  musicPlayer.startPlayingFile("/track003.mp3");
}

void loopTalk() {
  //GENERAL COUNTDOWN
  unsigned long ms = millis();
  int deltaTime = ms - lastMs;
  lastMs = ms;
  int minutes = countDown / 60000;
  int seconds = (countDown % 60000) / 1000;

  char buffer[4];
  buffer[0] = String(minutes / 10)[0];
  buffer[1] = String(minutes % 10)[0];
  buffer[2] = String(seconds / 10)[0];
  buffer[3] = String(seconds % 10)[0];

  alpha4.writeDigitAscii(0, buffer[0]);
  alpha4.writeDigitAscii(1, buffer[1], true);
  alpha4.writeDigitAscii(2, buffer[2]);
  alpha4.writeDigitAscii(3, buffer[3]);

  // write it out!
  alpha4.writeDisplay();
  delay(200);
  countDown -= deltaTime;

  // COUNTDOWN ENDED
  if (minutes < 1 && seconds < 1) {
    Serial.println(F("Playing track 007"));
  musicPlayer.startPlayingFile("/track007.mp3");

    for (int i = 0; i < 4; i++) {
      alpha4.writeDigitRaw(0, 0xFFFF);
      alpha4.writeDigitRaw(1, 0xFFFF);
      alpha4.writeDigitRaw(2, 0xFFFF);
      alpha4.writeDigitRaw(3, 0xFFFF);
      alpha4.writeDisplay();
      delay(200);
      alpha4.writeDigitRaw(0, 0x0000);
      alpha4.writeDigitRaw(1, 0x0000);
      alpha4.writeDigitRaw(2, 0x0000);
      alpha4.writeDigitRaw(3, 0x0000);
      alpha4.writeDisplay();
      delay(200);
    }
    state = base;
    setupBase();
  }


//   if(digitalRead(BUTTONA_PIN)==LOW){
//  Serial.println("LOW");
//  musicPlayer.stopPlaying();
//  musicPlayer.startPlayingFile("/track004.mp3");    
//   }

  if (buttonBPressed()) {
Serial.println(F("Playing track 007"));
  musicPlayer.startPlayingFile("/track007.mp3");

    for (int i = 0; i < 4; i++) {
      alpha4.writeDigitRaw(0, 0xFFFF);
      alpha4.writeDigitRaw(1, 0xFFFF);
      alpha4.writeDigitRaw(2, 0xFFFF);
      alpha4.writeDigitRaw(3, 0xFFFF);
      alpha4.writeDisplay();
      delay(200);
      alpha4.writeDigitRaw(0, 0x0000);
      alpha4.writeDigitRaw(1, 0x0000);
      alpha4.writeDigitRaw(2, 0x0000);
      alpha4.writeDigitRaw(3, 0x0000);
      alpha4.writeDisplay();
      delay(200);
    }
    state = base;
    setupBase();
  }

}

// void playStory() {
//   switch (storyState) {
//       // case NONE:
//       //patternNone();
//       //    break;
//     case STORY1:
//       setup1();
//       // patternStory1();
//       break;
      // case STORY2:
      // setup2();
      //   patternStory2();
      //  break;
      // case STORY3:
      //  patternStory3();
      //  break;
      // case STORY4:
      //   //patternStory4();
      //   break;
      // case STORY5:
      //   // patternStory5();
      //   break;
      // case STORY6:
      //   // patternStory6();
      //   break;
  //}
//}
