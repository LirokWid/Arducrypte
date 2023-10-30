#include "anim_loop.h"

//This file modify the leds color depending on an event

extern CRGB leds[NUM_LEDS];
extern mainData ledData;

void event_loop()
{
    uint8_t sum = 0;
    switch (ledData.event)
    {
        case FADE_BLACK:
        for (int i = 0; i < NUM_LEDS; i++)
        {
            sum += leds[i].r + leds[i].g + leds[i].b;
        }
        if (sum > 0)
        {
            fadeOutBPM(ledData.bpm);
        }
        else
        {
            ledData.animation = STATIC;
        }
        break;
    }
}