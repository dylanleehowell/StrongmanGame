/** This sketch reads a force sensor and lights up LEDs sequentially like those "Test Your Strength"
    hammer games at the fair/carnival.
    Author:   Dylan Howell
    For:      Arkansas State University, College of Engineering
    License:  MIT
*/

// An array of pins for each LED driver. index 0 is the bottom and index 17 is the top. (Pin 0 is bottom, Pin A5 is top, etc.
const int leds[] = {0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A1, A2, A3, A4, A5};
const int forceResistor = A0; // Pin reading the voltage from the FSR
const int buzzer = 3;         // Piezo buzzer pin

const int thresh = 19;        // Raise this to decrease sensitivity. Don't make it below 18, since we have 18 driver circuits.

void setup() {
  //initialize the pins
  for (auto i : leds) {
    pinMode(i, OUTPUT);
  }//end for
  pinMode(forceResistor, INPUT);
  pinMode(buzzer, OUTPUT);

  // blink them thrice
  for (int i = 0; i < 2; i++) {
    for (auto i : leds) {
      digitalWrite(i, HIGH);
    }//end for
    delay(500);
    for (auto i : leds) {
      digitalWrite(i, LOW);
    }//end for
    delay(500);
  }

}// end setup

void loop() {
  // Turn all the lEDs on to prep for the animation
  for (auto i : leds) {
    digitalWrite(i, HIGH);
  }//end for
  
  bool looping = true;                      // Set this to false when someone hits the hammer
  int mappedForce = 0;                      // the pecentage of the force sensor mapped to a value between 0 and thresh
  int counter = 0;                          // keeps track of the current index of leds[]
  unsigned long wait_time;                  // wait until this time during wait operations
  while (looping) {                         // loop until someone hits the hammer
    while (looping && counter < 18) {       // run through all 18 LED driver positions
      digitalWrite(leds[counter], LOW);     // turn off current LED
      if (counter == 0) {                   //  if it's the bottom LED, turn on the top LED.
        digitalWrite(leds[17], HIGH);
      }
      else {                                // If it's any other LED, turn on the one below it.
        digitalWrite(leds[counter - 1], HIGH);
      }
      wait_time = millis() + 50;            // sets the delay to 50 milliseconds from now
      mappedForce = map(analogRead(forceResistor), 0, 1023, 0, thresh); // read the pressure sensor
      while (millis() < wait_time && mappedForce < 2) {                 // We have a bias of about 1. So make sure the hammer was actually hit.
        mappedForce = map(analogRead(forceResistor), 0, 1023, 0, thresh); // Read it constantly while waiting for the 50 ms to elapse
      }
      if (mappedForce >= 2) {  // if someone hit the hammer, quit running the animation
        looping = false;
      }
      counter++;  // increment the count
    }

    // See above code for functionality. Eveything is the same except the lights are being cycled descendingly instead of ascendingly.
    counter = 17;
    while (looping && counter >= 0) {
      digitalWrite(leds[counter], LOW);
      if (counter == 17) {
        digitalWrite(leds[0], HIGH);
      }
      else {
        digitalWrite(leds[counter + 1], HIGH);
      }
      wait_time = millis() + 50;
      mappedForce = map(analogRead(forceResistor), 0, 1023, 0, thresh);
      while (millis() < wait_time && mappedForce < 2) {
        mappedForce = map(analogRead(forceResistor), 0, 1023, 0, thresh);
      }
      if (mappedForce >= 2) {
        looping = false;
      }
      counter--;
    }
  }

  // Get the highest reading in 90 seconds
  for (int i = 0; i < 3; i++) {
    int temp = map(analogRead(forceResistor), 0, 1023, 0, thresh);
    if (temp > mappedForce) {
      mappedForce = temp;
    }// end if
    delay(30);
  }// end for
  for (auto i : leds) {
    digitalWrite(i, LOW);
  }//end for

  // Turn lights on based on how hard the pressure sensor was smacked.
  setLights(mappedForce);

}// end loop

void setLights(int maxVal) {
  // the threshold allows for numbers higher than 18, but we only have 18 drivers circuits.
  if (maxVal > 18) {
    maxVal = 18;
  }// end if
  if (maxVal > 0) {                     // If the sensor was hit...
    // Turn on the lights ascendingly
    for (int i = 0; i < maxVal; i++) {
      digitalWrite(leds[i], HIGH);
      delay(100);
    }// end for

    if (maxVal == 18) {                 // If the max force was detected
      delay(500);
      analogWrite(buzzer, 0);
      // blink lights five times
      for (int k = 0; k < 5; k++) {
        for (int j = 0; j < maxVal; j++) {
          digitalWrite(leds[j], LOW);
          analogWrite(buzzer, 0);
        }// end for
        delay(300);
        for (int j = 0; j < maxVal; j++) {
          digitalWrite(leds[j], HIGH);
          analogWrite(buzzer, 50);
        }// end for
        delay(300);
      }
      analogWrite(buzzer, 0);
    }

    // Turn off the lights descendingly
    for (int i = maxVal; i > 0; i--) {
      digitalWrite(leds[i - 1], LOW);
      delay(100);
    }// end for
  }// end if
}// end setLights

