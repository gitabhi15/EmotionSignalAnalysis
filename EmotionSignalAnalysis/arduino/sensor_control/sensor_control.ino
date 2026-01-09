// pins
int gsrPin = A0;
int tempPin = A1;
int hrPin = A2;

unsigned long lastTime = 0;
int interval = 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (millis() - lastTime >= interval) {
    lastTime = millis();

    int gsrVal = analogRead(gsrPin);
    int tempRaw = analogRead(tempPin);
    int hrVal = analogRead(hrPin);

    float voltage = tempRaw * (5.0 / 1023.0);
    float temperature = (voltage - 0.5) * 100.0;

    Serial.print(millis() / 1000);
    Serial.print(",");
    Serial.print(gsrVal);
    Serial.print(",");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(hrVal);
  }
}
