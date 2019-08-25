
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
unsigned long tikTime = 0;
unsigned long tokTime = 0;
unsigned long tickLength = 0;
unsigned long tikTimeStart = 0;
unsigned long tokTimeStart = 0;

unsigned long rightTimeStart = 0;
unsigned long leftTimeStart = 0;
unsigned long rightTime = 0;
unsigned long leftTime = 0;

bool tik = true;
bool right = true;
int column = 0;
int columnLength = 0;
bool lastState = HIGH;

void setup() {
  // set the outputs
  for ( int i=pinLow; i < pinHigh; i++) {
    pinMode(i, OUTPUT);
  }
  // Set the sensor pin
  pinMode(inPin, INPUT);
}

void loop() {
  // Get state of sensor
  int state = digitalRead(inPin);
  unsigned long currentMillis = millis();
  // Update the clock and the "Left Right" state
  if (lastState == HIGH && state == LOW){
    tik = !tik;
    if (tik) {
      tokTime = currentMillis - tokTimeStart;
      tikTimeStart = currentMillis;
    } else {
      tikTime = currentMillis - tikTimeStart;
      tokTimeStart = currentMillis;
    }
    // The right side takes longer, so if tik or tok is longer see if we're in that zone.
    right = ((tikTime > tokTime) && right == tik) || ((tokTime > tikTime) && right != tik);
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
  
  unsigned long delta = 0;
  // Calculate the position since last change
  if (right) {
    // Get the delta postion shifted by half the left time.
    delta = currentMillis - (rightTimeStart - (leftTime / 2) );
  } else {
    // Or forward by right time
    delta = currentMillis - (leftTimeStart + rightTime);
  }

  // Check if forward or backward pass
  if (delta <= tickLength || delta >= tickLength + (rightTime/2)) { // Forward pass
    column = delta / columnLength;
  } else { // Backward pass
    column = columns - (delta - tickLength) / columnLength;
  }
  
  // Write that column to the LEDs
  for ( int i=pinLow; i < pinHigh; i++) {
    //byte output = ledBitmasks[i - pinLow] & image[column];
    int mask = ledBitmasks[i - pinLow];
    int output = mask & image[column];
    digitalWrite(i, (output > 0));
    //digitalWrite(i, state);
  }
  
}
