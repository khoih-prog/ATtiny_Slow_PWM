/****************************************************************************************************************************
  multiFileProject.ino

  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_Slow_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

// Important Note: To use drag-and-drop into CURIOSITY virtual drive if you can program via Arduino IDE
// For example, check https://ww1.microchip.com/downloads/en/DeviceDoc/40002193A.pdf

#if !( defined(MEGATINYCORE) )
  #error This is designed only for MEGATINYCORE megaAVR board! Please check your Tools->Board setting
#endif

#define AT_TINY_SLOW_PWM_VERSION_MIN_TARGET      F("ATtiny_Slow_PWM v1.0.0")
#define AT_TINY_SLOW_PWM_VERSION_MIN             1000000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "ATtiny_Slow_PWM.h"

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print(F("\nStarting multiFileProject on "));
  Serial.println(BOARD_NAME);
  Serial.println(AT_TINY_SLOW_PWM_VERSION);

#if defined(AT_TINY_SLOW_PWM_VERSION_MIN)

  if (AT_TINY_SLOW_PWM_VERSION_INT < AT_TINY_SLOW_PWM_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(AT_TINY_SLOW_PWM_VERSION_MIN_TARGET);
  }

#endif
}

void loop()
{
  // put your main code here, to run repeatedly:
}
