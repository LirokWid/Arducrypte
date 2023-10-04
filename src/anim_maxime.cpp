#include "anim_maxime.h"


void wave(int step, CRGB color1, CRGB color2)
{
  float num_led = 10.8;
  int offset = 0;
  turn_off();
  if(step<10)
  {
    fill_line(0, (int)(num_led*step), (int)num_led, color1, true);
    fill_line(1, (int)(num_led*step), (int)num_led, color2, false);
    fill_line(2, (int)(num_led*step), (int)num_led, color2, false);
    fill_line(3, (int)(num_led*step), (int)num_led, color1, true);
  }
  else if(10 <= step <20)
    {
    fill_line(0, (int)(num_led*(step-10)), (int)num_led, color2, false);
    fill_line(1, (int)(num_led*(step-10)), (int)num_led, color1, true);
    fill_line(2, (int)(num_led*(step-10)), (int)num_led, color1, true);
    fill_line(3, (int)(num_led*(step-10)), (int)num_led, color2, false);
  }
}

void wave_full(int step, CRGB color1, CRGB color2)
{
  float num_led = 11;
  int offset = 0;
  if(step==0) turn_off();
  if(step<9)
  {
    fill_line(0, (int)(num_led*step), (int)num_led, color1, true);
    fill_line(1, (int)(num_led*step), (int)num_led, color2, true);
    fill_line(2, (int)(num_led*step), (int)num_led, color2, true);
    fill_line(3, (int)(num_led*step), (int)num_led, color1, true);
  }
  else if(step==9)
  {
    fill_line(0, (int)(num_led*step), 9, color1, true);
    fill_line(1, (int)(num_led*step), 9, color2, true);
    fill_line(2, (int)(num_led*step), 9, color2, true);
    fill_line(3, (int)(num_led*step), 9, color1, true);
  }
  /*
  else if(step==10)
    {
    fill_line(0, (int)(num_led*(step)-9), 9, CRGB::Black, false);
    fill_line(1, (int)(num_led*(step)-9), 9, CRGB::Black, false);
    fill_line(2, (int)(num_led*(step)-9), 9, CRGB::Black, false);
    fill_line(3, (int)(num_led*(step)-9), 9, CRGB::Black, false);
  }
  */
  else if(10 < step <=19)
    {
    fill_line(0, (int)(num_led*(step-num_led)), (int)num_led, CRGB::Black, false);
    fill_line(1, (int)(num_led*(step-num_led)), (int)num_led, CRGB::Black, false);
    fill_line(2, (int)(num_led*(step-num_led)), (int)num_led, CRGB::Black, false);
    fill_line(3, (int)(num_led*(step-num_led)), (int)num_led, CRGB::Black, false);
  }
}

void strobe_sparkling(int qte, CRGB color)
{
  turn_off();
  int rand_point = random(qte,(36-qte));
  for(int bar = 0; bar < 12; bar++)
  {
    fill_block((rand_point+(36*bar)-qte), qte, color);
  }
}