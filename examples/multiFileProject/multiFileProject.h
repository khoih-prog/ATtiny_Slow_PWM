/****************************************************************************************************************************
  multiFileProject.h

  For Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using megaTinyCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/ATtiny_Slow_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

// Be careful when using MAX_NUMBER_CHANNELS > 16. Max pemissible MAX_NUMBER_CHANNELS is 64
#define MAX_NUMBER_CHANNELS        16

#define USING_MICROS_RESOLUTION       true    //false 

// Default is true, uncomment to false
//#define CHANGING_PWM_END_OF_CYCLE     false

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "ATtiny_Slow_PWM.hpp"
