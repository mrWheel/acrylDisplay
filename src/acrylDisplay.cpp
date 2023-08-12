/*
**  software by Michael Teeuw
*/

#define SW_VERSION "1.0.0 [10-08-2023]"

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>
#include <elapsedMillis.h>

//-- make sure to set pixelCount to the number of pixels in your strip
const uint16_t pixelCount = 100;  
//-- make sure to set pixelPin to the correct pin
const uint8_t  pixelPin   = 2;    

elapsedMillis updateTimer, blinkLedTimer;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(pixelCount, pixelPin);

uint8_t   wheel         = 0;
uint8_t   offsetPerLed  = 5;
uint16_t  speed         = 75;


//-----------------------------------------------------------------------
RgbColor generateColor(uint8_t wheelPos) 
{
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) 
  {
    return RgbColor(255 - wheelPos * 3, 0, wheelPos * 3);
  } 
  else if(wheelPos < 170) 
  {
    wheelPos -= 85;
    return RgbColor(0, wheelPos * 3, 255 - wheelPos * 3);
  } 
  else 
  {
    wheelPos -= 170;
    return RgbColor(wheelPos * 3, 255 - wheelPos * 3, 0);
  }

} //  generateColor()


//-----------------------------------------------------------------------
void updateColor() 
{
  for (uint16_t pixel = 0; pixel < pixelCount; pixel++) 
  {
    strip.SetPixelColor(pixel, generateColor(wheel + offsetPerLed * pixel));
  }
  strip.Show();
  wheel++;

} //  updateColor()

//=======================================================================
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  strip.Begin();
  strip.Show();    

} //  setup()


//=======================================================================
void loop()
{
  if (updateTimer > speed) 
  {
    updateColor();
    updateTimer = 0;
  }
  if (blinkLedTimer > 1500) 
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    blinkLedTimer = 0;
  }

} //  loop()
