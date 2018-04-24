#include <Wire.h> //library allows you to communicate with I2C / TWI devices
#include <FaBo9Axis_MPU9250.h>
#include <Arduino.h>
#include "mpu_gyro.h"

#define num_readings 50

  FaBo9Axis fabo_9axis;
  float gyro_z = 0;
  float accel_x = 0;
  float accel_y = 0;
  float ax,ay,az;
  float gx,gy,gz;  
  float cgx,cgy,cgz;
  float cax,cay,caz;
 
//constructor
MPU::MPU(){
}

void MPU::set_last_read_data_gyro(unsigned long time, float z_gyro) {
  last_read_time_gyro = time;
  gyro_z_angle = z_gyro;
}

void MPU::set_last_read_data_vel_x(unsigned long time, float vel_x) {
  last_read_time_vel_x = time;
  velocity_x = vel_x;
}

void MPU::set_last_read_data_vel_y(unsigned long time, float vel_y) {
  last_read_time_vel_y = time;
  velocity_y = vel_y;
}

void MPU::mpu_setup() {
  //Serial.begin(9600);                   //Sets the data rate in bits per second (baud) for serial data transmission
  
  if (fabo_9axis.begin()) {
    // Serial.println("configured FaBo 9Axis I2C Brick");
  } else {
    Serial.println("mpu device error");
    while(1);
  }

  //calibration for the gyroscope and accelerometer    
  for (int i = 0; i < num_readings; i++) {  //read in the first 50 values from the MPu and average them 
  //  float cgx,cgy,cgz;
    fabo_9axis.readGyroXYZ(&cgx,&cgy,&cgz);
    gyro_z += cgz;
   // float cax,cay,caz;
    fabo_9axis.readAccelXYZ(&cax,&cay,&caz);
    accel_x += cax;
    accel_y += cay;
    delay(1); //delay so the MPUu has time to get the next value
  }
  gyro_z /= num_readings; //calc the average
  gyro_offset = gyro_z; //store in the global offset variable
  accel_x /= num_readings; 
  accel_offset_x = accel_x;
  accel_y /= num_readings; 
  accel_offset_y = accel_y;
 
}

float MPU::get_angle() {
  unsigned long t_now = millis(); //stores the time the readings were taken  
  //read in the values  
  fabo_9axis.readGyroXYZ(&gx,&gy,&gz);
  
  float gyro_corrected = gz - gyro_offset;
  float dt = (t_now - last_read_time_gyro)/1000.0; //calculates the time since the last reading, in seconds 
  gyro_z_angle = gyro_corrected*dt + gyro_z_angle;
  
  set_last_read_data_gyro(t_now, gyro_z_angle);

  angle = gyro_z_angle;
  return angle;

}

float MPU::get_angular_velocity() {
   fabo_9axis.readGyroXYZ(&gx,&gy,&gz); 
   return gz;
}

float MPU::get_x_accel() {
  fabo_9axis.readAccelXYZ(&ax,&ay,&az);
  return ax;
}

float MPU::get_y_accel() {
  fabo_9axis.readAccelXYZ(&ax,&ay,&az);
  return ay;
}

float MPU::get_x_vel() {
  unsigned long t_now_x_vel = millis(); //stores the time the readings were taken  

  //read in the values
  fabo_9axis.readAccelXYZ(&ax,&ay,&az);
  
  float accel_corrected_x = ax - accel_offset_x;
  float dt = (t_now_x_vel - last_read_time_vel_x)/1000.0; //calculates the time since the last reading, in seconds
  velocity_x = accel_corrected_x*dt + velocity_x;
  
  set_last_read_data_vel_x(t_now_x_vel, velocity_x);
  return velocity_x;

}
float MPU::get_y_vel() {
  unsigned long t_now_y_vel = millis(); //stores the time the readings were taken  

  //read in the values
  fabo_9axis.readAccelXYZ(&ax,&ay,&az);
  
  float accel_corrected_y = ay - accel_offset_y;
  float dt = (t_now_y_vel - last_read_time_vel_y)/1000.0; //calculates the time since the last reading, in seconds
  velocity_y = accel_corrected_y*dt + velocity_y;

  set_last_read_data_vel_y(t_now_y_vel, velocity_y);
  return velocity_y;
}

void MPU::reset_angle_reading() { //this function resets and recalibrates the angle
   //FaBo9Axis fabo_9axis;

  //calibration for the gyroscope and accelerometer
  float gyro_z = 0;
 // float gx,gy,gz;  
    
  for (int i = 0; i < num_readings; i++) {  //read in the first 50 values from the MPu and average them 
   // float cgx,cgy,cgz;
    fabo_9axis.readGyroXYZ(&cgx,&cgy,&cgz);
    gyro_z += cgz;
    delay(1); //delay so the MPUu has time to get the next value
  }
  gyro_z /= num_readings; //calc the average
  gyro_offset = gyro_z; //store in the global offset variable
  gyro_z_angle = 0.0;
  unsigned long t_now_reset = millis();
  set_last_read_data_gyro(t_now_reset, gyro_z_angle);


}















