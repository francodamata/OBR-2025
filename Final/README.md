# 🤖 Robô Seguidor de Linha - OBR Presencial

Este projeto apresenta um **robô seguidor de linha** desenvolvido para a **Olimpíada Brasileira de Robótica (OBR) presencial**. O código foi inicialmente baseado na versão virtual/simulada (rEduc no sBotics), mas adaptado para a versão física utilizando Arduino e sensores LDR.

---

## 📌 Objetivo
O robô tem como objetivo:
- Seguir uma linha preta em fundo branco.
- Utilizar controle **PID** para corrigir a trajetória.
- Manter a velocidade constante com ajustes suaves nas curvas.
- Reconhecer a posição da linha através de sensores **LDR**.

---

## ⚙️ Hardware Utilizado
- **1x Arduino (Nano ou Uno)**  
- **2x Motores DC** (direito e esquerdo)  
- **2x Ponte H L298N ou L293D**  
- **5x Sensores LDR** dispostos da esquerda para a direita  
- **Resistores para divisor de tensão dos LDRs**  
- **Bateria compatível (7.4V LiPo ou 9V)**  

### Esquema dos LDRs
Os sensores foram organizados da **esquerda para a direita**:

[LDR0] [LDR1] [LDR2] [LDR3] [LDR4]


Cada um lê a intensidade de luz refletida no piso.  
Quanto mais próximo da linha preta, menor a reflexão.

---

## 🧮 Lógica do Controle

1. **Leitura dos LDRs**  
   Cada sensor gera um valor analógico que é convertido em posição relativa da linha.

2. **Cálculo da Posição da Linha**  
   A posição é obtida ponderando cada sensor pelo seu peso (da esquerda para a direita).  

   Exemplo:
   - LDR1 = posição -3  
   - LDR2 = posição -1  
   - LDR3 = posição +1  
   - LDR4 = posição +3  

3. **Erro**  
   O erro é a diferença entre a posição lida e a posição central (0).  

4. **Controle PID**  
   - `Kp` → corrige a intensidade do erro.  
   - `Kd` → suaviza mudanças bruscas.  
   - `Ki` → (opcional) corrige erros acumulados.  

   Fórmula do controle:  
PID = (Kp * erro) + (Kd * (erro - erroAnterior)) + (Ki * somaErros)


5. **Controle dos Motores**  
- Motor esquerdo = VelocBase - PID  
- Motor direito  = VelocBase + PID  

Dessa forma, se o robô desviar para a esquerda, o PID corrige aumentando a velocidade do motor esquerdo e diminuindo o direito (e vice-versa).

---

## 🚀 Passo a Passo do Código

1. **Declaração das variáveis**  
Define-se `Kp`, `Kd`, `Ki`, `VelocBase`, além das variáveis para posição e erro.  

2. **Função de leitura dos sensores**  
Lê os valores dos LDRs, calcula a posição e determina o erro.  

3. **Função PID**  
Calcula o valor de correção com base no erro atual, erro anterior e soma acumulada.  

4. **Controle de motores**  
Ajusta dinamicamente a velocidade dos motores esquerdo e direito.  

5. **Loop principal**  
O robô:
- Lê os sensores.
- Calcula a posição da linha.
- Aplica o controle PID.
- Corrige os motores.
- Repete o ciclo continuamente.

---

## 📊 Ajuste dos Parâmetros PID
O ajuste do PID deve ser feito experimentalmente:

1. Comece com `Kp` alto até o robô seguir a linha mas com oscilações.  
2. Aumente `Kd` para reduzir oscilações.  
3. Adicione `Ki` se o robô apresentar erros acumulados (não manter centro por muito tempo).  

---

## 🏁 Conclusão
Este código serve como **base inicial** para o robô seguidor de linha da OBR presencial.  
Com ele, é possível:
- Ajustar parâmetros para diferentes pistas.  
- Evoluir para reconhecer áreas especiais (quadrados verdes, obstáculos, resgates).  

---

## 📜 Licença
Este projeto é de uso livre para fins educacionais e competições de robótica.
