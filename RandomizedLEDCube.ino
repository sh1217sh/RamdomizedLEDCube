/**
 * 
 * Randomized LED Cube
 * 
 * Author: Sung-ho Lee (a.k.a. YamaeCoder) <sh1217sh@gmail.com>
 * 
 * Hardware configuration : Common cathod for each layer. Any size you want as the number of Arduino pins allows.
 * 
 * TESTED WITH ARDUINO UNO AND CUSTOM MADE LED CUBE. THE AUTHOR DOES NOT GARANTEE WHETHER THIS SOFTWARE IS APPLICATABLE ON OTHER ENVIRONMENTS.
 * 
 * ***** LICENSE (IMPORTANT!) *****
 * Copyright (C) 2015 Sung-ho Lee (a.k.a. YamaeCoder) <sh1217sh@gmail.com>
 * 
 * You can do whatever you want including modifying, redistributing, using commocially, etc. if you retain this license claim.
 * ********************************
 * 
 */

// ==== Configuration ====
#define NUMBER_OF_LAYERS 2
#define LEDS_ON_A_LAYER 4
#define DURATION 750

const byte layers[NUMBER_OF_LAYERS] = {9, 8};
const byte leds[LEDS_ON_A_LAYER] = {13, 12, 11, 10};
// =======================

boolean currentPattern[NUMBER_OF_LAYERS][LEDS_ON_A_LAYER];

long lastMillis = 0;

void setup() {
  // Set pins to output mode and initialize.
  for (int i = 8; i<=13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  //Serial.begin(9600);
}

void loop() {
  // Change LED pattern when setted time is over.
  if (millis() - lastMillis > DURATION) {
    changePattern();
    lastMillis = millis();
  }
  display();
}

void display() {
  // Display current pattern on the cube.
  // Uses dynamic driving
  for (int i=0; i<NUMBER_OF_LAYERS; i++) {
    digitalWrite(layers[i], LOW);
    for (int j=0; j<LEDS_ON_A_LAYER; j++) {
      digitalWrite(leds[j], currentPattern[i][j]);
    }
    digitalWrite(layers[i], HIGH);
    delay(1);
    digitalWrite(layers[i], LOW);
  }
}

void changePattern() {
  // Randomize the pattern.
  for (int i=0; i<NUMBER_OF_LAYERS; i++) {
    for (int j=0; j<LEDS_ON_A_LAYER; j++) {
      currentPattern[i][j] = random(0, 2);
    }
  }
}

// For debuging purpose. Call this function if you need it.
void printCurrentPattern() {
  for (int i=0; i<NUMBER_OF_LAYERS; i++) {
    for (int j=0; j<LEDS_ON_A_LAYER; j++) {
      Serial.print(currentPattern[i][j]);
    }
    Serial.println("");
  }
  Serial.println("");
}

