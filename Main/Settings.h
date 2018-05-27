#ifndef Settings_h
#define Settings_h

//------- Motor Settings ----------//
#define Motor_LF_Pin 46 //control motor pins
#define Motor_LR_Pin 47
#define Motor_RR_Pin 50
#define Motor_RF_Pin 51

//------- Fire Fighting Settings ----------//
#define fanPIN 00           //pin number that attached to the fan control
#define fanDELAY 2000       //amount of time that fan keeps running after fire is off in ms

//------- UltraSonic Settings ----------//
#define TRIG_PIN 11        //pin number for TRIG pin on Ultrasonic sensor
#define ECHO_PIN 10         //pin number for ECHO pin on Ultrasonic sensor
#define SERVO_PIN 8  //pin number for data pin on small servo motor

#define US_MinRange 20      //minimum sensing range for ultrasonic in ms which is 2cm
#define US_MaxRange 4000    //maximum sensing range for ultrasonic in ms which is 400cm

//------- IR sensor Settings ----------//
#define IR_FL_PIN 8
#define IR_FR_PIN 9
#define IR_SF_PIN 10
#define IR_SB_PIN 11

#define IR_Type_FL Short_2D120XF1Y
#define IR_Type_FR Short_2D120XF1Z
#define IR_Type_SF Medium_2Y0A21F06
#define IR_Type_SB Medium_2Y0A21F44

//------- Navigation Settings ----------//
#define Straight_Wall_Tolerance 3

#endif
