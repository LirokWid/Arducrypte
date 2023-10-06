#include "anim_loop.h"

extern CRGB leds[NUM_LEDS];
extern mainData ledData;

void animation_loop()
{
  static bool state = false;
  int strobe_delay = hz_to_ms(15);
  int sum = 0;
  switch (ledData.animation)
    {
    case STATIC:
      static_animation();
      break;

    case BPM:
      if (bpmTimer(ledData.bpm * 2)) //*2 because we want to change color every beat
      {
        if (state)
        {
          // turn all led red
          for (int i = 0; i < NUM_LEDS; i++)
          {
            leds[i].setRGB(ledData.color.r, ledData.color.g, ledData.color.b);
          }
        }
        else
        {
          fill_solid(leds, NUM_LEDS, CRGB::Black);
        }
        state = !state;
        FastLEDshowESP32();
      }
      break;

    case STROBE:
      if (millisTimer(strobe_delay))
      {
        if (state)
        {
          fill_solid(leds, NUM_LEDS, CRGB::White);
        }
        else
        {
          fill_solid(leds, NUM_LEDS, CRGB::Black);
        }
        state = !state;
      }
      FastLEDshowESP32();
      break;

    case FADE_BLACK:
      for (int i = 0; i < NUM_LEDS; i++)
      {
        sum += leds[i].r + leds[i].g + leds[i].b;
      }
      if (sum > 0)
      {
        fadeOutBPM(ledData.bpm);
        FastLEDshowESP32();
      }
      break;

    case WAVE:
      if (millisTimer(bpm_to_ms(ledData.bpm) / ANIMATION_STEPS))
      {
        static int step = 0;
        step = (step + 1) % ANIMATION_STEPS;
        wave(
            step,
            CRGB(ledData.color.r, ledData.color.g, ledData.color.b),
            complementary(ledData.color.r, ledData.color.g, ledData.color.b));
        FastLEDshowESP32();
      }
      break;
    case WAVE_FULL:
      if (millisTimer(bpm_to_ms(ledData.bpm) / ANIMATION_STEPS))
      {
        static int step = 0;
        step = (step + 1) % ANIMATION_STEPS;
        wave_full(
            step,
            CRGB(ledData.color.r, ledData.color.g, ledData.color.b),
            complementary(ledData.color.r, ledData.color.g, ledData.color.b));
        FastLEDshowESP32();
      }
      break;
    case STROBE_SPARKLING:
      if (millisTimer(bpm_to_ms(ledData.bpm) / ANIMATION_STEPS))
      {
        static int step = 0;
        step = (step + 1) % ANIMATION_STEPS;
        strobe_sparkling(
            step,
            CRGB(ledData.color.r, ledData.color.g, ledData.color.b));
        FastLEDshowESP32();
      }
      break;
    case PULSE:
      if (millisTimer(bpm_to_ms(ledData.bpm) / PULSE_STEPS))
      {
        uint8_t pulse_brightness = sin8(millis() / 1000.0 * ledData.bpm);
        uint8_t pulseR = scale8(ledData.color.r, pulse_brightness);
        uint8_t pulseG = scale8(ledData.color.g, pulse_brightness);
        uint8_t pulseB = scale8(ledData.color.b, pulse_brightness);
        fill_solid(leds, NUM_LEDS, CRGB(pulseR, pulseG, pulseB));
        FastLEDshowESP32();
      }
      break;

    case SLIDERAIN:
      if (millisTimer(bpm_to_ms(ledData.bpm) / NB_LIGNE))
      {
        static int step = 0;
        step = (step + 1) % NB_LIGNE;
        slide_rain(
            step,
            CRGB(ledData.color.r, ledData.color.g, ledData.color.b));
      }
      break;

    case SLIDELINE:
      if (millisTimer(bpm_to_ms(ledData.bpm) / NB_LIGNE))
      {
        static int step = 0;
        step = (step + 1) % NB_LIGNE;
        slideline(
            step,
            CRGB(ledData.color.r, ledData.color.g, ledData.color.b));
      }
      break;
    default:
      break;
  } 
}

bool bpmTimer(float bpm)
{
  static unsigned long previousMillisBpm = 0;
  unsigned long currentMillisBpm = millis();

  if (currentMillisBpm - previousMillisBpm >= 60000 / bpm)
  {
    previousMillisBpm = currentMillisBpm;
    return 1;
  }
  return 0;
}
bool millisTimer(int durationMs)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= durationMs)
  {
    previousMillis = currentMillis;
    return 1;
  }
  return 0;
}

void static_animation()
{
  // update if rgb value changed
  if (ledData.color.r != leds[0].r || ledData.color.g != leds[0].g || ledData.color.b != leds[0].b)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(ledData.color.r, ledData.color.g, ledData.color.b);
      FastLED.setBrightness(ledData.brightness);
      // TODO:Verifier que ça fonctionne
    }
    FastLEDshowESP32();
  }
}

void fadeOutBPM(uint16_t bpm)
{
  uint16_t fadeDuration = 60000 / bpm; // Calculate fade duration in milliseconds
  fadeDuration = fadeDuration / 8;

  fadeToBlackBy(leds, NUM_LEDS, 1);
  delay(fadeDuration / 256);
}