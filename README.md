# ESP-NOW
##ESP-NOW Multi-Node Sensor Network (ESP32 & ESP8266)


A low-power wireless sensor network built using ESP-NOW protocol, featuring multiple ESP8266 and ESP32 devices sending environmental data to a central ESP32 gateway. The system is scalable, reliable, and lightweight — ideal for IoT projects.

---

## 🛠 Features

- 🔁 ESP-NOW communication (no WiFi required)
- 🌡️ Temperature & humidity via DHT22
- 💨 Gas detection via MQ2
- 🌬️ Atmospheric pressure via BMP280
- ⏱️ Timestamping via DS3231 RTC
- 🖥️ Central OLED display on ESP32 gateway
- 📦 Modular codebase (easy to add more sensor nodes)

---

## 📡 System Architecture
[ESP8266-DHT22] [ESP8266-MQ2] [ESP32-BMP280+RTC]
\ | /
\ | /
________ ESP-NOW (2.4 GHz) ________/
|
[ESP32 Gateway w/ OLED]

---

## 🔌 Hardware Components

| Device | Component        | Notes                     |
|--------|------------------|---------------------------|
| ESP8266 | DHT22 Sensor      | Temp & Humidity           |
| ESP8266 | MQ2 Gas Sensor    | Smoke & Gas Detection     |
| ESP32   | BMP280 + RTC DS3231 | Pressure + Timestamp     |
| ESP32   | SSD1306 OLED      | Data display              |

---

## 📁 Project Structure
esp-now-multinode-network/
├── nodes/
│ ├── sender_esp8266_dht22/
│ ├── sender_esp8266_mq2/
│ └── sender_esp32_bmp280_rtc/
│ └── receiver_gateway_esp32.ino
├── shared/
│ ├── common_structs.h
│ └── macros.h
└── README.md


