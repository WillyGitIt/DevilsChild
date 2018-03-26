#ifndef mpu_gyro
#define mpu_gyro

void mpu_setup();

/* creating an mpu gyroscope class */ 

class MPU {
    public:
        void mpu_setup();
        void get_angle(float * angle);
    private:
        void set_last_read_data(unsigned long time, float z_gyro);

};




#endif
