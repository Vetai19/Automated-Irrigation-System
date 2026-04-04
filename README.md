# Automated Irrigation System: Distributed PID Control & IoT Telemetry

## 1. Project Overview
This repository contains a **three-tier distributed automation system** designed to solve water scarcity through precision irrigation. Unlike monolithic architectures, this system decouples the **Real-Time Control Law** from the **Network Communication Layer** to ensure industrial-grade reliability and deterministic performance.

---

## 2. System Requirements

### 2.1 Hardware Requirements
* **Microcontrollers**: 
    * 1x **Arduino Uno** (Atmega328P): Dedicated to high-speed deterministic control.
    * 1x **NodeMCU** (ESP8266): Dedicated as an IoT/MQTT gateway.
* **Sensors & Actuators**: 
    * 1x **Conductive Soil Moisture Sensor**: For real-time moisture acquisition.
    * 1x **Submersible DC Water Pump**: Final control element for irrigation.
    * 1x **Single-Phase Relay** or BJT: For PWM-based power switching.
* **Power & Interfacing**: 
    * 9V Battery with a **Voltage Regulator** (5V/3.3V).
    * **Logic Level Shifter**: Required for 5V (Arduino) to 3.3V (ESP8266) UART communication.

### 2.2 Software Requirements
* **Environment**: Arduino IDE (C++ firmware) and Python 3.x (Local SCADA).
* **Libraries**: 
    * `PubSubClient.h` (ESP8266 MQTT).
    * `paho-mqtt` (Python Client).
* **Cloud Infrastructure**: **CloudMQTT** Broker account (Port **12038**).

---

## 3. System Connections (Wiring Map)

The system architecture utilizes a **UART Serial Bridge** to separate tasks.

### 3.1 Inter-Chip UART Connection
| From (Arduino Uno) | To (NodeMCU/ESP8266) | Purpose |
| :--- | :--- | :--- |
| **TX (Pin 1)** | **RX (Pin 3)** | Telemetry data transmission |
| **RX (Pin 0)** | **TX (Pin 1)** | Command reception (Optional) |
| **GND** | **GND** | Common voltage reference |

### 3.2 Sensor & Actuator Mapping
* **Input**: Moisture Sensor Signal $\rightarrow$ **Arduino A0**.
* **Output**: Arduino **Pin 9** (PWM) $\rightarrow$ Relay/BJT $\rightarrow$ Pump.

---

## 4. Technical Highlights

### 4.1
