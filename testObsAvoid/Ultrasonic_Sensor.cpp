#include "Ultrasonic_Sensor.h"
#include "Arduino.h"
#include <hcsr04.h>
#include <Servo.h>
#include "Settings.h" 

Ultrasonic_Sensor::Ultrasonic_Sensor(int ServoPin, int TrigPin, int EchoPin, int MinRange, int MaxRange){ //HCSR04 UltrasonicSensor(TrigPin, EchoPin, MinRange, MaxRange);
    
    Servo_Pin = ServoPin;
    Trig_Pin = TrigPin;
    Echo_Pin = EchoPin;
    Min_Range = MinRange;
    Max_Range = MaxRange;
    
}

void Ultrasonic_Sensor::UltraSonicScan () {//scan front 180 degree and write data to 'FrontScan'
  Servo spinnything; 
  spinnything.attach(Servo_Pin); 
  HCSR04 UltrasonicSensor(Trig_Pin, Echo_Pin, Min_Range, Max_Range);
  unsigned int degree = spinnything.read();
  
  if (degree <= 90) {
    
    spinnything.write(0);
    delay(200);
   
   for (unsigned int i = 0; i <= 180; i++){
      spinnything.write(i);
      delay(15);
      FrontScan[i] = (UltrasonicSensor.distanceInMillimeters())*0.1; //return cm
   } 
   
  }else{ 
    
    spinnything.write(180);
    delay(200);
    
    for (unsigned int i = 180; i >= 0; i--){
      spinnything.write(i);
      delay(15);
      FrontScan[i] = (UltrasonicSensor.distanceInMillimeters())*0.1; //return cm
    }
  }
  spinnything.detach();
}

int Ultrasonic_Sensor::USmeasure(unsigned int degree) //measure the distance with US sensor in a certain direction "degree" return 
{
  Servo spinnything;
  HCSR04 UltrasonicSensor(Trig_Pin, Echo_Pin, Min_Range, Max_Range);
  spinnything.attach(Servo_Pin); 
  spinnything.write(degree);
  delay(200);
  spinnything.detach();
  return (UltrasonicSensor.distanceInMillimeters())*0.1;
}

float Ultrasonic_Sensor::getFrontScan()
{
  //return FrontScan;
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
