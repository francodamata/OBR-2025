# 🎨 Projeto: Leitura de Cores com Dois Sensores TCS34725 via TCA9548A e Arduino Mega

Este projeto demonstra como utilizar **dois sensores de cor TCS34725** simultaneamente com um **multiplexador I²C TCA9548A**, conectados ao **Arduino Mega 2560**, para leitura e identificação de cores básicas como **vermelho**, **verde**, **azul**, **branco** e **preto**.

---

## 🔧 Materiais Utilizados

| Quantidade | Item                         |
|------------|------------------------------|
| 1          | Arduino Mega 2560            |
| 2          | Sensor de cor TCS34725       |
| 1          | Multiplexador I²C TCA9548A   |
| 1          | Protoboard                   |

---

## ⚙️ Ligações

### 🟦 Conexões do TCA9548A com o Arduino Mega:

| TCA9548A | Arduino Mega |
|----------|--------------|
| VIN      | 5V           |
| GND      | GND          |
| SDA      | 20           |
| SCL      | 21           |

---

### 🔴 Conexões dos sensores TCS34725 com o TCA9548A:

#### Sensor 1 (canal 0):

| TCS34725 | Canal 0 do TCA9548A |
|----------|---------------------|
| VIN      | VIN (5V)            |
| GND      | GND                 |
| SDA      | SDA0                |
| SCL      | SCL0                |
| LED      | Pino 22 do Arduino  |

#### Sensor 2 (canal 1):

| TCS34725 | Canal 1 do TCA9548A |
|----------|---------------------|
| VIN      | VIN (5V)            |
| GND      | GND                 |
| SDA      | SDA1                |
| SCL      | SCL1                |
| LED      | Pino 24 do Arduino  |
