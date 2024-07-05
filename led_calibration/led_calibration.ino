// This script will step through each LED in order
// It will blink for the number of the pin on the microcontroller


const long blinkSpeed = 1000;
int ledPins[] = {4, 6, 9, 10, 8, 7, 5, 3};
int currentLed = 0;
int currentBlinkCount = 0;
long nextBlinkUpdate = 0;

void setup() {
  // set the outputs
  for ( int i=0; i <= 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Start with the first pin
  currentLed = 0;
  currentBlinkCount = 0;

}

void loop() {
  long now = millis();

  // Check if it's time to update our state
  if (now < nextBlinkUpdate) {
    return;
  }
  nextBlinkUpdate = now + blinkSpeed;

  // Update the pin counter
  if (currentBlinkCount > (currentLed + 1 ) * 2) {
    // Go to next pin
    currentLed++;
    currentBlinkCount = 0;
    if (currentLed > 7) {
        currentLed = 0;
    }
  }

  // Update our LED state
  bool ledState = currentBlinkCount % 2 == 0;
  currentBlinkCount++;

  // Write updates to LED pins
  for ( int i=0; i <= 7; i++) {
    if (i == currentLed) {
      digitalWrite(ledPins[i], ledState);
    } else {
      digitalWrite(ledPins[i], false);
    }
  }
}
