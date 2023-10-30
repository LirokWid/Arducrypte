/**
 * @file anim_loop.h
 * @author LiroKwid
 * @brief 
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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

    /**
     * @brief Animation loop
     * 
     * This function is ran in a while loop in the main.cpp,
     * it is the main animation loop and does not contains hard delays
     */
    void animation_loop();


#endif