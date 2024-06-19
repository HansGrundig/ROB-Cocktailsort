#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12
#define NUM_COLORS 6
int i = 0;
CRGB leds[NUM_LEDS];
CRGB colors[] = {
    CRGB::Black,
    CRGB::Purple,
    CRGB::Blue,
    CRGB::Green,
    CRGB::Yellow,
    CRGB::Red};
int sort[NUM_LEDS];

void led_colorval(int *array, CRGB *colors)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = colors[sort[i]];
  }
}

void cocktailShakerSort(int *list, int length)
{
  int j = 0;
  int swapped = 0;
  do
  {
    for (int i = 0; i < length; i++)
    {
      if (list[i] > list[i + 1]) // Elements in wrong order?
      {                          // from left to right
        // Swap!
        int temp = list[i];
        list[i] = list[i + 1];
        list[i + 1] = temp;
        swapped = 1;
        delay(250);
        led_colorval(list, colors);
        FastLED.show();
      }
    }
    if (!swapped)
      return;
    for (int i = length; i > 0; i--)
    { // from right to left
      if (list[i] < list[i - 1])
      {
        int temp = list[i];
        list[i] = list[i - 1];
        list[i - 1] = temp;
        swapped = 1;
        delay(500);
        led_colorval(list, colors);
        FastLED.show();
      }
    }
  } while (swapped == 1);
  return;
}

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    sort[i] = rand() % (NUM_COLORS - 1) + 1;
  }
  led_colorval(sort, colors);
  FastLED.show();
  delay(1500);

  cocktailShakerSort(sort, NUM_LEDS);

  delay(2000);
}