#ifndef ANIM_MAXIME_H
#define ANIM_MAXIME_H
    #include <FastLED.h>
    #include "params.h"
    #include "tools.h"

    void wave(int step, CRGB color1, CRGB color2);
    void wave_full(int step, CRGB color1, CRGB color2);
    void strobe_sparkling(int qte, CRGB color);

#endif