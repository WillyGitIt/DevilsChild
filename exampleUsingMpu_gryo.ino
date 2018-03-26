#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include "mpu_gyro.h"

MPU mpu;

void setup() {
    mpu.mpu_setup();
}

void loop() {
    float angle_reading;
    mpu.get_angle(&angle_reading);
    Serial.print("Angle: ");
    Serial.println(angle_reading);

    delay(50);  //delay the loop 500 ms 
}

