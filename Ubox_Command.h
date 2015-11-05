// -----
// Ubox_Command.h - Library to control uBox by Serial Commands
// -----

#ifndef Ubox_Command_h
#define Ubox_Command_h

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

// Comandos = pt-BR
#define CMD_VOICE_ENABLE "*ativar"
#define CMD_VOICE_DISABLE "*desativar"
#define CMD_FORWARD "*para frente"
#define CMD_FORWARD2 "*pra frente"
#define CMD_BACKWARD "*para trás"
#define CMD_BACKWARD2 "*pra trás"
#define CMD_LEFT "*esquerda"
#define CMD_LEFT2 "*pra esquerda"
#define CMD_RIGHT "*direita"
#define CMD_RIGHT2 "*pra direita"
#define CMD_STOP "*parar"
#define CMD_STOP2 "*parado"

#include <SoftwareSerial.h>
#include "Ubox_Time.h"
#include "Ubox_Head.h"
#include "Ubox_Engines.h"

// class Ubox_Command;
typedef void (*commandEventHandler)(String&);

class Ubox_Command : public Ubox_Time {
public:
  /* Class constructor.
    Parameters:
    serial: pointer to bluethoot
    head: pointer to head control
    engines: pointer to engines control
    interval: interval to check sensors between process
  */
  Ubox_Command(SoftwareSerial *serial, Ubox_Head *head, Ubox_Engines *engines, uint8_t interval);

  void run();
  void eventDisplay(commandEventHandler handler);

private:
  void processCommand(String cmd);
  void processCommand(char cmd);

  SoftwareSerial *_serial;
  Ubox_Head *_head;
  Ubox_Engines *_engines;
  commandEventHandler _onDisplay; // Callback for display
  bool _voice_active = false;
};

#endif