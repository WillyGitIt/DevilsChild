#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include "mpu_gyro.h"

MPU mpu;

void setup() {
    mpu.mpu_setup();
    Serial.begin(9600); 
}

void loop() {
    float angle_reading;
    float angular_velocity;

    angle_reading = mpu.get_angle();
    angular_velocity = mpu.get_angular_velocity();

    //Serial.print("Angle: ");
    Serial.print(angle_reading);
    Serial.print(", ");
    //Serial.print(" Anglular velocity: ");
    Serial.println(angular_velocity);


    delay(50);  //delay the loop 500 ms 
}

