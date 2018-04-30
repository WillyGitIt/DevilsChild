#include "phototrans.h"

Phototrans Phototrans;

void setup() {
  Phototrans.setup(14, 5, 15, 4, 0.2);
  Serial.begin(9600); // sets the serial port to 9600
  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH); 
}

void loop() {
 
  if (Phototrans.isFire()) {
    Serial.println(", 1");
    digitalWrite(34, LOW);   
  } else {
    Serial.println(", 0");
    digitalWrite(34, HIGH);  
  }

  delay(100);  //delay the loop 500 ms 
  
}
