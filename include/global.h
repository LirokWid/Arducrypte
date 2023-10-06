//Define all global variables as externs to be included in other files

#ifndef GLOBAL_H
#define GLOBAL_H
#include <Arduino.h>
#include <WiFi.h>
#include "params.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>


extern WiFiClient wifi;

//#include <FastLED.h>        //cascade d'erreur si inclusion ici
//extern CRGB leds[NUM_LEDS];

extern AsyncWebSocket ws;
extern AsyncWebServer server;
extern JSONVar jsonValues;

struct Color{
  int r;
  int g;
  int b;
};

struct mainData
{
  float bpm;
  Color color;
  int animation;
  int brightness;
  int animationSpeed;
};
extern mainData ledData;

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
  SLIDELINE
};

#endif