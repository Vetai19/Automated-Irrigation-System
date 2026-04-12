# Automated Irrigation System: Distributed PID Control & IoT Telemetry

## 1. Project Overview
[cite_start]This repository contains a **three-tier distributed automation system** designed to solve water scarcity through precision irrigation[cite: 74, 75]. Unlike monolithic architectures, this system decouples the **Real-Time Control Law** from the **Network Communication Layer** to ensure industrial-grade reliability and deterministic performance.

---

## 2. System Requirements

### 2.1 Hardware Requirements
* **Microcontrollers**: 
    * [cite_start]1x **Arduino Uno** (Atmega328P): Dedicated to high-speed deterministic control[cite: 102].
    * [cite_start]1x **NodeMCU** (ESP8266): Dedicated as an IoT/MQTT gateway[cite: 98, 100].
* **Sensors & Actuators**: 
    * [cite_start]1x **Conductive Soil Moisture Sensor**: For real-time moisture acquisition[cite: 103, 104].
    * [cite_start]1x **Submersible DC Water Pump**: Final control element for irrigation[cite: 95].
    * [cite_start]1x **Single-Phase Relay** or BJT: For PWM-based power switching[cite: 82, 85, 108].
* **Power & Interfacing**: 
    * [cite_start]9V Battery with a **Voltage Regulator** (5V/3.3V)[cite: 83, 86].
    * **Logic Level Shifter**: Required for 5V (Arduino) to 3.3V (ESP8266) UART communication.

### 2.2 Software Requirements
* [cite_start]**Environment**: Arduino IDE (C++ firmware) and Python 3.x (Local SCADA)[cite: 102, 134, 173].
* **Libraries**: 
    * [cite_start]`PubSubClient.h` (ESP8266 MQTT)[cite: 174].
    * [cite_start]`paho-mqtt` (Python Client)[cite: 135].
* [cite_start]**Cloud Infrastructure**: **CloudMQTT** Broker account (Port **12038**)[cite: 152, 153].

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
* [cite_start]**Input**: Moisture Sensor Signal $\rightarrow$ **Arduino A0**[cite: 121, 181].
* [cite_start]**Output**: Arduino **Pin 9** (PWM) $\rightarrow$ Relay/BJT $\rightarrow$ Pump[cite: 114, 129].

---

## 4. Technical Highlights

### 4.1 Advanced Control Law
* **Manual PID Implementation**: Features **Anti-Windup Clamping** to prevent integral saturation and a dynamic $dt$ calculation for mathematical rigor.
* **Signal Conditioning**: Employs a **First-Order Low-Pass Filter** (Exponential Moving Average) to suppress high-frequency moisture sensor jitter.

### 4.2 Distributed IoT Logic
* **Decoupled Reliability**: The Arduino maintains the **Safety Instrumented Function (SIF)** independently; irrigation continues even if WiFi connectivity is lost.
* **Asynchronous Telemetry**: NodeMCU handles the TCP/IP stack overhead, preventing network latency from affecting the PID sampling rate.

---

## 5. Implementation Notes
* [cite_start]**Maintenance**: Conductive metal sensors require frequent maintenance due to oxidation from moisture exposure[cite: 239].
* [cite_start]**Scalability**: The modular MQTT structure allows for multiple node deployments with centralized data retrieval for research purposes[cite: 237].
