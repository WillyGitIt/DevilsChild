#ifndef phototrans
#define phototrans

#include <Arduino.h>

class Phototrans {
    public:
      Phototrans();
        void setup(int pinf5, int pinf3, int pinfs, int pinb5, int pinb3, int pinbs, float alpha);
        bool isFire(); 
    private:
        float avgtf5;
        float avgtf3;
        float avgtfs;
        float avgtb5;
        float avgtb3;
        float avgtbs;
        int pinf5;
        int pinf3;
        int pinfs;
        int pinb5;
        int pinb3;
        int pinbs;
        float alpha;
        

};

#endif
