/**
 * @file global.h
 * @author LirokWid
 * @brief 
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GLOBAL_H
#define GLOBAL_H
#include <Arduino.h>
#include <WiFi.h>
#include "params.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>

extern WiFiClient wifi;
extern AsyncWebSocket ws;
extern AsyncWebServer server;
extern JSONVar jsonValues;

/**
 * @brief struct of the color
 * 
 */
struct Color{
  int r;
  int g;
  int b;
};

/**
 * @brief struct of the main data
 * 
 */
struct mainData
{
  float bpm;
  Color color;
  int animation;
  int brightness;
  int animationSpeed;

  int event;
};
extern mainData ledData;

/**
 * @brief enum of all the animations
 * 
 */
enum animation
{
  STATIC,
  BPM,
  STROBE,
  FADE_BLACK,
  WAVE,
  WAVE_FULL,
  STROBE_SPARKLING,
  PULSE,
  SLIDERAIN,
  SLIDE_X_LEFT,
  SLIDE_Y_UP,
  FLASH_RANDOM_STICK
};

/**
 * @brief enum of all the animations nodes
 * 
 */
enum animationMode{
  STATIC_MODE,
  ANIM_MODE
};

#endif