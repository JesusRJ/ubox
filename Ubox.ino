#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>
#include <ArduinoJson.h>
#include "Ubox_Base.h"
#include "Ubox_Command.h"
#include "Ubox_Sensors.h"
#include "Ubox_Engines.h"
#include "Ubox_Head.h"

// Motors pins
#define pin_m11 4
#define pin_m12 5
#define pin_m21 6
#define pin_m22 7
#define pin_m1_enable 9
#define pin_m2_enable 10
// Bluetooth pins
#define pin_ble_rx 11
#define pin_ble_tx 12
// Ultrasonic pins
#define pin_trigger 2
#define pin_echo 3
#define pin_ldr A0 // Analog pin
// Servos pins
#define pin_servo_head 8 // Head Control Servo Horizontal

// Engines control pins
uint8_t motor1[3] = { pin_m11, pin_m12, pin_m1_enable };
uint8_t motor2[3] = { pin_m21, pin_m22, pin_m2_enable };

// LCD Display initialize on address 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27);

// Bluetooth initialize
SoftwareSerial bluetooth(pin_ble_rx, pin_ble_tx);

// Ultrasonic sensor initialize
NewPing ultrasonic(pin_trigger, pin_echo, MAX_SENSOR_DISTANCE);

// Initialize order:
//   head controller
//   engines controller
//   commands interpreter (by voice/bluetooth and USB serial)
//   sensor controller
Ubox_Head head(pin_servo_head, INTERVAL_HEAD);
Ubox_Engines engines(motor1, motor2, INTERVAL_ENGINES);
Ubox_Sensors sensors(&ultrasonic, pin_ldr, INTERVAL_SENSORS);
Ubox_Command command(&bluetooth, &head, &engines, &sensors, INTERVAL_COMMAND);

void setup() {
  // LCD Display configuration
  lcd.noBacklight();
  lcd.begin (16, 2);

  lcd.home();
  lcd.print("Unisys");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  // System setup
  /* Serial for PC communication Initialization */
  Serial.begin(9600);
  while (!Serial) {
    // wait serial port initialization
  }

  /* uBox objects initialization **********************/
  engines.setSpeed(MIN_SPEED);

  // Associate callbacks events to classes
  command.eventDisplay(onDisplayLine1);
  engines.eventDisplay(onDisplayLine1);
  sensors.eventDisplay(onDisplayLine2);

  sensors.setLDRState(OFF);
  sensors.setUltrasonicState(OFF);

  /****************************************************/
  // end - System setup

  delay(500);
  lcd.clear();
  lcd.print("      uBox      ");
}

void loop() {
  command.process();
  sensors.process();
  head.process();
  engines.process();
}

// Print information on first line of LCD Display
void onDisplayLine1(const char *value) {
  lcd.setCursor(0, 0);
  lcd.print(value);
  Serial.print("Display Line1: ");
  Serial.println(value);
}

// Print information on second line of LCD Display
void onDisplayLine2(const char *value) {
  lcd.setCursor(0, 1);
  lcd.print(value);
  Serial.print("Display Line2: ");
  Serial.println(value);
}
