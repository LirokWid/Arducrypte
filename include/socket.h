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
#include "login.h"


/**
 * @brief handle incoming websocket messages and parse them
 * @param arg 
 * @param data 
 * @param len 
 */
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

/**
 * @brief Check if a message contains a specific keyword
 * 
 * @param keyword String to search for
 * @param message String to search in
 * @return true 
 * @return false 
 */
bool messageContains(const char* keyword, const char* message);

/**
 * @brief handle websocket events
 * 
 * @param server 
 * @param client 
 * @param type 
 * @param arg 
 * @param data 
 * @param len 
 */
void onEvent(AsyncWebSocket *server,AsyncWebSocketClient *client,AwsEventType type,void *arg, uint8_t *data, size_t len);

/**
 * @brief initialize the websocket
 * 
 */
void initSocket();

/**
 * @brief Send a message to all clients
 * 
 * @param message 
 */
void notifyClients(String message);

/**
 * @brief Get all data values as a JSON string
 * 
 * @return JSON string 
 */
String getValues();

/**
 * @brief Kill client connections if they are not active
 * 
 */
void cleanupClients();

/**
 * @brief Initialize the SPIFFS filesystem
 * 
 */
void initFS();

/**
 * @brief Setup and connect to the wifi in AP or STA mode
 * 
 */
void setupWifi();

/**
 * @brief Initialize the webserver
 * 
 */
void initWebServer();


#endif // SOCKET_H
