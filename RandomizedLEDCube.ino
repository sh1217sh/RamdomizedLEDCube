/**
 *
 * Randomized LED Cube
 *
 * Author: Sung-ho Lee (a.k.a. NullPointer) <sh1217sh@gmail.com>
 *
 * Hardware configuration : Common cathod for each layer. Any size you want as the number of Arduino pins allows.
 *
 * TESTED WITH ARDUINO UNO AND CUSTOM MADE LED CUBE. THE AUTHOR DOES NOT GARANTEE WHETHER THIS SOFTWARE IS APPLICATABLE ON OTHER ENVIRONMENTS.
 *
 * ***** LICENSE (IMPORTANT!) *****
 * The MIT License.
 * Copyright (C) 2015 Sung-ho Lee (a.k.a. NullPointer) <sh1217sh@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * ********************************
 *
 */

// ==== Configuration ====
#define NUMBER_OF_LAYERS 2
#define LEDS_ON_A_LAYER 4
#define INTERVAL 750

const byte layers[NUMBER_OF_LAYERS] = {5, 4};
const byte leds[LEDS_ON_A_LAYER] = {3, 2, 1, 0};
// =======================

boolean currentPattern[NUMBER_OF_LAYERS][LEDS_ON_A_LAYER];

long lastMillis = 0;

void setup() {
  // Set pins to output mode and initialize.
  byte i;
  for (i = 0; i < NUMBER_OF_LAYERS; i++) {
    pinMode(layers[i], OUTPUT);
  }
  for (i = 0; i < LEDS_ON_A_LAYER; i++) {
    pinMode(leds[i], OUTPUT);
  }

  //Serial.begin(9600);
}

void loop() {
  // Change LED pattern when setted time is over.
  if (millis() - lastMillis > INTERVAL) {
    changePattern();
    lastMillis = millis();
  }
  display();
}

void display() {
  // Display current pattern on the cube.
  // Uses dynamic driving
  for (byte i=0; i<NUMBER_OF_LAYERS; i++) {
    digitalWrite(layers[i], LOW);
    for (byte j=0; j<LEDS_ON_A_LAYER; j++) {
      digitalWrite(leds[j], currentPattern[i][j]);
    }
    digitalWrite(layers[i], HIGH);
    delay(1);
    digitalWrite(layers[i], LOW);
  }
}

void changePattern() {
  // Randomize the pattern.
  for (byte i=0; i<NUMBER_OF_LAYERS; i++) {
    for (byte j=0; j<LEDS_ON_A_LAYER; j++) {
      currentPattern[i][j] = random(0, 2);
    }
  }
}

// For debuging purpose. Call this function if you need it.
// void printCurrentPattern() {
//   for (byte i=0; i<NUMBER_OF_LAYERS; i++) {
//     for (byte j=0; j<LEDS_ON_A_LAYER; j++) {
//       Serial.print(currentPattern[i][j]);
//     }
//     Serial.println("");
//   }
//   Serial.println("");
// }
