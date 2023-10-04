#include "animation.h"



void strobe_bpm(float bpm,CRGB color)
{

  int delay_strobe = 60000/bpm;// Pour récupérer le délais par rapport aux bpm

    for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }
  FastLED.show();
  delay(delay_strobe/2);
      for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
    FastLED.show();
  delay(delay_strobe/2);
}

void gauche_droite(float bpm,CRGB color,int row,int col)
{

  int nb_mid= (STICK_NB/2)*STICK_LED_NB; 
  int delay_strobe = 60000/bpm;// Pour récupérer le délais par rapport aux bpm

  for (int i = 0; i < nb_mid; i++)
  {
    leds[i] = 0;
  }

    for (int i = nb_mid; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }
  FastLED.show();
  
  delay(delay_strobe/2);

  for (int i = 0; i < nb_mid; i++)
  {
    leds[i] = color;
  }
    for (int i = nb_mid; i < NUM_LEDS; i++)
  {
    leds[i] = 0;
  }
  FastLED.show();
  delay(delay_strobe/2);
}

void colorChaseAnimation(CRGB color, int wait) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; // Éteint toutes les LED
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;       // Allume la LED actuelle avec la couleur spécifiée
    FastLED.show();
    delay(wait);
    leds[i] = CRGB::Black; // Éteint la LED après le délai
  }
}

void chenillard(float Hz,CRGB color)
{
}

CRGB random_color()
{

  return CRGB(random(0, 255), random(0, 255), random(0, 255));
}

void pulseAnimation(int durationMs) 
{
  unsigned long startTime = millis();
  
  while (millis() - startTime < durationMs) {
    for (int brightness = 0; brightness <= 255; brightness += 5) {
      FastLED.setBrightness(brightness);
      FastLED.show();
      delay(20);
    }
    
    for (int brightness = 255; brightness >= 0; brightness -= 5) {
      FastLED.setBrightness(brightness);
      FastLED.show();
      delay(20);
    }
  }
}
void flash_random_stick(int flash_delay,CRGB color)
{
  change_stick_color(random_stick_no_repeat(),color);
  delay(flash_delay);
  turn_off();
}

void randomSparkleAnimation(int durationMs,CRGB color)
{
  unsigned long startTime = millis();
  
  while (millis() - startTime < durationMs) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (random(5) == 0) {
        leds[i] = color;
      } else {
        leds[i] = CRGB::Black;
      }
    }
    
    FastLED.show();
    delay(50);
  }
}

void color_wave_animation(int durationMs)
{
  unsigned long startTime = millis();
  uint8_t waveSpeed = 5;
  uint8_t offset = 0;

  while (millis() - startTime < durationMs) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV((offset + i * waveSpeed) % 256, 255, 255);
    }

    FastLED.show();
    delay(30);

    offset++;
  }
}
void beat_bpm(int durationMs, CRGB color1, CRGB color2)
{

  unsigned long startTime = millis();
  int beatInterval = 500;

  while (millis() - startTime < durationMs) {
    int beatPhase = (millis() / beatInterval) % 2;
    if (beatPhase == 0) {
      fill_solid(leds, NUM_LEDS, color1);
    } else {
      fill_solid(leds, NUM_LEDS, color2);
    }

    FastLED.show();
    delay(10);
  }
}


