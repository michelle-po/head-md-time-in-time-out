void setupBase() {
  musicPlayer.stopPlaying();
  Serial.println("setup base");
}

void loopBase() {
  //send a message!
  for (uint8_t i = 0; i < strlen(welcome) - 4; i++) {
    alpha4.writeDigitAscii(0, welcome[i]);
    alpha4.writeDigitAscii(1, welcome[i + 1]);
    alpha4.writeDigitAscii(2, welcome[i + 2]);
    alpha4.writeDigitAscii(3, welcome[i + 3]);
    alpha4.writeDisplay();

    for (uint8_t i = 0; i < 30; i++) {

      delay(10);

      if (buttonAPressed()) {
        state = call;
        Serial.println("A pressed");
        Serial.println(state);
        setupCall();
        return;
      }
    }

    delay(300);
  }
}