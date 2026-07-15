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

int heartValue;
int gsrValue;
int muscleValue;

const unsigned long gsrInterval = 100000;
const unsigned long emgInterval = 5000;
const unsigned long adxlInterval = 20000;
const unsigned long heartInterval = 10000;

unsigned long lastGsrTime = 0;
unsigned long lastEmgTime = 0;
unsigned long lastAdxlTime = 0;
unsigned long lastHeartTime = 0;

bool isLogging = false;

void setup() {
  Serial.begin(115200);
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
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "SEND") {
      isLogging = true;
      Serial.println("Session started.");
    } else if (command == "END") {
      isLogging = false;
      Serial.println("Session ended.");
    }
  }
  if (isLogging) {
    unsigned long currentMicros = micros();
    if (currentMicros - lastAdxlTime >= adxlInterval) {
      if (accel.update()) {
        lastAdxlTime = currentMicros;
        Serial.print("X: ");
        Serial.print(accel.getX());
        Serial.print(", ");
        Serial.print("Y: ");
        Serial.print(accel.getY());
        Serial.print(", ");
        Serial.print("Z: ");
        Serial.print(accel.getZ());
        Serial.println("");
      } else {
        Serial.println("Update failed");
      }
    }

    if (currentMicros - lastHeartTime >= heartInterval) {
      lastHeartTime = currentMicros;
      heartValue = analogRead(heartPin);
      Serial.print("Heart rate: ");
      Serial.print(heartValue);
      Serial.println("");
    }

    if (currentMicros - lastGsrTime >= gsrInterval) {
      lastGsrTime = currentMicros;
      gsrValue = analogRead(gsrPin);
      Serial.print("Skin conductance: ");
      Serial.print(gsrValue);
      Serial.println("");
    }

    if (currentMicros - lastEmgTime >= emgInterval) {
      lastEmgTime = currentMicros;
      muscleValue = analogRead(musclePin);
      Serial.print("EMG value: ");
      Serial.print(muscleValue);
      Serial.println("");
    }
  }
}
