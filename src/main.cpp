/**
 * @file main.cpp
 * @author LirokWid
 * @brief This is the main file of the project
 * @version 0.1
 * @date 2023-10-04
 * 
 * @copyright 
 * 
 */

#include <Arduino.h>
#include <FastLED.h>
#include "params.h"

/**
 * @brief enum for the different animations
 * 
 */



#include "socket.h"
#include "task.h"

#include "anim_loop.h"

CRGB leds[NUM_LEDS];
mainData ledData;





void pulse(int step, CRGB color)
{
}

void setup()
{
  Serial.begin(115200);

  ledData.bpm = 150;
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); // for GRB LEDs
  // turn_off();
  Serial.print("Main code running on core ");
  Serial.println(xPortGetCoreID());
  createShowTask();
  initWebServer();
  Serial.println("Setup done");
}

void loop()
{
  animation_loop();
  cleanupClients();
}