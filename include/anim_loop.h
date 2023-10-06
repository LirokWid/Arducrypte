#ifndef ANIM_LOOP_H
#define ANIM_LOOP_H
    #include <FastLED.h>
    #include "params.h"
    #include "tools.h"
    #include "task.h"
    #include "global.h"
    #include "anim_maxime.h"
    #include "anim_vincent.h"
    #include "animation.h"



    void static_animation();

    bool bpmTimer(float bpm);
    bool millisTimer(int durationMs);
    void fadeOutBPM(uint16_t bpm);
    void animation_loop();


#endif