#include <Adafruit_NeoPixel.h>

#define ButtonPin 0
#define LEDpin 1
#define NeoPixelPin 2
#define nPixels 48 // Number of NeoPixels
#define Brightness 128 // Brightness (For all modes except mode 2 'All White')
#define HoldTime 1500 // Button hold time to change modes
#define interval 30000 // Interval for healing 30 sec
#define GlobalTickDelay 4 //The length of time between each loop

#define n_modes 4 // number of modes 
boolean buttonState = 0;         // current state of the button
boolean lastButtonState = 1;     // previous state of the button
boolean pressed = false;
boolean healing = false;
unsigned long previousMillis = 0;
unsigned long previousMillishold = 0;
unsigned long cycle = 0; 
byte mode = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nPixels, NeoPixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(LEDpin, OUTPUT);

  while (!pressed){ //rainbow standby 
    strip.setPixelColor(random(strip.numPixels()), Wheel((cycle+random(64))/2));
    strip.setPixelColor(random(strip.numPixels()),0);
    share();
  }
  randomSeed(millis());
}

void loop() {

  switch (mode) {
  case 0: // healing and standby
    if(healing){ //healing mode
      digitalWrite(LEDpin,1);
      long t = millis() - previousMillis;
      byte p = map(t, 0, interval, 0, (strip.numPixels()+1));
      strip.setPixelColor(random(p,strip.numPixels()), Wheel((random(32)+96)));
      strip.setPixelColor(random(p), Wheel((random(42))));
      if(t > interval)
        healing = false;
    }
    else{ //standby mode
      digitalWrite(LEDpin,0);
      strip.setPixelColor(random(strip.numPixels()), Wheel(random(64)+96));
    }

    if (pressed){
      healing = !healing;
      if(healing){
        previousMillis = millis();
      }
      pressed = false;
    }
    strip.setPixelColor(random(strip.numPixels()),0);
    break;  

  case 1:// Flame 
    strip.setPixelColor((cycle+random(3))%strip.numPixels(), Wheel(((((cycle+random(5))%32)+48+random(7))%256)));
    strip.setPixelColor(random(strip.numPixels()),0);
    break;

  case 2: // All White
    strip.setBrightness(255);
    allStrip(0xFFFFFF);
    break;
  case 3://Police Lights

    if (cycle%20 == 0)
      if (cycle%200 >= 100)
        allStrip(0xFF0000);
      else
        allStrip(0x0000FF);
    if ((cycle+10)%20 == 0)
      allStrip(0x000000);
    break;
  }

  share();  

}

void allStrip(uint32_t color){
  for (int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i,color);
  }
}

void share(){  
  delay(GlobalTickDelay);
  buttonCheck();
  cycle++;
  strip.show();
  strip.setBrightness(128);
}

void buttonCheck(){
  buttonState = digitalRead(ButtonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      pressed = true;
      previousMillishold = millis();
    }
  }
  else{
    if (buttonState == LOW) {
      unsigned long t = millis() - previousMillishold;
      if(t > HoldTime){
        mode++;
        mode=mode%n_modes;
        previousMillishold = millis();
      }
    }
  }

  lastButtonState = buttonState;
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
