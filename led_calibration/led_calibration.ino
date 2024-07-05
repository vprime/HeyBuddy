// This script will step through each LED in order
// It will blink for the number of the pin on the microcontroller

const int pinLow =  2; // the number of the LED pin
const int pinHigh = 10;
const long blinkSpeed = 1000;

int currentPin = 0;
int currentBlinkCount = 0;
long nextBlinkUpdate = 0;

void setup() {
  // set the outputs
  for ( int i=pinLow; i < pinHigh; i++) {
    pinMode(i, OUTPUT);
  }

  // Start with the first pin
  currentPin = pinLow;
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
  if (currentBlinkCount > currentPin * 2) {
    // Go to next pin
    currentPin++;
    currentBlinkCount = 0;
    if (currentPin > pinHigh) {
      currentPin = pinLow;
    }
  }

  // Update our LED state
  bool ledState = currentBlinkCount % 2 == 0;

  // Write updates to LED pins
  for ( int i=pinLow; i < pinHigh; i++) {
    if (i == currentPin) {
      digitalWrite(i, ledState);
    } else {
      digitalWrite(i, false);
    }
  }
}
