#include "Arduino.h"
#include "Motor.h"

boolean is_battery_voltage__not_OK()
{
  static unsigned long previous_millis;
  
  if (millis() - previous_millis > 500) { //500ms timed if statement to check lipo and output speed settings
    previous_millis = millis();
    Serial.print("Lipo level:");
    int Lipo_level_cal;
    //the voltage of a LiPo cell depends on its chemistry and varies from about 2.7-3.1 V (discharged) = 620(3.1V Min)
    //to about 4.20-4.25 V (fully charged) = 820(4.1V Max)
    Lipo_level_cal = (analogRead(A0) - 620);
    Lipo_level_cal = Lipo_level_cal * 100;
    Lipo_level_cal = Lipo_level_cal / 200;

    Serial.print(Lipo_level_cal);
    Serial.println("%");
    if (Lipo_level_cal < 0) return false;
  }
  return false;
}

