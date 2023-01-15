void setupCall() {
  Serial.println("setup call");
  alpha4.clear();
  alpha4.writeDisplay();
  Serial.println(F("Playing track 002"));
  musicPlayer.startPlayingFile("/track002.mp3");
}

void loopCall() {
  //LED ANIMATION
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

  //RESTART RINGTONE
  if (buttonAPressed()) {
    Serial.println("A pressed");
    state = call;
    setupCall();
    return;
  }

  //START TALK
  if (buttonBPressed()) {
    musicPlayer.stopPlaying();
    alpha4.clear();
    alpha4.writeDisplay();
    Serial.println("B pressed");
    state = talk;
    setupTalk();
    return;
  }
}