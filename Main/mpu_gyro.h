#ifndef mpu_gyro
#define mpu_gyro

#include <Arduino.h>

/* creating an mpu gyroscope class */ 

class MPU {
    public:
        MPU();
        void mpu_setup();
        float get_angle();
        float get_angular_velocity();
        float get_x_accel();
        float get_y_accel();
        float get_x_vel();
        float get_y_vel();
        void reset_angle_reading();
    private:
        void set_last_read_data_gyro(unsigned long time, float z_gyro);
        void set_last_read_data_vel_x(unsigned long time, float vel_x);
        void set_last_read_data_vel_y(unsigned long time, float vel_y);
        //variables to hold calibartion values
        float gyro_offset;
        float gyro_z_angle;
        float accel_offset_x;   
        float accel_offset_y;
        float velocity_y;
        float velocity_x;
        unsigned long last_read_time_gyro; //to help compute the time over which the integrationg is calculated
        unsigned long last_read_time_vel_x;
        unsigned long last_read_time_vel_y;
        float angle;

};


extern MPU mpu;

#endif
