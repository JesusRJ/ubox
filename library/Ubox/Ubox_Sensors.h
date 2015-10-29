// -----
// Ubox_Sensors.h - Library to control the sensors from uBox.
// -----

#ifndef Ubox_Sensors_h
#define Ubox_Sensors_h

#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <SoftwareSerial.h>
#include <UboxPing.h>

class Ubox_Sensors {
public:
  /* Class constructor.
    Parameters:
    ultrasonic: pointer to array referenced pins from sonar
    pin_ldr: LDR pin
  */
  Ubox_Sensors(UboxPing *ultrasonic, uint8_t pin_ldr);
  void process(); // Process read sensors
  void ultrasonicOn(); // Turn On read of ultrasonic sensor
  void ultrasonicOff(); // Turn Off read of ultrasonic sensor
  void ldrOn(); // Turn On read of ldr sensor
  void ldrOff(); // Turn Off read of ldr sensor
private:
  UboxPing *_ultrasonic;
  uint8_t _pin_ldr;

  bool _ultrasonic_on = true;
  bool _ldr_on = false;
};

#endif