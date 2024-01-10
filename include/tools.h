#ifndef TOOLS_H
#define TOOLS_H

#include <FastLED.h>
#include "params.h"

CRGB complementary_color(int r,int g,int b);
int bpm_to_ms(float bpm);
void fill_block(int from, int qte, CRGB color);
void fill_bar(int bar,CRGB color);
void fill_line(int line, int from, int qte, CRGB color, bool inv);
float bpm_to_hz(float bpm);
float hz_to_ms(float hz);


float hz_to_bpm(float hz);
void change_range_color(int start_led,int last_led,CRGB color);
void change_stick_color(int stick_number,CRGB color);
void turn_off();
void turn_on(CRGB color);
void fadeall();

int random_stick_no_repeat();


#endif