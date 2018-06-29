enum {
  MOTOR1_PIN1 = 0,
  MOTOR1_PIN2 = 1,
  MOTOR2_PIN1 = 7,
  MOTOR2_PIN2 = 8,
  MOTOR1_REFS_PIN = 5,
  MOTOR2_REFS_PIN = 6,
};

void setup() {
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR1_REFS_PIN, OUTPUT);
  
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  pinMode(MOTOR2_REFS_PIN, OUTPUT);
}

void loop() {
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  analogWrite(MOTOR1_REFS_PIN, 192);
  
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
  analogWrite(MOTOR2_REFS_PIN, 192);
}
