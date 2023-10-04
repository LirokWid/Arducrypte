#ifndef TASK_H
#define TASK_H

#include <Arduino.h>
#include <FastLED.h>
#include "params.h"


void FastLEDshowESP32();

void FastLEDshowTask(void *pvParameters);


void createShowTask();

#endif // TASK_H