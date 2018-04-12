#include <Arduino.h>
#include "phototrans.h"

Phototrans::Phototrans(){
}

void Phototrans::setup(int pinf5, int pinf3, int pinfs, int pinb5, int pinb3, int pinbs, float alpha) {
    avgtf5 = analogRead(pinf5); // read analog input pin 15 with the 5mm
    avgtf3 = analogRead(pinf3); // read analog input pin 14 with the 3mm
    avgtfs = analogRead(pinfs); // read analog input pin 13 with the smol 

    avgtb5 = analogRead(pinb5); // read analog input pin 5 with the 5mm
    avgtb3 = analogRead(pinb3); // read analog input pin 4 with the 3mm
    avgtbs = analogRead(pinbs); // read analog input pin 3 with the smol 

    alpha = alpha;
}

bool Phototrans::isFire() {
    bool isFire;

    float tf5 = analogRead(pinf5); // read analog input pin 15 with the 5mm
    float tf3 = analogRead(pinf3); // read analog input pin 14 with the 3mm
    float tfs = analogRead(pinfs); // read analog input pin 13 with the smol 

    //readings from the phototransistors at back of robot
    float tb5 = analogRead(pinb5); // read analog input pin 5 with the 5mm
    float tb3 = analogRead(pinb3); // read analog input pin 4 with the 3mm
    float tbs = analogRead(pinbs); // read analog input pin 3 with the smol 

    //calculate the avergae
    avgtf5 += (tf5 - avgtf5) * alpha;
    avgtf3 += (tf3 - avgtf3) * alpha;
    avgtfs += (tfs - avgtfs) * alpha;
    avgtb5 += (tb5 - avgtb5) * alpha;
    avgtb3 += (tb3 - avgtb3) * alpha;
    avgtbs += (tbs - avgtbs) * alpha;

    //compare the fornt transistors to the back transistors and if there enough of a difference between all three, indicate
    //there is a fire (% diff =  100 x (B-A)/((A+b)/2))
    float percent_diff_t5 = 100.0*(avgtf5 - avgtb5)/((avgtf5 + avgtb5)/2);
    float percent_diff_t3 = 100.0*(avgtf3 - avgtb3)/((avgtf3 + avgtb3)/2);
    float percent_diff_ts = 100.0*(avgtfs - avgtbs)/((avgtfs + avgtbs)/2);

    if (abs(percent_diff_t5) >60 && abs(percent_diff_t5) >60 && abs(percent_diff_t5) >60) 
    {
        isFire = true;
    } else 
    {
        isFire = false;
    }
return isFire;  

}


