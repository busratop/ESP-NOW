#include <ESP8266WiFi.h>
#include <espnow.h>
#include <DHT.h>
#include "common_structs.h"
#include "macros.h"

// DHT sensor settings
#define DHTPIN D4      // GPIO2 on NodeMCU
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Data structure to send
struct_message outgoingData;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Set device in station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer (gateway)
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(gatewayAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Debug: Print MAC address
  Serial.print("Sender MAC Address: ");
  Serial.println(WiFi.macAddress());

  Serial.println("ESP8266 DHT22 Sender Initialized");
}

void loop() {
  // Read temperature and humidity from DHT22
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Validate sensor data
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT22 sensor");
    delay(2000);
    return;
  }

  // Fill the outgoing struct
  outgoingData.senderId = SENDER_ID_DHT22;
  outgoingData.temperature = temp;
  outgoingData.humidity = hum;

  // Send data to the gateway
  esp_now_send(gatewayAddress, (uint8_t *) &outgoingData, sizeof(outgoingData));

  // Debug output
  Serial.print("Sent => Temp: ");
  Serial.print(temp);
  Serial.print(" °C, Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(5000);  // Wait before sending next data
}
