#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <RTClib.h>
#include "common_structs.h"
#include "macros.h"

// BMP280 and RTC instances
Adafruit_BMP280 bmp;       // I2C
RTC_DS3231 rtc;

// Data structure to send
struct_message outgoingData;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // I2C init

  // Initialize BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not detected!");
    while (1);
  }

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting to current time.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set to compile time
  }

  // WiFi setup
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // ESP-NOW init
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(gatewayAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  Serial.println("ESP32 BMP280 + RTC Sender Initialized");
}

// Optional: callback on send
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Delivery Status: ");
  Serial.println(sendStatus == 0 ? "Success" : "Fail");
}

void loop() {
  // Read BMP280 sensor data
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;  // Convert to hPa

  // Read timestamp from RTC
  DateTime now = rtc.now();
  snprintf(outgoingData.timestamp, TIMESTAMP_LENGTH, "%04d-%02d-%02d %02d:%02d",
           now.year(), now.month(), now.day(), now.hour(), now.minute());

  // Fill struct
  outgoingData.senderId = SENDER_ID_BMP280;
  outgoingData.temperature = temperature;
  outgoingData.pressure = pressure;

  // Send data
  esp_now_send(gatewayAddress, (uint8_t *) &outgoingData, sizeof(outgoingData));

  // Debug
  Serial.print("Sent => Temp: ");
  Serial.print(temperature);
  Serial.print(" °C, Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa, Timestamp: ");
  Serial.println(outgoingData.timestamp);

  delay(5000);
}
