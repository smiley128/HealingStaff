#include <Adafruit_NeoPixel.h>
#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(48, PIN, NEO_GRB + NEO_KHZ800);

byte buttonPushCounter = 0;   // counter for the number of button presses
boolean buttonState = 0;         // current state of the button
boolean lastButtonState = 1;     // previous state of the button
boolean pressed = false;
boolean healing = false;
unsigned long previousMillis = 0;
unsigned long previousMillishold = 0;
#define interval 30000 //30 sec
unsigned int cycle = 0;
byte mode = 0;
#define n_modes 3

void setup() {
  strip.begin();
  pinMode(3, INPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, OUTPUT);
  randomSeed(analogRead(3));
  strip.setBrightness(128);
  strip.show();

  while (buttonPushCounter < 1){
    strip.setPixelColor(random(strip.numPixels()), Wheel((cycle+random(64))/2));
    strip.setPixelColor(random(strip.numPixels()),0x000000);
    share();
  }
}

void loop() {

  switch (mode) {
  case 0:
    if(healing){
      digitalWrite(1,1);
      long t = millis() - previousMillis;
      byte  p = map(t, 0, interval, 0, (strip.numPixels()+1));
      strip.setPixelColor(random(p,strip.numPixels()), Wheel((random(32)+96)));
      strip.setPixelColor(random(p), Wheel((random(42))));
      if(t > interval)
        healing = false;
    }
    else{
      digitalWrite(1,0);
      strip.setPixelColor(random(strip.numPixels()), Wheel(random(64)+96));
    }
   
    if (pressed){
    healing = !healing;
    if(healing)
      previousMillis = millis();

    pressed = false;
  }
    break;
  case 1:
    strip.setPixelColor((cycle+random(3))%64, Wheel(((((cycle+random(5))%32)+strip.numPixels()+random(7))%256)));
    break;
  case 2:
  
    if (cycle%20 == 0)
      if (cycle%200 >= 100)
      allStrip(0xFF0000);
      else
      allStrip(0x0000FF);
    if ((cycle+10)%20 == 0)
    allStrip(0x000000);
    break;
  }

if (mode < 2)
strip.setPixelColor(random(strip.numPixels()),0);

share();  

}

void allStrip(uint32_t color){
  for (int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i,color);
  }
}

void share(){  
  delay(4);
  buttonCheck();
  cycle++;
  strip.show();
}

void buttonCheck(){
  buttonState = digitalRead(0);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      buttonPushCounter++;
      pressed = true;
      previousMillishold = millis();
    }
  }
  else{
    if (buttonState == LOW) {
      long t = millis() - previousMillishold;
      if(t > 2000){
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







