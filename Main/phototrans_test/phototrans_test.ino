#include "phototrans.h"

Phototrans Phototrans;

void setup() {
  Phototrans.setup(15, 14, 13, 5, 4, 3, 0.2);
  Serial.begin(9600); // sets the serial port to 9600
}

void loop() {
  bool fireDetected = Phototrans.isFire();
  if (fireDetected) {
    Serial.println("FIRE");
  } else {
    Serial.println("no fire");
  }

  delay(500);  //delay the loop 500 ms 
  
}
