#include <Wire.h>

enum {
  MOTOR1_REFS_PIN = 5,
  MOTOR1_PIN1 = 10,
  MOTOR1_PIN2 = 11,
  
  MOTOR2_REFS_PIN = 6,
  MOTOR2_PIN1 = 12,
  MOTOR2_PIN2 = 13,

  I2C_ADDRESS = 8,
};

enum {
  MOTOR_SPEED_ACCEL = 1,
};

void clearWire();
void accelSpeed(int *speed, int request);

int motor1Speed = 0;
int motor2Speed = 0;

int motor1RequestSpeed = 0;
int motor2RequestSpeed = 0;

void setup() {
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR1_REFS_PIN, OUTPUT);
  
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  pinMode(MOTOR2_REFS_PIN, OUTPUT);

  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  accelSpeed(&motor1Speed, motor1RequestSpeed);
  accelSpeed(&motor2Speed, motor2RequestSpeed);
  
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  analogWrite(MOTOR1_REFS_PIN, motor1Speed);
  
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
  analogWrite(MOTOR2_REFS_PIN, motor2Speed);

  delayMicroseconds(100);
}

void receiveEvent(int howMany) {
  const char reg = Wire.read();
  if(reg != 'M') {
    clearWire();
    return;
  }

  if(Wire.available()) {
    motor1RequestSpeed = Wire.read();
  }

  if(Wire.available()) {
    motor2RequestSpeed = Wire.read();
  }

  clearWire();
}

void requestEvent() {
  Wire.write(motor1Speed);
  Wire.write(motor2Speed);
}

void clearWire() {
  for(; Wire.available(); Wire.read())
      ; // do nothing
}

void accelSpeed(int *speed, int request) {
  const int s = *speed;
  if(s < request) {
    *speed = min(request, s + MOTOR_SPEED_ACCEL);
  } else if(s > request) {
    *speed = max(request, s - MOTOR_SPEED_ACCEL);
  }
}

