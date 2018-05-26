#include "FSM.h"
#include "Motor.h"
#include "Arduino.h"
#include "battery.h"
#include "LED.h"
#include "Logic.h"

STATE initialising() {
  if (is_battery_voltage__not_OK){
    comms_print("<Initialisation Failed: Low Battery>");
    return STOPPED;
  } else {
    comms_print("<Initialising...>");
    ledSETUP();
    motor.SETUP();
    motor.enable_motors();
    mpu.mpu_setup();
    Homing();
    delay(2000);
    comms_print("<Initialisation Finsihed, Entering Spiraling State...>");
    return SPIRALING;
  }
}

STATE spiraling() {
  if (is_battery_voltage__not_OK){
    comms_print("<Spiraling State Entering Failed: Low Battery>");
    return STOPPED;
  } else {
    comms_print("<Spiraling State Entered>");
    //Enter the code for spiraling here !!!!!!!!!!!!!!!!!!!!//
  }
}

STATE avoidance()  {
   if (is_battery_voltage__not_OK){
    comms_print("<Avoidance State Entering Failed: Low Battery>");
    return STOPPED;
  } else {
    comms_print("<Spiraling State Entered>");
    //Enter the code for avoidance here !!!!!!!!!!!!!!!!!!!!//
  }
}

STATE stopped() {
  comms_print("<Program Stopped>");
  static byte counter_lipo_voltage_ok;
  static unsigned long previous_millis;

  motor.disable_motors();
  slow_flash_LED_builtin();


  if (millis() - previous_millis > 500) { //print massage every 500ms
    previous_millis = millis();
    Serial1.println("I'm running LOW, you gonna damage my LiPo!!!!");
    Serial1.println("Hurry up and charge me!!!!");
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

void comms_print(char message)      //print message to both usb and bluetooth
{
  Serial.println(message);
  Serial1.println(message); 
}


