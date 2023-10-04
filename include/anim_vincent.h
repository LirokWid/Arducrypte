#ifndef ANIM_VINCENT_H
#define ANIM_VINCENT_H
    #include <FastLED.h>
    #include "params.h"
    #include "tools.h"
    #include "task.h"


    #define NB_LED_LIGNE 108
    #define NB_LIGNE 4

    void slide_rain(int step, CRGB color);
    void slideline(int step, CRGB color);



#endif