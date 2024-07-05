
const int pinLow =  2;// the number of the LED pin
const int pinHigh = 10;
const int inPin = 11;
const byte image[] = {0x80,0xFF,0x80,0x80,0x00,0xFF,0x89,0x89,0x81,0x00,0xF9,0x89,0x89,0x8F,0x00,0x80,0xFF,0x80,0x80,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF};
const int columns = 32;
const int ledBitmasks[] = {
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001
  };

unsigned long previousMillis = 0;
float tikTime = 0;
float tokTime = 0;
float tickLength = 0;
unsigned long tikTimeStart = 0;
unsigned long tokTimeStart = 0;

unsigned long rightTimeStart = 0;
unsigned long leftTimeStart = 0;
float rightTime = 0;
float leftTime = 0;

bool tik = true;
bool right = true;
int column = 0;
float columnLength = 0;
bool lastState = HIGH;

float speedModifierRadius = .5;
float speedModifierPivot = 1.5;

void setup() {
  // set the outputs
  for ( int i=pinLow; i < pinHigh; i++) {
    pinMode(i, OUTPUT);
  }
  // Set the sensor pin
  pinMode(inPin, INPUT);
}

float timeshift(float delta) {
  float base = delta / tickLength;
  float mod = 0.5 * cos(3.14 * base - 3.14) + 0.5;
  return mod * tickLength;
}

void loop() {
  // Get state of sensor
  int state = digitalRead(inPin);
  unsigned long currentMillis = millis();
  // Update the clock and the "Left Right" state
  if (lastState == LOW && state == HIGH){
    tik = !tik;
    if (tik) {
      tokTime = currentMillis - tokTimeStart;
      tikTimeStart = currentMillis;
    } else {
      tikTime = currentMillis - tikTimeStart;
      tokTimeStart = currentMillis;
    }
    // The right side takes longer, so if tik or tok is longer see if we're in that zone.
    right = ((tikTime > tokTime) && tik) || ((tokTime > tikTime) && !tik);
    // Set relative variables
    rightTimeStart = (tik == right)? tikTimeStart : tokTimeStart;
    leftTimeStart = (tik == right)? tokTimeStart : tikTimeStart;
    rightTime = (tik == right)? tikTime : tokTime;
    leftTime = (tik == right)? tokTime : tikTime;
    // Calculate the time it takes to make one whole swipe
    tickLength = (tokTime / 2) + (tikTime /2);
    // Calculate the length of each column
    columnLength = tickLength / columns;
  }
  lastState = state;
  
  float delta = currentMillis - rightTimeStart;

  // Account for the passage of half of left by shifting the time a bit.
  delta = delta + (leftTime/2);
  
  // If delta is less than one tick length, then it's simple math
  if (delta < tickLength) {
    delta = delta;
  } else if (delta > tickLength && delta < (tickLength * 2)){ // If delta is longer than a tick length, then we minus and go backwards till we reach more than 2 tickLenght
    delta = (tickLength - (delta - tickLength));
  } else if (delta > (tickLength * 2)){ // If delta is longer than two strokes then it's returning.
    delta = (delta - (tickLength * 2));
  }
  // Shift time with a sin() function
  delta = timeshift(delta);
  
  column = delta / columnLength;
  // Write that column to the LEDs
  for ( int i=pinLow; i <= pinHigh; i++) {
    //byte output = ledBitmasks[i - pinLow] & image[column];
    int mask = ledBitmasks[i - pinLow];
    int output = mask & image[column];
    digitalWrite(i, (output != 0));
    //digitalWrite(i, state);
  }
  
}
