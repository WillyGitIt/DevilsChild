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
#define TRIG_PIN 11         //pin number for TRIG pin on Ultrasonic sensor
#define ECHO_PIN 10         //pin number for ECHO pin on Ultrasonic sensor
#define SPINNYTHING_PIN 8   //pin number for data pin on small servo motor

#define US_MinRange 20      //minimum sensing range for ultrasonic in ms
#define US_MaxRange 4000    //maximum sensing range for ultrasonic in ms

//------- IR sensor Settings ----------//
#define IR_forward_left_PIN 8
#define IR_forward_right_PIN 9
#define IR_side_front_PIN 10
#define IR_side_back_PIN 11

#define IR_Type_FL Short_2D120XF1Y
#define IR_Type_FR Short_2D120XF1Z
#define IR_Type_SF Medium_2Y0A21F06
#define IR_Type_SB Medium_2Y0A21F44

//------- Spiral Settings ----------//
#define Wall_Distance 5   //how close the robot should be to the wall for first round (cm)


//------- Obtacle detection Settings ----------//
#define obstacle_stopDistance     10      //how close the robot should stop infront of an abstacle (cm)
#define obstacle_dectectDistance  15      //how close the obstacle needs to be infront of a sensor to count as a threat (cm)
#endif
