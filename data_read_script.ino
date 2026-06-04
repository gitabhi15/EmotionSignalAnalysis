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
  if (accel.update()) {
    Serial.print(accel.getX());
    Serial.print(",");
    Serial.print(accel.getY());
    Serial.print(",");
    Serial.print(accel.getZ());
    Serial.println("");
  } else {
    Serial.println("update failed");
    while (1) {
      delay(100);
    }
  }
  delay(300);

  heartValue = analogRead(heartPin);
  Serial.println(heartValue);
  delay(1000);

  gsrValue = analogRead(gsrPin);
  Serial.println(gsrValue);
  delay(1000);

  muscleValue = analogRead(musclePin);
  Serial.println(muscleValue);
  delay(1000);
}
