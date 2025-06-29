#include <ESP8266WiFi.h>
#include <espnow.h>
#include "common_structs.h"
#include "macros.h"

// MQ2 analog pin
#define MQ2_PIN A0

// Data structure to send
struct_message outgoingData;

void setup() {
  Serial.begin(115200);

  // Set WiFi mode and disconnect from AP
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  // Register gateway as peer
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(gatewayAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  Serial.print("Sender MAC Address: ");
  Serial.println(WiFi.macAddress());

  Serial.println("ESP8266 MQ2 Sender Initialized");
}

void loop() {
  // Read analog gas value
  int gasValue = analogRead(MQ2_PIN);
  float gasVoltage = gasValue * (3.3 / 1024.0);  // Convert to voltage

  // Fill struct
  outgoingData.senderId = SENDER_ID_MQ2;
  outgoingData.gas = gasVoltage;

  // Send data
  esp_now_send(gatewayAddress, (uint8_t *) &outgoingData, sizeof(outgoingData));

  // Debug print
  Serial.print("Sent => Gas Voltage: ");
  Serial.print(gasVoltage);
  Serial.println(" V");

  delay(5000);
}
