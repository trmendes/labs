int ldrPin = A0;
int tempPin = A1;
int ldrValue = 0;
int tempValue = 0;

#define aref_voltage 5.0

void setup() {
  Serial.begin(9600);

}

void loop() {
  ldrValue = analogRead(ldrPin);
  tempValue = analogRead(tempPin);
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = tempValue * aref_voltage;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 10;
  Serial.print(ldrValue);
  Serial.print("\n");
  Serial.print(temperatureC);
  Serial.print("\n");
  delay(1000);
}
