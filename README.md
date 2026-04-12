# Automated Irrigation System: Distributed PID Control & IoT Telemetry

## 1. Project Overview
This repository contains a **three-tier distributed automation system** designed to solve water scarcity through precision irrigation. By decoupling the **Real-Time Control Law** from the **Network Communication Layer**, the system ensures industrial-grade reliability and prevents network latency from affecting the control sampling rate.

---

## 2. System Requirements

### 2.1 Hardware Requirements
* **Microcontrollers**: 
    * 1x **Arduino Uno**: Dedicated to high-speed deterministic control.
    * 1x **NodeMCU (ESP8266)**: Dedicated as an IoT/MQTT gateway.
* **Sensors & Actuators**: 
    * 1x **Conductive Soil Moisture Sensor**: For real-time moisture acquisition.
    * 1x **Submersible DC Water Pump**: Final control element for irrigation.
    * 1x **Single-Phase Relay**: For power switching and RPM control.
* **Power & Interfacing**: 
    * 9V Battery with a **Voltage Regulator**.
    * **Logic Level Shifter**: Required for 5V (Arduino) to 3.3V (NodeMCU) UART communication.

### 2.2 Software Requirements
* **Firmware**: Arduino IDE for C++ implementation.
* **SCADA/Monitoring**: Python 3.x for local PC data retrieval.
* **IoT Infrastructure**: **CloudMQTT** Broker account (Port **12038**).

---

## 3. System Connections (Wiring Map)

The architecture utilizes a **UART Serial Bridge** to separate control and communication tasks.

### 3.1 Inter-Chip UART Connection
| From (Arduino Uno) | To (NodeMCU/ESP8266) | Purpose |
| :--- | :--- | :--- |
| **TX (Pin 1)** | **RX (Pin 3)** | Telemetry data transmission |
| **RX (Pin 0)** | **TX (Pin 1)** | Command reception |
| **GND** | **GND** | Common voltage reference |

### 3.2 Sensor & Actuator Mapping
* **Input**: Moisture Sensor Signal $\rightarrow$ **Arduino A0**.
* **Output**: Arduino **Pin 3/9** (PWM) $\rightarrow$ Relay $\rightarrow$ Pump.

---

## 4. Technical Highlights

### 4.1 Advanced Control Law
* **Manual PID Implementation**: Coded from first principles to include **Anti-Windup Clamping** and dynamic $dt$ calculations, ensuring stability during actuator saturation.
* **Signal Conditioning**: Employs a **First-Order Digital Low-Pass Filter** to suppress sensor noise while managing phase-lag for loop stability.

### 4.2 Distributed IoT Logic
* **Decoupled Reliability**: The Arduino maintains the control loop independently; irrigation continues even if WiFi connectivity is lost.
* **Asynchronous Telemetry**: The NodeMCU handles the TCP/IP stack overhead, ensuring the PID sampling rate remains constant.

---

## 5. Implementation Notes
* **Maintenance**: Conductive metal sensors require frequent maintenance due to oxidation from moisture exposure.
* **Data Security**: Centralized cloud storage allows for historical research but requires monitoring for potential data corruption.
