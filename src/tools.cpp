#include "tools.h"


extern CRGB leds[NUM_LEDS];



CRGB complementary(int r,int g,int b) {
    return CRGB(255-r,255-g,255-b);
}


void fill_block(int from, int qte, CRGB color)
{
  fill_solid(&leds[from], qte, color);
}

void fill_bar(int bar,CRGB color)
{
  fill_solid(&leds[bar*36], 36, color);
}

void fill_line(int line, int from, int qte, CRGB color, bool inv)
{
  if(inv)
  {
    if((line == 0) || (line == 2)) fill_block(from + STICK_LED_NB*STICK_PER_LINE*line, qte, color);
    else fill_block(STICK_LED_NB*STICK_PER_LINE*(line+1)-qte-from, qte, color);
  }
  else if(!inv)
  {
    if((line == 1) || (line == 3)) fill_block(from + STICK_LED_NB*STICK_PER_LINE*line, qte, color);
    else fill_block(STICK_LED_NB*STICK_PER_LINE*(line+1)-qte-from, qte, color);
  }
}

float hertz_to_ms(float hz)
{
  return 1000/hz;
}


int bpm_to_ms(float bpm)
{
  return (int)(1000/(bpm/60));
}


float bpm_to_hz(float bpm)
{
  return bpm/60;
}

float hz_to_bpm(float hz)
{
  return hz*60;
}

float hz_to_ms(float hz)
{
  return 1000/hz;
}

void change_range_color(int start_led,int last_led,CRGB color)
{
  for(int i = start_led;i<last_led;i++)
  {
      leds[i]=color;
  }
    FastLED.show();
}

void change_stick_color(int stick_number,CRGB color)
{
  int start_led,stop_led;
  start_led = stick_number*STICK_LED_NB;
  stop_led = start_led + STICK_LED_NB;

  for (int i = start_led; i<stop_led; i++)
  {
    leds[i] = color;
  }
  FastLED.show();  
}

void turn_off()
{
    for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black; // Éteint toutes les LED
  }
  FastLED.show();
}

void turn_on(CRGB color)
{
    for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }
  FastLED.show();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

int random_stick_no_repeat()


{
  static int last_random_stick;
  int random_stick = random(0,STICK_NB);
  while(last_random_stick == random_stick)
  {
    Serial.println("ssame stick avoided");
    random_stick = random(0,STICK_NB);
  }
  last_random_stick = random_stick;
  return random_stick;
}
