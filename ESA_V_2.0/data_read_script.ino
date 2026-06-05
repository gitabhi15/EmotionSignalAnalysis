#include <Wire.h>
#include <hd44780.h>
#include <ADXL345.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#define ROWS 4
#define COLS 4

hd44780_I2Cexp lcd;
ADXL345 accel(ADXL345_STD);

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

const int heartPin = 3;
const int gsrPin = 4;
const int musclePin = 5;

float heartValue;
float gsrValue;
float muscleValue;

String command;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(LCD_COLS, LCD_ROWS);
  pinMode(heartPin, INPUT);

  byte deviceID = accel.readDeviceID();
  if (deviceID != 0) {
    Serial.print("0x");
    Serial.print(deviceID, HEX);
    Serial.println("");
  } else {
    Serial.println("read device id: failed");
    while (1) {
      delay(100);
    }
  }

  if (!accel.writeRange(ADXL345_RANGE_16G)) {
    Serial.println("write range: failed");
    while (1) {
      delay(100);
    }
  }

  if (!accel.start()) {
    Serial.println("start: failed");
    while (1) {
      delay(100);
    }
  }
}

void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil("\n");
    command.trim();

    if (command == "SEND") {
      if (accel.update()) {
        Serial.print("X: ");
        Serial.print(accel.getX());
        Serial.print(", ");
        Serial.print("Y: ");
        Serial.print(accel.getY());
        Serial.print(", ");
        Serial.print("Z: ")
          Serial.print(accel.getZ());
        Serial.println("");
      } else {
        Serial.println("Update failed");
      }

      heartValue = analogRead(heartPin);
      Serial.print("Heart rate: ");
      Serial.print(heartValue);
      Serial.println("");

      gsrValue = analogRead(gsrPin);
      Serial.print("Skin conductance: ");
      Serial.print(gsrValue);
      Serial.println("");

      muscleValue = analogRead(musclePin);
      Serial.print("EMG value: ")
      Serial.print(muscleValue);
      Serial.println("");

    } else if (command == "END") {
      Serial.println("Session completed.")
    }
  }
}
