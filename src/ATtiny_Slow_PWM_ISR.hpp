/****************************************************************************************************************************
  ATtiny_Slow_PWM_ISR.hpp
  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_Slow_PWM
  Licensed under MIT license
  
  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one AVRDx-based timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      27/08/2022 Initial coding to support AVR ATtiny (ATtiny3217, etc.) using megaTinyCore
*****************************************************************************************************************************/

#pragma once

#ifndef AT_TINY_SLOW_PWM_ISR_HPP
#define AT_TINY_SLOW_PWM_ISR_HPP

#if defined(MEGATINYCORE)

  #define TIMER_INTERRUPT_USING_MEGATINYCORE        true
  
  #if !defined(BOARD_NAME)
  
    ////////////////////////// Curiosity Nano //////////////////////////
  
    #if ( defined(ARDUINO_AVR_CuriosityNano3217) )
      #define BOARD_NAME      F("AVR_CuriosityNano3217" )    
    #elif ( defined(ARDUINO_AVR_CuriosityNano1627) )
      #define BOARD_NAME      F("AVR_CuriosityNano1627")
    #elif ( defined(ARDUINO_AVR_CuriosityNano1607) )
      #define BOARD_NAME      F("AVR_CuriosityNano1607")
    #elif ( defined(ARDUINO_AVR_Xplained_Pro_3217) )
      #define BOARD_NAME      F("AVR_Xplained_Pro_3217")
    #elif ( defined(ARDUINO_AVR_Xplained_Pro_817) )
      #define BOARD_NAME      F("AVR_Xplained_Pro_817" )    
    #elif ( defined(ARDUINO_AVR_XplainedMini817) )
      #define BOARD_NAME      F("AVR_XplainedMini817")
    #elif ( defined(ARDUINO_AVR_XplainedNano416) )
      #define BOARD_NAME      F("AVR_XplainedNano416")
  
    ////////////////////////// tinyAVR 0/1 series (atxy7) //////////////////////////
  
    #elif ( defined(ARDUINO_AVR_ATtiny3217) )
      #define BOARD_NAME      F("AVR_ATtiny3217" )    
    #elif ( defined(ARDUINO_AVR_ATtiny1617) )
      #define BOARD_NAME      F("AVR_ATtiny1617")
    #elif ( defined(ARDUINO_AVR_ATtiny817) )
      #define BOARD_NAME      F("AVR_ATtiny817")
    #elif ( defined(ARDUINO_AVR_ATtiny417) )
      #define BOARD_NAME      F("AVR_ATtiny417")
    #elif ( defined(ARDUINO_AVR_ATtiny3227) )
      #define BOARD_NAME      F("AVR_ATtiny3227" )    
    #elif ( defined(ARDUINO_AVR_ATtiny1627) )
      #define BOARD_NAME      F("AVR_ATtiny1627")
    #elif ( defined(ARDUINO_AVR_ATtiny827) )
      #define BOARD_NAME      F("AVR_ATtiny827")
    #elif ( defined(ARDUINO_AVR_ATtiny427) )
      #define BOARD_NAME      F("AVR_ATtiny427")  
    #elif ( defined(ARDUINO_AVR_ATtiny1607) )
      #define BOARD_NAME      F("AVR_ATtiny1607")
    #elif ( defined(ARDUINO_AVR_ATtiny807) )
      #define BOARD_NAME      F("AVR_ATtiny807")  
             
    ////////////////////////// tinyAVR 0/1 series (atxy6) //////////////////////////
  
    #elif ( defined(ARDUINO_AVR_ATtiny3216) )
      #define BOARD_NAME      F("AVR_ATtiny3216" )    
    #elif ( defined(ARDUINO_AVR_ATtiny1616) )
      #define BOARD_NAME      F("AVR_ATtiny1616")
    #elif ( defined(ARDUINO_AVR_ATtiny816) )
      #define BOARD_NAME      F("AVR_ATtiny816")
    #elif ( defined(ARDUINO_AVR_ATtiny416) )
      #define BOARD_NAME      F("AVR_ATtiny416")
    #elif ( defined(ARDUINO_AVR_ATtiny3226) )
      #define BOARD_NAME      F("AVR_ATtiny3226" )    
    #elif ( defined(ARDUINO_AVR_ATtiny1626) )
      #define BOARD_NAME      F("AVR_ATtiny1626")
    #elif ( defined(ARDUINO_AVR_ATtiny826) )
      #define BOARD_NAME      F("AVR_ATtiny826")
    #elif ( defined(ARDUINO_AVR_ATtiny426) )
      #define BOARD_NAME      F("AVR_ATtiny426")  
    #elif ( defined(ARDUINO_AVR_ATtiny1606) )
      #define BOARD_NAME      F("AVR_ATtiny1606")
    #elif ( defined(ARDUINO_AVR_ATtiny806) )
      #define BOARD_NAME      F("AVR_ATtiny806")  
    #elif ( defined(ARDUINO_AVR_ATtiny406) )
      #define BOARD_NAME      F("AVR_ATtiny406")  
    
    
    ////////////////////////// tinyAVR 0/1 series (atxy4) //////////////////////////
     
    #elif ( defined(ARDUINO_AVR_ATtiny1614) )
      #define BOARD_NAME      F("AVR_ATtiny1614")
    #elif ( defined(ARDUINO_AVR_ATtiny814) )
      #define BOARD_NAME      F("AVR_ATtiny814")
    #elif ( defined(ARDUINO_AVR_ATtiny414) )
      #define BOARD_NAME      F("AVR_ATtiny414")
    #elif ( defined(ARDUINO_AVR_ATtiny214) )
      #define BOARD_NAME      F("AVR_ATtiny214")  
    #elif ( defined(ARDUINO_AVR_ATtiny3224) )
      #define BOARD_NAME      F("AVR_ATtiny3224" )    
    #elif ( defined(ARDUINO_AVR_ATtiny1624) )
      #define BOARD_NAME      F("AVR_ATtiny1624")
    #elif ( defined(ARDUINO_AVR_ATtiny824) )
      #define BOARD_NAME      F("AVR_ATtiny824")
    #elif ( defined(ARDUINO_AVR_ATtiny424) )
      #define BOARD_NAME      F("AVR_ATtiny424")  
    #elif ( defined(ARDUINO_AVR_ATtiny1604) )
      #define BOARD_NAME      F("AVR_ATtiny1604")
    #elif ( defined(ARDUINO_AVR_ATtiny804) )
      #define BOARD_NAME      F("AVR_ATtiny804")  
    #elif ( defined(ARDUINO_AVR_ATtiny404) )
      #define BOARD_NAME      F("AVR_ATtiny404")
    #elif ( defined(ARDUINO_AVR_ATtiny204) )
      #define BOARD_NAME      F("AVR_ATtiny204")
      
    ////////////////////////// tinyAVR 0/1 series (atxy2) //////////////////////////
     
    #elif ( defined(ARDUINO_AVR_ATtiny412) )
      #define BOARD_NAME      F("AVR_ATtiny412")
    #elif ( defined(ARDUINO_AVR_ATtiny212) )
      #define BOARD_NAME      F("AVR_ATtiny212"
    #elif ( defined(ARDUINO_AVR_ATtiny402) )
      #define BOARD_NAME      F("AVR_ATtiny402")
    #elif ( defined(ARDUINO_AVR_ATtiny202) )
      #define BOARD_NAME      F("AVR_ATtiny202")    
     
    ////////////////////////////////////////////////////////////////

    #endif
    
  #endif  // #if !defined(BOARD_NAME)
            
#else
 
  #error This is designed only for AVR_ATtiny boards using megaTinyCore

#endif

///////////////////////////////////////////////////////////////////////////////

#ifndef AT_TINY_SLOW_PWM_VERSION
  #define AT_TINY_SLOW_PWM_VERSION           F("ATtiny_Slow_PWM v1.0.0")
  
  #define AT_TINY_SLOW_PWM_VERSION_MAJOR     1
  #define AT_TINY_SLOW_PWM_VERSION_MINOR     0
  #define AT_TINY_SLOW_PWM_VERSION_PATCH     0

  #define AT_TINY_SLOW_PWM_VERSION_INT       1000000
#endif

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_        0
#endif

#include "PWM_Generic_Debug.h"

#include <stddef.h>

#include <inttypes.h>

#if defined(ARDUINO)
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
#endif

#define AT_TINY_SLOW_PWM_ISR  ATtiny_Slow_PWM

typedef void (*timer_callback)();
typedef void (*timer_callback_p)(void *);

#if !defined(USING_MICROS_RESOLUTION)

  #if (_PWM_LOGLEVEL_ > 3)
    #warning Not USING_MICROS_RESOLUTION, using millis resolution
  #endif
    
  #define USING_MICROS_RESOLUTION       false
#endif

#if !defined(CHANGING_PWM_END_OF_CYCLE)
  #if (_PWM_LOGLEVEL_ > 3)
    #warning Using default CHANGING_PWM_END_OF_CYCLE == true
  #endif
  
  #define CHANGING_PWM_END_OF_CYCLE     true
#endif

#define INVALID_AT_TINY_PIN         255

#if !defined(MAX_NUMBER_CHANNELS)
  // maximum number of PWM channels
  #define MAX_NUMBER_CHANNELS        16
#else
  #if (MAX_NUMBER_CHANNELS > 64)
    #undef MAX_NUMBER_CHANNELS
    #define MAX_NUMBER_CHANNELS        64
    
    #warning Reset too big MAX_NUMBER_CHANNELS to 64
  #endif
#endif  

//////////////////////////////////////////////////////////////////

class AT_TINY_SLOW_PWM_ISR 
{

  public:  

    // constructor
    AT_TINY_SLOW_PWM_ISR();

    void init();

    // this function must be called inside loop()
    void run();
    
    //////////////////////////////////////////////////////////////////
    // PWM
    // Return the channelNum if OK, -1 if error
    int setPWM(const uint32_t& pin, const float& frequency, const float& dutycycle, timer_callback StartCallback = nullptr, 
                timer_callback StopCallback = nullptr)
    {
      uint32_t period = 0;
      
      if ( ( frequency >= 0.0 ) && ( frequency <= 1000.0 ) )
      {
#if USING_MICROS_RESOLUTION
        // period in us
        period = (uint32_t) (1000000.0f / frequency);
#else    
        // period in ms
        period = (uint32_t) (1000.0f / frequency);
#endif
        PWM_LOGDEBUG1(F("Frequency = "), frequency);
      
      }
      else
      {       
        PWM_LOGERROR("Error: Invalid frequency, max is 1000Hz");
        
        return -1;
      }
      
      return setupPWMChannel(pin, period, dutycycle, (void *) StartCallback, (void *) StopCallback);   
    }

    // period in us
    // Return the channelNum if OK, -1 if error
    int setPWM_Period(const uint32_t& pin, const uint32_t& period, const float& dutycycle, 
                      timer_callback StartCallback = nullptr, timer_callback StopCallback = nullptr)  
    {     
      return setupPWMChannel(pin, period, dutycycle, (void *) StartCallback, (void *) StopCallback);      
    } 
    
    //////////////////////////////////////////////////////////////////
    
    // low level function to modify a PWM channel
    // returns the true on success or false on failure
    bool modifyPWMChannel(const uint8_t& channelNum, const uint32_t& pin, const float& frequency, const float& dutycycle)
    {
      uint32_t period = 0;
      
      if ( ( frequency >= 0.0 ) && ( frequency <= 1000.0 ) )
      {
#if USING_MICROS_RESOLUTION
        // period in us
        period = (uint32_t) (1000000.0f / frequency);
#else    
        // period in ms
        period = (uint32_t) (1000.0f / frequency);
#endif
        
        PWM_LOGDEBUG1(F("Frequency = "), frequency);
      }
      else
      {       
        PWM_LOGERROR("Error: Invalid frequency, max is 1000Hz");
        return false;
      }
      
      return modifyPWMChannel_Period(channelNum, pin, period, dutycycle);
    }
    
    //////////////////////////////////////////////////////////////////
    
    //period in us
    bool modifyPWMChannel_Period(const uint8_t& channelNum, const uint32_t& pin, const uint32_t& period, const float& dutycycle);
    
    //////////////////////////////////////////////////////////////////

    // destroy the specified PWM channel
    void deleteChannel(const uint8_t& channelNum);

    // restart the specified PWM channel
    void restartChannel(const uint8_t& channelNum);

    // returns true if the specified PWM channel is enabled
    bool isEnabled(const uint8_t& channelNum);

    // enables the specified PWM channel
    void enable(const uint8_t& channelNum);

    // disables the specified PWM channel
    void disable(const uint8_t& channelNum);

    // enables all PWM channels
    void enableAll();

    // disables all PWM channels
    void disableAll();

    // enables the specified PWM channel if it's currently disabled, and vice-versa
    void toggle(const uint8_t& channelNum);

    // returns the number of used PWM channels
    int8_t getnumChannels();

    // returns the number of available PWM channels
    uint8_t getNumAvailablePWMChannels() 
    {
      if (numChannels <= 0)
        return MAX_NUMBER_CHANNELS;
      else 
        return MAX_NUMBER_CHANNELS - numChannels;
    };

  private:

    // low level function to initialize and enable a new PWM channel
    // returns the PWM channel number (channelNum) on success or
    // -1 on failure (f == NULL) or no free PWM channels 
    int setupPWMChannel(const uint32_t& pin, const uint32_t& period, const float& dutycycle, void* cbStartFunc = nullptr, void* cbStopFunc = nullptr);

    // find the first available slot
    int findFirstFreeSlot();

    typedef struct 
    {
      ///////////////////////////////////
      
      
      ///////////////////////////////////
      
      uint32_t      prevTime;           // value returned by the micros() or millis() function in the previous run() call
      uint32_t      period;             // period value, in us / ms
      uint32_t      onTime;             // onTime value, ( period * dutyCycle / 100 ) us  / ms
      
      void*         callbackStart;      // pointer to the callback function when PWM pulse starts (HIGH)
      void*         callbackStop;       // pointer to the callback function when PWM pulse stops (LOW)
      
      ////////////////////////////////////////////////////////////
      
      uint32_t      pin;                // PWM pin
      bool          pinHigh;            // true if PWM pin is HIGH
      ////////////////////////////////////////////////////////////
      
      bool          enabled;            // true if enabled
      
      // New from v1.2.0     
      uint32_t      newPeriod;          // period value, in us / ms
      uint32_t      newOnTime;          // onTime value, ( period * dutyCycle / 100 ) us  / ms
      float         newDutyCycle;       // from 0.00 to 100.00, float precision
    } PWM_t;

    volatile PWM_t PWM[MAX_NUMBER_CHANNELS];

    // actual number of PWM channels in use (-1 means uninitialized)
    volatile int8_t numChannels;
};

#endif    // AT_TINY_SLOW_PWM_ISR_HPP


