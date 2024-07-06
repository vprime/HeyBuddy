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

# Hardware
HD74LS244P 5M16
Octal 3 state buffer
https://learn.adafruit.com/digital-circuits-6-eprom-emulator/the-74244-octal-tristate-buffer


ATMEL542
24C08A
P127  D
2 Pin serial eeprom with analog pins attached to the power.

S8050 2w NPN transitor
Center pin attached to 1k (brn, blk, red, gold) resistor
Triggers the motor coil

Swing arm resonance cycle peak to peak 0.11666667sec

# Development log
Pin 10 wasn't triggering, but it was because my loop skipped the last pin.
I had all the pins to the LED's jumbled up, but now that I have looked up the specs on the buffer and LED's i was able to fix that issue.
I cut the lines from the microcontroller as the old microcontroller was causing interference. 
While testing, I accidently shorted the 12v to something on the back of the device and let out the magic smoke.
I don't see any scorch marks on any of the discreet parts, and didn't catch where the smoke came out from. I think we may just be left with a dead board now, I should double check with the remote.
Remote flashes, but won't "power" the device.
I might be able to trigger the motor from the arduino, since the arduino is fine and the LED's are fine. 
Triggering works, but this will need a lot of calibration. Probably need to ramp up the power graduly. Best result so far has been 60ms on every 120ms.
While testing, I broke the power neg off the 12v input. These wires were old, I should just replace with fresh ones.
I should break the signal between the old microcontroller and the motor input signal to prevent interferrance. 
While testing with the motor, I realized that the break beam sensor wasn't getting picked up by the arduino but it was powered and working.
break beam works once I made the pin INPUT_PULLUP instead of INPUT.
The swing arm has a constant resonance, so if we pulse the motor at that rate it should work.
To measure the resonance, I manually swing the arm and let it sway for a bit while recording in slow-mo. 

# Recording swing rate 1/8th time
Video is 30fps at 1/8th (0.125) of real time
Early
00:00:30,27
- 00:00:31,11 (14f)
00:00:31,25 (14f)
- 00:00:32,09
00:00:32,23 (14f)
~0.93333333 sec per cycle

Mid
00:01:13,23
-00:01:14,07 (14f)
00:01:14,21 (14f)
-00:01:15,06 (15f)
00:01:15,19 (13f)
~0.93333333 sec per cycle


Falloff
00:02:00,14
-00:02:00,28 (14f)
00:02:01,12 (14f)
-00:02:01,26 (14f)
00:02:02,10 (14f)
~0.93333333 sec per cycle

Resonance frequency should be 0.11666667sec or 8.571428hz
Power on motor for 0.058333333333333sec
rate in mills (116.6666666)
power in mills (58.33333333333)
This makes sense, as 120/60 seemed to be really close.
