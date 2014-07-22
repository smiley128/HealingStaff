HealingStaff
============

Arduino sketch for my NeoPixel LED "Healing" timer staff.

##Pin configuration
- Pin 0: Button
- Pin 1: LED (onboard LED on the trinket)
- Pin 2: NeoPixel strip

##How to use
When the sketch starts it begins in a rainbow standby pattern, just push the button to start the timer. The LED will turn on and the NeoPixel strip will start to become more and more green as the timer progresses when the time is up the NeoPixel strip will turn back to it pink/purple standby pattern.

While the timer is going the button can be pushed at any time to reset the timer and return to the pink/purple standby pattern.

###Extra modes
There are 3 extra modes that can be accessed buy holding down the button for 1 and a half seconds, but note this takes it out of standby-healing mode and to return to the standby-healing mode you need to ether reset the microcontroller or cycle through them until you get back to standby-healing mode.

The extra modes are
- Flame: Tries to emulate a orangey-red flame
- All White: Self explanatory, all the LEDs got white. It also sets the brightness to 255, but will revert back to the defalt brightness when changing to the next mode.
- Police Lights: LEDs flash red and blue. [warning: may cause epileptic seizures]

##Dependencies
[Adafruit NeoPixel][neopixel] library 

[neopixel]:  https://github.com/adafruit/Adafruit_NeoPixel
