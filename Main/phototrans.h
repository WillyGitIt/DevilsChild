#ifndef phototrans
#define phototrans

#include <Arduino.h>

class Phototrans {
    private:
        float avgtf5;
        float avgtf3;
        float avgtb5;
        float avgtb3;
        int pinf5;
        int pinf3;
        int pinb5;
        int pinb3;
        float alph; 
    public:
        Phototrans(float alphaInput, int pinf5, int pinf3, int pinb5, int pinb3);
        void setup();
        bool isFire(); 


};

#endif
