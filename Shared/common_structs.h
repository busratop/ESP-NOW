#ifndef COMMON_STRUCTS_H
#define COMMON_STRUCTS_H

#include <Arduino.h>

// Max character length (Exp: "2025-06-29 15:42")
#define TIMESTAMP_LENGTH 20

typedef struct struct_message {
  uint8_t senderId;                // Send node ID (Exp: 1, 2, 3)
  float temperature = 0.0;
  float humidity = 0.0;
  float gas = 0.0;
  float pressure = 0.0;
  char timestamp[TIMESTAMP_LENGTH] = "N/A";  // If not RTC "N/A"
} struct_message;

#endif
