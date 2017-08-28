const int LED1 = 13;
const int LED2 = 12;
const int LED3 = 11;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED2, HIGH);
  delay(200);
  digitalWrite(LED3, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  delay(300);
  digitalWrite(LED2, LOW);
  delay(300);
  digitalWrite(LED3, LOW);
  delay(300);
}
