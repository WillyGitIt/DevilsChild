#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include "mpu_gyro.h"

MPU mpu;

void setup() {
    mpu.mpu_setup();
}

void loop() {
    float angle_reading;
    float angular_velocity;
    float x_accel;
    float y_accel;
    float x_vel;
    float y_vel;
    mpu.get_angle(&angle_reading);
    mpu.get_angular_velocity(&angular_velocity);
    mpu.get_x_accel(&x_accel);
    mpu.get_y_accel(&y_accel);
    mpu.get_x_vel(&x_vel);
    mpu.get_y_vel(&y_vel);

    Serial.print("Angle: ");
    Serial.print(angle_reading);
    Serial.print(" Anglular velocity: ");
    Serial.print(angular_velocity);
    Serial.print(" x accel: ");
    Serial.print(x_accel);
    Serial.print(" y accel: ");
    Serial.print(y_accel);
    Serial.print(" x vel: ");
    Serial.print(x_vel);
    Serial.print(" y vel: ");
    Serial.println(y_vel);

    delay(500);  //delay the loop 500 ms 
}

