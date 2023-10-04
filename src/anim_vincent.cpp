#include "anim_vincent.h"

extern CRGB leds[NUM_LEDS];

void slide_rain(int step, CRGB color) 
{
  // Animation de défilement de la colonne vers la droite


    // Allumer la colonne décalée vers la droite
    for (int col1=0; col1 < NB_LED_LIGNE; col1++) 
    {
        int ledIndex = step + col1*NB_LIGNE;
        leds[ledIndex] = color;
    }
    FastLEDshowESP32();

    // Éteindre la colonne décalée vers la droite
    for (int col1=0; col1 < NB_LED_LIGNE; col1++) 
    {
        int ledIndex = (step) + col1*NB_LIGNE;
        leds[ledIndex] = CRGB::Black;
    }
}

void slideline(int step, CRGB color)
{
    for (int row1=0; row1 < NB_LED_LIGNE; row1++) 
    {
        int ledIndex = NB_LED_LIGNE*step+row1;
        leds[ledIndex] = color;
    }
    FastLEDshowESP32();
    for (int row1=0; row1 < NB_LED_LIGNE; row1++) 
    {
        int ledIndex = NB_LED_LIGNE*step+row1;
        leds[ledIndex] = CRGB::Black; // Vous pouvez changer la couleur si vous le souhaitez
    }
}
