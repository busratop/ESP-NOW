#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "common_structs.h"
#include "macros.h"

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Structure to receive data
struct_message incomingData;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("ESP32 Gateway Ready");
  display.display();

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  // Register receive callback
  esp_now_register_recv_cb(OnDataReceived);

  Serial.println("ESP32 Gateway initialized");
}

// ESP-NOW receive callback
void OnDataReceived(const uint8_t * mac, const uint8_t *incoming, int len) {
  memcpy(&incomingData, incoming, sizeof(incomingData));

  Serial.print("Data received from sender ID: ");
  Serial.println(incomingData.senderId);

  // Display based on sender ID
  display.clearDisplay();
  display.setCursor(0, 0);

  if (incomingData.senderId == SENDER_ID_DHT22) {
    display.println("Sender: DHT22");
    display.print("Temp: ");
    display.println(incomingData.temperature);
    display.print("Humidity: ");
    display.println(incomingData.humidity);
  }
  else if (incomingData.senderId == SENDER_ID_MQ2) {
    display.println("Sender: MQ2");
    display.print("Gas Voltage: ");
    display.println(incomingData.gas);
  }
  else if (incomingData.senderId == SENDER_ID_BMP280) {
    display.println("Sender: BMP280");
    display.print("Temp: ");
    display.println(incomingData.temperature);
    display.print("Pressure: ");
    display.println(incomingData.pressure);
    display.print("Time: ");
    display.println(incomingData.timestamp);
  }
  else {
    display.println("Unknown sender");
  }

  display.display();
}
