#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define TCA9548A_ADDR 0x70
#define LED_SENSOR_0 22
#define LED_SENSOR_1 24

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS, 
  TCS34725_GAIN_4X
);

void tcaSelect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

String identificarCor(uint16_t r, uint16_t g, uint16_t b, uint16_t c) {
  if (c < 100) return "Preto";  // luminosidade muito baixa
  if (r > 300 && g > 300 && b > 300 && abs(r - g) < 80 && abs(r - b) < 80) return "Branco";
  if (r > g * 1.5 && r > b * 1.5) return "Vermelho";
  if (g > r * 1.5 && g > b * 1.5) return "Verde";
  if (b > r * 1.5 && b > g * 1.5) return "Azul";
  return "Cor indefinida";
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(LED_SENSOR_0, OUTPUT);
  pinMode(LED_SENSOR_1, OUTPUT);
  digitalWrite(LED_SENSOR_0, LOW);
  digitalWrite(LED_SENSOR_1, LOW);
  for (uint8_t i = 0; i < 2; i++) {
    tcaSelect(i);
    delay(10);
    if (tcs.begin()) {
      Serial.print("Sensor no canal ");
      Serial.print(i);
      Serial.println(" detectado.");
    } else {
      Serial.print("Sensor no canal ");
      Serial.print(i);
      Serial.println(" NÃO detectado.");
    }
  }
  Serial.println("Teste iniciado.\n");
}

void loop() {
  uint16_t r, g, b, c;
  for (uint8_t i = 0; i < 2; i++) {
    tcaSelect(i);
    delay(10);

    if (i == 0) digitalWrite(LED_SENSOR_0, HIGH);
    else        digitalWrite(LED_SENSOR_1, HIGH);

    tcs.getRawData(&r, &g, &b, &c);

    String corDetectada = identificarCor(r, g, b, c);

    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" -> R: ");
    Serial.print(r);
    Serial.print(" G: ");
    Serial.print(g);
    Serial.print(" B: ");
    Serial.print(b);
    Serial.print(" C: ");
    Serial.print(c);
    Serial.print(" => Cor: ");
    Serial.println(corDetectada);
    delay(500);
  }
  Serial.println("----------------------");
  delay(1000);
}
