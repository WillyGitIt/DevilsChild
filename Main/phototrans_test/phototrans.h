#ifndef phototrans
#define phototrans

#include <Arduino.h>

class Phototrans {
    public:
      Phototrans();
        void setup(int pinf5, int pinf3, int pinb5, int pinb3, float alphaInput);
        bool isFire(); 
    private:
        float avgtf5;
        float avgtf3;
        float avgtb5;
        float avgtb3;
        int pinf5;
        int pinf3;
        int pinb5;
        int pinb3;
        float alpha;
        

};

#endif
