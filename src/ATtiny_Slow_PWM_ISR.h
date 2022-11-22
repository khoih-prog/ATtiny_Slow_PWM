/****************************************************************************************************************************
  ATtiny_Slow_PWM_ISR.h
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

#ifndef AT_TINY_SLOW_PWM_ISR_H
#define AT_TINY_SLOW_PWM_ISR_H

#include "ATtiny_Slow_PWM_ISR.hpp"
#include "ATtiny_Slow_PWM_ISR_Impl.h"

#endif    // AT_TINY_SLOW_PWM_ISR_H


