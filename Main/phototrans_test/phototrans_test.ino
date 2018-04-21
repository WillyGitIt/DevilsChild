#include "phototrans.h"

Phototrans Phototrans;

void setup() {
  Phototrans.setup(5, 14, 15, 4, 0.3);
  Serial.begin(9600); // sets the serial port to 9600
}

void loop() {
 
  if (Phototrans.isFire()) {
    Serial.println(" FIRE");
  } else {
    Serial.println(" no fire");
  }

  delay(500);  //delay the loop 500 ms 
  
}
