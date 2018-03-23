#include <Arduino.h>
#include <Wire.h> //ibrary allows you to communicate with I2C / TWI devices, may not be needed in here?
#include <FaBo9Axis_MPU9250.h>

#define delayAmount 500


FaBo9Axis fabo_9axis;

//variables to hold gyroscope calc values
float gyro_offset;
float gyro_z_angle;
float angle = 0.00;       // value to hold final calculated gyro angle
unsigned long last_read_time; //to help compute the time over which the integrationg is calculated

void set_last_read_data(unsigned long time, float z_gyro) {
  last_read_time = time;
  gyro_z_angle = z_gyro;
}


void setup() {
  Serial.begin(9600);                   //Sets the data rate in bits per second (baud) for serial data transmission
  Serial.println("RESET");
  Serial.println();

  Serial.println("configuring device.");

  if (fabo_9axis.begin()) {
    Serial.println("configured FaBo 9Axis I2C Brick");
  } else {
    Serial.println("device error");
    while(1);
  }

  //calibration
  int num_readings = 50;
  float gyro_z = 0;
    
  for (int i = 0; i < num_readings; i++) {  //read in the first 50 values from the MPu and average them 
    float cgx,cgy,cgz;
    fabo_9axis.readGyroXYZ(&cgx,&cgy,&cgz);
    gyro_z += cgz;
    Serial.print(cgz);
    Serial.print(",");
    delay(5); //delay so the MPUu has time to get the next value
  }
  gyro_z /= num_readings; //calc the average
  gyro_offset = gyro_z; //store in the global offset variable
  Serial.print("Offset is ");
  Serial.println(gyro_offset);
}

void loop() {
  unsigned long t_now = millis(); //stores the time the readings were taken  
  
  //declaring variables for all the data
  float ax,ay,az;
  float gx,gy,gz;  
  //read in the values  
  fabo_9axis.readAccelXYZ(&ax,&ay,&az);
  fabo_9axis.readGyroXYZ(&gx,&gy,&gz);

  float gyro_corrected = gz - gyro_offset;
  float dt = (t_now - last_read_time)/1000.0; //calculates the time since the last reading, in seconds 
  gyro_z_angle = gyro_corrected*dt + gyro_z_angle;

  Serial.print(dt);
  Serial.print(",");
  Serial.println(gyro_z_angle);

  set_last_read_data(t_now, gyro_z_angle);

  delay(delayAmount);  //delay the loop 500 ms to see it on serial monitor
}
