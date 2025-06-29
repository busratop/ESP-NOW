#ifndef MACROS_H
#define MACROS_H

// Her cihaza özel ID
#define SENDER_ID_DHT22   1
#define SENDER_ID_MQ2     2
#define SENDER_ID_BMP280  3

// Receiver MAC adress (to be used in transmitters)
// You need to enter the Gateway ESP32's MAC address here (sample address)
uint8_t gatewayAddress[] = { 0x24, 0x6F, 0x28, 0xA1, 0xB2, 0xC3 };

#endif
