#ifndef Settings_h
#define Settings_h

//------- Motor Settings ----------//
#define Motor_LF_Pin 46; //control motor pins
#define Motor_LR_Pin 47;
#define Motor_RR_Pin 48;
#define Motor_RF_Pin 49;

//------- Fire Fighting Settings ----------//
#define fanPIN 00           //pin number that attached to the fan control
#define fanDELAY 2000       //amount of time that fan keeps running after fire is off in ms

//------- UltraSonic Settings ----------//
#define TRIG_PIN 12         //pin number for TRIG pin on Ultrasonic sensor
#define ECHO_PIN 13         //pin number for ECHO pin on Ultrasonic sensor
#define SPINNYTHING_PIN 14  //pin number for data pin on small servo motor

#define US_MinRange 20      //minimum sensing range for ultrasonic in ms
#define US_MaxRange 4000    //maximum sensing range for ultrasonic in ms

//------- IR sensor Settings ----------//
#define IR_forward_left_PIN 00
#define IR_forward_right_PIN 00
#define IR_side_front_PIN 00
#define IR_side_back_PIN 00

#define IR_Type_FL 00
#define IR_Type_FR 00
#define IR_Type_SF 00
#define IR_Type_SB 00

//------- Navigation Settings ----------//
#define Straight_Wall_Tolerance 3

#endif
