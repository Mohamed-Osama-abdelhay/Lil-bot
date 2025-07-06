# 🤖 Lil bot

This project is a distributed robotic control system integrating multiple microcontrollers. It features a Master-Slave Arduino communication architecture, wireless networking using ESP32 and ESP8266, and a main robot control unit.

## 🧩 Project Modules

| File                     | Description |
|--------------------------|-------------|
| `Robot main code.ino`    | Core robot logic, controlling motors, actuators, and responding to inputs. |
| `Arduino (Master).ino`   | Acts as the controller, coordinating communication between slave units. |
| `Arduino (Slave).ino`    | Handles peripheral tasks like sensor data collection, on master's request. |
| `ESP32.ino`              | Provides Wi-Fi/Bluetooth capability, enabling remote control or monitoring. |
| `ESP8266.ino`            | Secondary wireless interface, possibly used for MQTT, cloud sync, or lightweight remote tasks. |

## 🛠 Hardware Used

- Arduino Uno / Nano (x2 or more)
- ESP32 Dev Module
- ESP8266 NodeMCU / WeMos D1 Mini
- Motor Driver (e.g., L298N)
- Sensors (IR, ultrasonic, encoders, etc.)
- Wheels, chassis, and power supply (battery pack)

## 🔌 System Overview

### Control Flow

1. **ESP32 / ESP8266**  
   Handle wireless connectivity — one might serve a webpage for control; the other might relay commands via MQTT.

2. **Arduino Master**  
   Central brain — receives commands from ESP modules and delegates actions to Slave(s) or Robot Main.

3. **Arduino Slave**  
   Peripheral node — may read sensors or actuate simple components.

4. **Robot Main (Separate or Master)**  
   Handles real-time motor control and robot movements.

### Communication Protocols

- **UART / I2C** between Arduinos (Master ↔ Slave)
- **Serial / UART / WiFi** between ESP modules and Master
- **WiFi** for web/MQTT communication with external device

## 📦 How to Use

### 1. Flash the Code

- Upload `Robot main code.ino` to your robot controller board (likely an Arduino).
- Upload `Arduino (Master).ino` and `Arduino (Slave).ino` to their respective Arduinos.
- Upload `ESP32.ino` to ESP32, and `ESP8266.ino` to ESP8266.

### 2. Set Wi-Fi Credentials

In `ESP32.ino` and `ESP8266.ino`, modify the following:

```cpp
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
```
### 3. Wiring
Motor driver connected to Robot main board.

ESP32/ESP8266 TX/RX to Arduino Master.

I2C (SDA/SCL) or UART between Master and Slave Arduinos.

### 4. Monitor and Control
Use Serial Monitor for debugging.

ESP32/8266 may host a web interface or subscribe to MQTT topics.

### 📈 Potential Features
Web-based robot control interface

Real-time telemetry (battery, position, etc.)

Autonomous navigation or remote/manual driving

Cloud integration for data logging

### 🧪 Testing Steps
Power all components.

Connect ESP modules to known Wi-Fi.

Monitor Serial logs to verify communication.

Send commands via web/MQTT or serial to trigger robot motion or sensor readouts.

### 🔧 Libraries Required
Install in Arduino IDE via Library Manager or ZIP:

WiFi.h / ESP8266WiFi.h

Wire.h

SoftwareSerial.h

ESPAsyncWebServer.h (optional for web interface)

PubSubClient.h (for MQTT, if used)
