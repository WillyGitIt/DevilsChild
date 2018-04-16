#ifndef Settings_h
#define Settings_h

//------- Fire Fighting Settings ----------//
#define fanPIN 00           //pin number that attached to the fan control
#define fanDELAY 2000       //amount of time that fan keeps running after fire is off in ms

//------- UltrsSonic Settings ----------//
#define TRIG_PIN 12         //pin number for TRIG pin on Ultrasonic sensor
#define ECHO_PIN 13         //pin number for ECHO pin on Ultrasonic sensor
#define SPINNYTHING_PIN 14  //pin number for data pin on small servo motor

#define US_MinRange 20      //minimum sensing range for ultrasonic in ms
#define US_MaxRange 4000    //maximum sensing range for ultrasonic in ms

//------- IR sensor Settings ----------//
#define IR_forward_left_PIN 00
#define IR_forward_right_PIN 00
#define IR_left_PIN 00
#define IR_right_PIN 00

//------- Navigation Settings ----------//
#define Straight_Wall_Tolerance 3

#endif