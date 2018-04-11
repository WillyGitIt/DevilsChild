#include "Ultrasonic_Sensor.h"
#include "main.h"
#include "Arduino.h"
#include <hcsr04.h>
#include <Servo.h>




void setup(){
    unsigned int TRIG_PIN = 12;
    unsigned int ECHO_PIN = 13;
    unsigned int SPINNYTHING_PIN = 14;
    Servo spinnything; 
    spinnything.attach(SPINNYTHING_PIN); 
    HCSR04 UltrasonicSensor(TRIG_PIN, ECHO_PIN, 20, 4000);
}

void UltraSonicScan () {
  unsigned int degree = spinnything.read();
  
  if (degree <= 90) {
    
    spinnything.write(0);
    delay(200);
   
   for (unsigned int i = 0; i <= 180; i++){
      spinnything.write(i);
      delay(15);
      FrontScan[i] = UltrasonicSensor.distanceInMillimeters();
   } 
   
  }else{ 
    
    spinnything.write(180);
    delay(200);
    
    for (unsigned int i = 180; i >= 0; i--){
      spinnything.write(i);
      delay(15);
      FrontScan[i] = UltrasonicSensor.distanceInMillimeters();
    }
  }
}






/*
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;

void setup() 
{
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() 
{
  
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance (mm) 
distance = duration * 0.034/2;

// Convert this to mm 
newDistance = 10*distance;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(newDistance);

} */ 
