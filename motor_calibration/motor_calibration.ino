
int motorDrivePin = 2;
int motorSensorPin = 11;

long motorPulseLength = 10;
long motorPulseDelay = 100;
long pulseStart = 0;


void setup() {
  pinMode(motorSensorPin, INPUT);
  pinMode(motorDrivePin, OUTPUT);
}

void loop() {
  long now = millis();
  if (now < pulseStart + motorPulseLength) {
    digitalWrite(motorDrivePin, true);
  } else {
    digitalWrite(motorDrivePin, false);
  }
  if (now > pulseStart + motorPulseDelay) {
    pulseStart = now;
  }
}