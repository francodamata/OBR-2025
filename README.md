# 🤖 Projeto OBR - Modalidade Resgate

Este repositório reúne os códigos desenvolvidos para a **Olimpíada Brasileira de Robótica (OBR)**, na **modalidade Resgate**, voltados ao desenvolvimento, testes e integração do robô seguidor de linha com capacidade de resgate.

## 🧠 Objetivo

Desenvolver, testar e integrar módulos independentes para o controle do robô, incluindo motores, sensores e estratégias, com foco em performance, confiabilidade e modularidade. Ao final, todos os módulos serão combinados em um código principal e definitivo para a competição.

---

## 📁 Estrutura do Repositório
├── ponte_H/   
│   └── TestePonteH.ino.   
├── sensor_TCS34725/        
│   └── tcs_leitura.ino    
├── sensor_Ultrassom/       
│   └── ultrassom_teste.ino     
├── controle_PID/            
│   └── pid_basico.ino.  
├── código_final/            
│   └── resgate_completo.ino.  
└── README.md.     

## 🛠️ Tecnologias Utilizadas

- **Arduino C++**
- **Placa**: Arduino Mega 2560
- **IDE**: Arduino IDE
- **Sensores**:
  - TCS34725 (sensor de cor)
  - TCA9548A (multiplexador I2C)
  - HC-SR04 (sensor ultrassônico)
  - Módulo de sensores reflexivos (IR)
- **Controle**:
  - Ponte H L298N ou similar
  - Algoritmo PID para seguimento de linha

---

## 🚧 Status do Projeto

- [x] Organização inicial do repositório
- [ ] Teste individual da ponte H
- [x] Leitura básica do sensor de cor TCS34725
- [x] Leitura básica do sensor ultrassônico HC-SR04
- [ ] Testes com PID ajustado para diferentes pistas
- [ ] Integração de sensores com controle motor
- [ ] Código final pronto para competição

---

## 📌 Observações

- Cada pasta contém comentários no código explicando o funcionamento de cada módulo.
- O código final está sendo continuamente atualizado com melhorias de cada etapa.
- Recomenda-se carregar e testar os códigos de forma modular antes de utilizar o código final.

---

## 👨‍💻 Autor

Desenvolvido pela equipe **The Fusions**  
Programação comandada por **Franco da Mata**
Estudante | Competidor OBR | Entusiasta em robótica e programação  
📍 IFBA - Campus Salvador

---

## 📜 Licença

Este projeto está sob a licença MIT. Sinta-se à vontade para estudar, modificar e utilizar para fins educacionais e não comerciais.
