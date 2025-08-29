#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int LDR_COUNT = 5;
const int ldrPins[LDR_COUNT] = {A0, A1, A2, A3, A4};
const int LDR_WEIGHT[LDR_COUNT] = {100, 50, 0, -50, -100};
const int BLACK_THRESHOLD = 500;


float Kp = 11.5;
float Kd = 1.5;
int baseSpeed = 220; //max 255

#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9

const int trigPin = 41;
const int echoPin = 39;
const float SOUND_SPEED = 0.034; // cm/us

#define TCA_ADDR 0x70
#define LED_SENSOR_0 22
#define LED_SENSOR_1 24

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

float lastPosition = 0;
float lastError = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(LED_SENSOR_0, OUTPUT);
  pinMode(LED_SENSOR_1, OUTPUT);
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  for (uint8_t ch = 0; ch < 2; ch++) {
    tcaSelect(ch);
    delay(10);
    if (tcs.begin()) { //teste
      Serial.print("Sensor TCS34725 canal ");
      Serial.print(ch);
      Serial.println(" detectado.");
    } else {
      Serial.print("Sensor TCS34725 canal ");
      Serial.print(ch);
      Serial.println(" NAO detectado!");
    }
  }
  Serial.println("Inicializacao completa.");
//Ponte H
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

//Ultra som
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //ostaculo
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * SOUND_SPEED) / 2;
  if (distance > 0 && distance < 10.0) { // menos de 10cm
    Serial.println("Obstaculo detectado! Efetuando desvio...");
    stopMotors();
    delay(100);
    moveBackward(150);
    delay(600);
    stopMotors();
    turnLeft(700);
  }

  //verde
  bool greenRight = false, greenLeft = false;
  uint16_t r, g, b, c;
  //direitaa
  tcaSelect(0);
  digitalWrite(LED_SENSOR_0, HIGH);
  delay(10);
  tcs.getRawData(&r, &g, &b, &c);
  digitalWrite(LED_SENSOR_0, LOW);
  if (g > r*1.5 && g > b*1.5) greenRight = true;

  //esquerda
  tcaSelect(1);
  digitalWrite(LED_SENSOR_1, HIGH);
  delay(10);
  tcs.getRawData(&r, &g, &b, &c);
  digitalWrite(LED_SENSOR_1, LOW);
  if (g > r*1.5 && g > b*1.5) greenLeft = true;

  if (greenRight && greenLeft) {
    Serial.println("Curva verde (ambos sensores)!");
    stopMotors(); delay(50);
    moveBackward(150);
    delay(400);
    stopMotors(); delay(100);
    turnLeft(1400);  //curva de +/- 180
  }
  else if (greenLeft) {
    Serial.println("Curva verde (lado esquerdo)!");
    stopMotors(); delay(50);
    moveBackward(150);
    delay(400);
    stopMotors();
    moveForward(200);
    delay(1000);
    stopMotors();
    turnLeft(700);  //curva de +/- 90 pra esquerda
  }
  else if (greenRight) {
    Serial.println("Curva verde (lado direito)!");
    stopMotors(); delay(50);
    moveBackward(150);
    delay(400);
    stopMotors();
    moveForward(200);
    delay(1000);
    stopMotors();
    turnRight(700); //curva de +/- 90 pra direita
  }

  //PID
  float soma = 0;
  int countBlack = 0;
  for (int i = 0; i < LDR_COUNT; i++) {
    int val = analogRead(ldrPins[i]);
    if (val < BLACK_THRESHOLD) {
      soma += LDR_WEIGHT[i];
      countBlack++;
    }
  }
  float position = lastPosition;
  if (countBlack > 0) {
    position = soma / countBlack;  //media ponderada
  }
  lastPosition = position;
  float error = 0 - position;     // centro 0
  float deltaError = error - lastError;
  float VelocAdj = Kp * error + Kd * deltaError;
  lastError = error;

  int speedLeft  = baseSpeed + (int)VelocAdj;
  int speedRight = baseSpeed - (int)VelocAdj;
  speedLeft  = constrain(speedLeft,  0, 255);
  speedRight = constrain(speedRight, 0, 255);
  //reverter sentido
  setMotorSpeeds(speedLeft, speedRight);

  delay(10); //pausa para estabilidade
}

void tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

void setMotorSpeeds(int speedL, int speedR) {
  if (speedL >= 0) {
    analogWrite(IN1, speedL);
    digitalWrite(IN2, LOW);
  } else {
    analogWrite(IN2, -speedL);
    digitalWrite(IN1, LOW);
  }
  if (speedR >= 0) {
    analogWrite(IN3, speedR);
    digitalWrite(IN4, LOW);
  } else {
    analogWrite(IN4, -speedR);
    digitalWrite(IN3, LOW);
  }
}

void moveForward(int speed) {
  analogWrite(IN1, speed);
  digitalWrite(IN2, LOW);
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);
}

void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, speed);
  digitalWrite(IN3, LOW);
  analogWrite(IN4, speed);
}

void stopMotors() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void turnLeft(int durationMs) {
  analogWrite(IN1, 0);
  analogWrite(IN2, 150);
  analogWrite(IN3, 150);
  analogWrite(IN4, 0);
  delay(durationMs);
  stopMotors();
}

void turnRight(int durationMs) {
  analogWrite(IN1, 150);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 150);
  delay(durationMs);
  stopMotors();
}
