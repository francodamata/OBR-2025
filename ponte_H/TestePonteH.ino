
#define IN1 10
#define IN2 9
#define IN3 6
#define IN4 5

void setup() {
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);

}

void loop() {
    analogWrite(IN1,255/2);
    digitalWrite(IN2, LOW);
  delay(5000);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2, LOW);
    analogWrite(IN2,255/2);
    digitalWrite(IN1, LOW);
  delay(5000);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2, LOW);
    analogWrite(IN3,255/2);
    digitalWrite(IN4, LOW);
  delay(5000);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4, LOW);
    analogWrite(IN4,255/2);
    digitalWrite(IN3, LOW);
  delay(5000);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4, LOW);
}
