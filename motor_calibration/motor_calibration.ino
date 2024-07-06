
int motorDrivePin = 2;
int motorSensorPin = 11;

int ledMotor = 4;
int ledSensor = 3;

long motorPulseLength = 58;
long motorPulseDelay = 117;
long pulseStart = 0;


void setup() {
  pinMode(motorSensorPin, INPUT_PULLUP);
  pinMode(motorDrivePin, OUTPUT);
  pinMode(ledMotor, OUTPUT);
  pinMode(ledSensor, OUTPUT);
}

void loop() {
  //int sensorValue = digitalRead(motorSensorPin);
  // int motorValue = digitalRead(motorDrivePin);
  // Serial.println(sensorValue + ", "  + motorValue);
  // delay(1);
  long now = millis();

  digitalWrite(ledSensor, digitalRead(motorSensorPin));
  if (now < pulseStart + motorPulseLength) {
    digitalWrite(motorDrivePin, true);
    digitalWrite(ledMotor, false);
  } else {
    digitalWrite(motorDrivePin, false);
    digitalWrite(ledMotor, true);
  }
  if (now > pulseStart + motorPulseDelay) {
    pulseStart = now;
  }

}