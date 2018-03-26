#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>
#include <mpu_gyro.h>

MPU mpu;

void initialise() {
    mpu.setup();
}

void loop() {
    float angle_reading;
    mpu.get_angle(&angle_reading);
    Serial.print("Angle: ");
    Serial.println(angle_reading)

    delay(500);  //delay the loop 500 ms 
}

