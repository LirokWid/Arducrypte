#pragma once

//Stick setup
#define STICK_LED_NB 36
#define STICK_NB 12
#define NUM_LEDS STICK_LED_NB*STICK_NB
#define STICK_X_NB 4
#define STICK_Y_NB 3


#define DATA_PIN 23
#define FASTLED_SHOW_CORE 0

//LED setup
#define LED_BUILTIN 2

#define ANIMATION_STEPS 10
#define PULSE_STEPS 100
#define STICK_PER_LINE 3
#define NB_LINE 4
#define PROTO
#ifdef PROTO
  #define BS_NB 0
  #define BB_NB 0
#else
  #define BS_NB 2 //BACK_SCENE
  #define BB_NB 1 //BACK_BASS
#endif

#define MAIN_NB STICK_NB-BS_NB-BB_NB

//Wifi setup
#define AP_MODE true



//Webserver setup
#define SERVER_PORT 80
