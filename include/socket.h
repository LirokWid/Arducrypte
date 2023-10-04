#ifndef SOCKET_H
#define SOCKET_H

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <Arduino_JSON.h>
#include <FastLED.h>

#include "SPIFFS.h"

#include "params.h"
#include "global.h"
#include "task.h"


void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
// Check if a message contains a specific keyword
bool messageContains(const char* keyword, const char* message);
void onEvent(AsyncWebSocket *server,AsyncWebSocketClient *client,AwsEventType type,void *arg, uint8_t *data, size_t len);

void initSocket();
void notifyClients(String sliderValues);
String getValues();
void cleanupClients();
void initFS();
void setupWifi();
void initWebServer();
void handleWeb();

#endif // SOCKET_H
