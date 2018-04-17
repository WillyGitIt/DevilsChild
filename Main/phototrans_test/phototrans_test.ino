#include "phototrans.h"

Phototrans Phototrans;

void setup() {
  Phototrans.setup(15, 14, 5, 4, 0.2);
  Serial.begin(9600); // sets the serial port to 9600
}

void loop() {
 
  if (Phototrans.isFire()) {
    Serial.println("FIRE");
  } else {
    Serial.println("no fire");
  }

  delay(500);  //delay the loop 500 ms 
  
}
