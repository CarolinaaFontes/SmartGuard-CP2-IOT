# SmartGuard IoT — Monitoramento Inteligente com ESP32, MQTT, Node-RED e MySQL

## Descrição do Projeto

O **SmartGuard IoT** é uma solução de monitoramento inteligente desenvolvida para simular o acompanhamento de uma área restrita ou ambiente controlado utilizando conceitos de Internet das Coisas.

O sistema utiliza um **ESP32 simulado no Wokwi**, conectado a sensores físicos simulados, para coletar dados de aproximação e luminosidade. Esses dados são enviados via protocolo **MQTT** para o **Node-RED**, onde são processados, exibidos em um dashboard em tempo real e armazenados em um banco de dados **MySQL/MariaDB**.

Além dos sensores, o projeto também contempla uma integração com uma **API externa de clima**, exibindo dados ambientais externos no dashboard.

---

## Objetivo

Desenvolver uma arquitetura IoT completa, contemplando:

- Coleta de dados por sensores conectados ao ESP32;
- Comunicação via MQTT;
- Processamento dos dados no Node-RED;
- Exibição em dashboard em tempo real;
- Persistência dos dados em banco MySQL;
- Consumo de API externa;
- Documentação técnica para entrega acadêmica.

---

## Problema Simulado

O projeto simula o monitoramento de uma área restrita, sala técnica, laboratório ou ambiente sensível.

O sistema identifica:

- Aproximação de pessoas ou objetos;
- Nível de luminosidade do ambiente;
- Status geral do ambiente;
- Dados climáticos externos para contextualização ambiental.

Quando uma aproximação é detectada, o sistema aciona um LED de alerta e atualiza os dados no dashboard.

---

## Tecnologias Utilizadas

| Tecnologia | Finalidade |
|---|---|
| ESP32 | Microcontrolador principal |
| Wokwi | Simulação do circuito físico |
| HC-SR04 | Sensor ultrassônico para medir distância |
| LDR | Sensor de luminosidade |
| LED | Indicador visual de alerta |
| MQTT | Comunicação entre ESP32 e Node-RED |
| Mosquitto/HiveMQ | Broker MQTT |
| Node-RED | Processamento, integração e dashboard |
| Node-RED Dashboard | Visualização em tempo real |
| MySQL/MariaDB | Persistência dos dados |
| MySQL Workbench | Administração e validação do banco |
| Open-Meteo API | API externa de clima |
| GitHub | Versionamento e documentação |

---

## Arquitetura da Solução

```text
Sensores físicos/simulados
        |
        v
ESP32 / Wokwi
        |
        | MQTT - JSON
        v
Broker MQTT
        |
        v
Node-RED
   |        |          |
   |        |          +--> Dashboard em tempo real
   |        |
   |        +--> MySQL/MariaDB
   |
   +--> API externa de clima
