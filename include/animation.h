#ifndef ANIMATION_H
#define ANIMATION_H
#include <FastLED.h>
#include "params.h"
#include "tools.h"

extern CRGB leds[NUM_LEDS];

void static_animation();
void strobe_bpm(float bpm,CRGB color);
void gauche_droite(float bpm,CRGB color,int row,int col);
void colorChaseAnimation(CRGB color, int wait);
void chenillard(float Hz,CRGB color);
CRGB random_color();
void pulseAnimation(int durationMs);
void flash_random_stick(int flash_delay,CRGB color);
void randomSparkleAnimation(int durationMs,CRGB color);
void color_wave_animation(int durationMs);
void beat_bpm(int durationMs, CRGB color1, CRGB color2);

#endif
