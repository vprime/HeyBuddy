# [WIP] HeyBuddy
The Hey Buddy is an 8 led Persistance of Vision display controller for Arduino

# Image Format
32 Byte array of images formatted as most signifigant bit on the top, in order of left to right.
When complete, send the image data as blocks of 32 Bytes through a USB serial connection.
The device will display image data as it's sent, and will persist on the last given frame.

# Arduino pinout
Uses 8 pins in a row for LED output, mark the first pin and last pin. 
Uses 1 pin for light break sensor. It is assumed the postion of the light break sensor is to the left of center, the program may need to be adjusted if your model isn't.
May god save you if the sensor is in the middle.

