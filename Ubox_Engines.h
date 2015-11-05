// -----
// Ubox_Engines.h - Library to control uBox engines.
// -----

#ifndef Ubox_Engines_h
#define Ubox_Engines_h

#if defined (ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif

#if defined (__AVR__)
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif

#include "Ubox_Time.h"

#define MIN_SPEED 115 // Min speed to move uBox
#define MAX_SPEED 255 // Max speed from uBox
#define MOTOR_DELAY 30 // Time to wait action motor
#define DEBUG_MOTOR 3000 // Time to debug motor

typedef enum ActionEngine { STOP, GO_FORWARD, GO_BACKWARD, GO_RIGHT, GO_LEFT };

class Ubox_Engines : public Ubox_Time {
public:
  /* Class constructor.
    Receive two pointers to array referenced pins.
    interval: interval to check sensors between process
  */
  Ubox_Engines(uint8_t *motor1, uint8_t *motor2, uint8_t interval); 

  void setSpeed(uint8_t speed); // Set the speed
  void run(); // Process the action of engines
  void stop(); // Set STOP action
  void forward(); // Set FORWARD action
  void backward(); // Set BACKWARD action
  void right(); // Set RIGHT action
  void left(); // Set LEFT action
  ActionEngine action(); // Return the action value
private:
  uint8_t *_motor1; // Pointer to motor1 pin definitions
  uint8_t *_motor2; // Pointer to motor2 pin definitions
  uint8_t _speed = MIN_SPEED; // Current speed 
  ActionEngine _action = STOP; // Current action
  ActionEngine _last_action = STOP; // Last action control

  void setAction(ActionEngine action); // Set current action
  void motorStop(uint8_t *motor); // Put motor to forward action
  void motorForward(uint8_t *motor); // Put motor to forward action
  void motorBackward(uint8_t *motor); // Put motor to backward action
};

#endif