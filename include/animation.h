#ifndef ANIMATION_H
#define ANIMATION_H
#include <FastLED.h>
#include "params.h"
#include "tools.h"

extern CRGB leds[NUM_LEDS];

void static_animation();
//void strobe_bpm(float bpm,CRGB color);
void left_right(float bpm,CRGB color,int row,int col);
void color_chase_animatiopn(CRGB color, int wait);
void chenillard(float Hz,CRGB color);
CRGB random_color();
void pulseAnimation(int durationMs);
void randomSparkleAnimation(int durationMs,CRGB color);
void color_wave_animation(int durationMs);
void beat_bpm(int durationMs, CRGB color1, CRGB color2);
void slide_front_back(int step, CRGB color);
void light_random_stick(CRGB color);

#endif
