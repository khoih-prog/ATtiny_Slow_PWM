/****************************************************************************************************************************
  ISR_Modify_PWM.ino
  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_Slow_PWM
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one AVRDx-based timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.
*****************************************************************************************************************************/

// Important Note: To use drag-and-drop into CURIOSITY virtual drive if you can program via Arduino IDE
// For example, check https://ww1.microchip.com/downloads/en/DeviceDoc/40002193A.pdf

#if !( defined(MEGATINYCORE) )
  #error This is designed only for MEGATINYCORE megaAVR board! Please check your Tools->Board setting
#endif

// These define's must be placed at the beginning before #include "ATtiny_Slow_PWM.h"
// _PWM_LOGLEVEL_ from 0 to 4
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_      4

// Be careful when using MAX_NUMBER_CHANNELS > 16. Max pemissible MAX_NUMBER_CHANNELS is 64
#define MAX_NUMBER_CHANNELS        16

// Select USING_FULL_CLOCK      == true for  20/16MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_HALF_CLOCK      == true for  10/ 8MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_250KHZ          == true for 250KHz to Timer TCBx => longer timer,  but worse  accuracy
// Not select for default 250KHz to Timer TCBx => longer timer,  but worse accuracy
#define USING_FULL_CLOCK      true
#define USING_HALF_CLOCK      false
#define USING_250KHZ          false         // Not supported now

// Try to use RTC, TCA0 or TCD0 for millis()
#define USE_TIMER_0           true          // Check if used by millis(), Servo or tone()
#define USE_TIMER_1           false         // Check if used by millis(), Servo or tone()

#if USE_TIMER_0
  #define CurrentTimer   ITimer0
#elif USE_TIMER_1
  #define CurrentTimer   ITimer1
#else
  #error You must select one Timer
#endif

#define USING_MICROS_RESOLUTION       true  //false 

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "ATtiny_Slow_PWM.h"

#define LED_OFF             HIGH
#define LED_ON              LOW

#ifdef LED_BUILTIN
  #undef LED_BUILTIN

  // To modify according to your board
  // For Curiosity Nano ATtiny3217 => PIN_PA3
  #if defined(ARDUINO_AVR_CuriosityNano3217)
    #define LED_BUILTIN   PIN_PA3
  #else
    // standard Arduino pin 13
    #define LED_BUILTIN   PIN_PA3
  #endif
#endif

#define USING_HW_TIMER_INTERVAL_MS        false   //true

// Don't change these numbers to make higher Timer freq. System can hang
#define HW_TIMER_INTERVAL_MS        0.0333f
#define HW_TIMER_INTERVAL_FREQ      30000L

volatile uint32_t startMicros = 0;

// Init AT_TINY_SLOW_PWM, each can service max 64 different ISR-based PWM channels
AT_TINY_SLOW_PWM_ISR ISR_PWM;

//////////////////////////////////////////////////////

void TimerHandler()
{
  ISR_PWM.run();
}

//////////////////////////////////////////////////////

#define USING_PWM_FREQUENCY     false //true

//////////////////////////////////////////////////////

// You can assign pins here. Be carefull to select good pin to use or crash
uint32_t PWM_Pin    = LED_BUILTIN;

// You can assign any interval for any timer here, in Hz
float PWM_Freq1   = 2.0f;   //200.0f;
// You can assign any interval for any timer here, in Hz
float PWM_Freq2   = 1.0f;   //100.0f;

// You can assign any interval for any timer here, in microseconds
uint32_t PWM_Period1 = 1000000 / PWM_Freq1;
// You can assign any interval for any timer here, in microseconds
uint32_t PWM_Period2 = 1000000 / PWM_Freq2;

// You can assign any duty_cycle for any PWM here, from 0-100
float PWM_DutyCycle1  = 10.0f;     //50.0f;
// You can assign any duty_cycle for any PWM here, from 0-100
float PWM_DutyCycle2  = 5.55f;    //90.0f;

// Channel number used to identify associated channel
int channelNum;

////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print(F("\nStarting ISR_Modify_PWM on "));
  Serial.println(BOARD_NAME);
  Serial.println(AT_TINY_SLOW_PWM_VERSION);
  Serial.print(F("CPU Frequency = "));
  Serial.print(F_CPU / 1000000);
  Serial.println(F(" MHz"));
  Serial.print(F("Max number PWM channels = "));
  Serial.println(MAX_NUMBER_CHANNELS);

  Serial.print(F("TCB Clock Frequency = "));

#if USING_FULL_CLOCK
  Serial.println(F("Full clock (20/16MHz, etc) for highest accuracy"));
#elif USING_HALF_CLOCK
  Serial.println(F("Half clock (10/8MHz, etc.) for high accuracy"));
#else
  Serial.println(F("250KHz for lower accuracy but longer time"));
#endif

#if USING_HW_TIMER_INTERVAL_MS

  CurrentTimer.init();

  if (CurrentTimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS, TimerHandler))
  {
    Serial.print(F("Starting ITimer OK, micros() = "));
    Serial.println(micros());
  }
  else
    Serial.println(F("Can't set ITimer. Select another freq. or timer"));

#else

  CurrentTimer.init();

  if (CurrentTimer.attachInterrupt(HW_TIMER_INTERVAL_FREQ, TimerHandler))
  {
    Serial.print(F("Starting ITimer OK, micros() = "));
    Serial.println(micros());
  }
  else
    Serial.println(F("Can't set ITimer. Select another freq. or timer"));

#endif    // USING_HW_TIMER_INTERVAL_MS

  Serial.print(F("Using PWM Freq = "));
  Serial.print(PWM_Freq1);
  Serial.print(F(", PWM DutyCycle = "));
  Serial.println(PWM_DutyCycle1);

#if USING_PWM_FREQUENCY

  // You can use this with PWM_Freq in Hz
  ISR_PWM.setPWM(PWM_Pin, PWM_Freq1, PWM_DutyCycle1);

#else
#if USING_MICROS_RESOLUTION
  // Or using period in microsecs resolution
  channelNum = ISR_PWM.setPWM_Period(PWM_Pin, PWM_Period1, PWM_DutyCycle1);
#else
  // Or using period in millisecs resolution
  channelNum = ISR_PWM.setPWM_Period(PWM_Pin, PWM_Period1 / 1000, PWM_DutyCycle1);
#endif
#endif
}

////////////////////////////////////////////////

void changePWM()
{
  static uint8_t count = 1;

  float PWM_Freq;
  float PWM_DutyCycle;

  if (count++ % 2)
  {
    PWM_Freq        = PWM_Freq2;
    PWM_DutyCycle   = PWM_DutyCycle2;
  }
  else
  {
    PWM_Freq        = PWM_Freq1;
    PWM_DutyCycle   = PWM_DutyCycle1;
  }

  // You can use this with PWM_Freq in Hz
  if (ISR_PWM.modifyPWMChannel(channelNum, PWM_Pin, PWM_Freq, PWM_DutyCycle))
  {
    Serial.print(F("Modify Freq => "));
    Serial.print(PWM_Freq);
    Serial.print(F(", DC => "));
    Serial.println(PWM_DutyCycle);
  }
  else
  {
    Serial.println(F("changePWM error for PWM_Period"));
  }
}

////////////////////////////////////////////////

void changingPWM()
{
  static unsigned long changingPWM_timeout = 0;

  static unsigned long current_millis;

#define CHANGING_PWM_INTERVAL    10000L

  current_millis = millis();

  // changePWM every CHANGING_PWM_INTERVAL (10) seconds.
  if ( (current_millis > changingPWM_timeout) )
  {
    if (changingPWM_timeout > 0)
      changePWM();

    changingPWM_timeout = current_millis + CHANGING_PWM_INTERVAL;
  }
}

////////////////////////////////////////////////

void loop()
{
  changingPWM();
}
