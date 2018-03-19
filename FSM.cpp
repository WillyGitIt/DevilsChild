#include "FSM.h"
#include "Motor.h"
#include "Arduino.h"
#include "battery.h"
#include "LED.h"

STATE initialising() {
  //Do some initialising
  Serial1.println("INITIALISING....");
  delay(1000); //One second delay to see the serial string "INITIALISING...."
  Serial1.println("Enabling Motors...");
  
  return RUNNING;
}

STATE running() {
  motor.read_serial_command();
  fast_flash_double_LED_builtin();
  //range_and_speed_settings();
  if (is_battery_voltage__not_OK()) return STOPPED;
  return RUNNING;
}

STATE stopped() {
  static byte counter_lipo_voltage_ok;
  static unsigned long previous_millis;
  
  motor.disable_motors();
  slow_flash_LED_builtin();
  
  
  if (millis() - previous_millis > 500) { //print massage every 500ms
    previous_millis = millis();
    Serial1.println("Lipo voltage too LOW, any lower and the lipo with be damaged");
    Serial1.println("Please Re-charge Lipo");
  }
  //500ms timed if statement to check lipo and output speed settings
  if (!is_battery_voltage__not_OK()) {
    counter_lipo_voltage_ok++;
    if (counter_lipo_voltage_ok > 20) { //Making sure lipo voltage is stable 
      counter_lipo_voltage_ok = 0;
      return RUNNING;
    }
  } else counter_lipo_voltage_ok = 0;
  return STOPPED;
}


