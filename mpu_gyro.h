#ifndef mpu_gyro
#define mpu_gyro

#include <Arduino.h>

/* creating an mpu gyroscope class */ 

class MPU {
    public:
        MPU();
        void mpu_setup();
        void get_angle(float * angle);
    private:
        void set_last_read_data(unsigned long time, float z_gyro);
        //variables to hold gyroscope calc values
        float gyro_offset;
        float gyro_z_angle;
        float angle = 0.00;       // value to hold final calculated gyro angle
        unsigned long last_read_time; //to help compute the time over which the integrationg is calculated

};

#endif
