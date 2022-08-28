# ATtiny_Slow_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/ATtiny_Slow_PWM.svg?)](https://www.ardu-badge.com/ATtiny_Slow_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ATtiny_Slow_PWM.svg)](https://github.com/khoih-prog/ATtiny_Slow_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ATtiny_Slow_PWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ATtiny_Slow_PWM.svg)](http://github.com/khoih-prog/ATtiny_Slow_PWM/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Important Note for Arduino IDE](#Important-Note-for-Arduino-IDE)
* [Why do we need this ATtiny_Slow_PWM library](#why-do-we-need-this-ATtiny_Slow_PWM-library)
  * [Features](#features)
  * [Why using ISR-based PWM is better](#why-using-isr-based-pwm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [More useful Information](#more-useful-information)
  * [1. Documents](#1-documents)
  * [2. Timer TCB0-TCB4](#2-timer-tcb0-tcb4)
* [Usage](#usage)
  * [1. Init Hardware Timer](#1-init-hardware-timer)
  * [2. Set PWM Frequency, dutycycle, attach irqCallbackStartFunc and irqCallbackStopFunc functions](#2-Set-PWM-Frequency-dutycycle-attach-irqCallbackStartFunc-and-irqCallbackStopFunc-functions)
* [Examples](#examples)
  * [ 1. ISR_8_PWMs_Array](examples/ISR_8_PWMs_Array)
  * [ 2. ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex)
  * [ 3. ISR_8_PWMs_Array_Simple](examples/ISR_8_PWMs_Array_Simple)
  * [ 4. ISR_Changing_PWM](examples/ISR_Changing_PWM)
  * [ 5. ISR_Modify_PWM](examples/ISR_Modify_PWM)
  * [ 6. multiFileProject](examples/multiFileProject). **New**
* [Example ISR_8_PWMs_Array_Complex](#Example-ISR_8_PWMs_Array_Complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_8_PWMs_Array_Complex on AVR_ATtiny3217](#1-ISR_8_PWMs_Array_Complex-on-AVR_ATtiny3217)
  * [2. ISR_8_PWMs_Array on AVR_ATtiny3217](#2-isr_8_pwms_array-on-AVR_ATtiny3217)
  * [3. ISR_8_PWMs_Array_Simple on AVR_ATtiny3217](#3-ISR_8_PWMs_Array_Simple-on-AVR_ATtiny3217)
  * [4. ISR_Modify_PWM on AVR_ATtiny3217](#4-ISR_Modify_PWM-on-AVR_ATtiny3217)
  * [5. ISR_Changing_PWM on AVR_ATtiny3217](#5-ISR_Changing_PWM-on-AVR_ATtiny3217)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Important Note for Arduino IDE

With some Arduino IDE versions, such as v1.8.19, upload directly via USB to some boards, such as `AVR_CuriosityNano3217` can't be done without `unknown-to-me` fix. We'll get the following error when uploading

```
avrdude: Version 6.3-20201216
         Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
         Copyright (c) 2007-2014 Joerg Wunsch

         System wide configuration file is "/home/kh/.arduino15/packages/megaTinyCore/hardware/megaavr/2.5.11/avrdude.conf"
         User configuration file is "/home/kh/.avrduderc"
         User configuration file does not exist or is not a regular file, skipping

         Using Port                    : usb
         Using Programmer              : curiosity_updi
avrdude: usbdev_open(): Found nEDBG CMSIS-DAP, serno: MCHP3333021800000998
avrdude: usbdev_open(): WARNING: failed to set configuration 1: Device or resource busy
avrdude: Found CMSIS-DAP compliant device, using EDBG protocol
avrdude: usbdev_send(): wrote -5 out of 912 bytes, err = Input/output error
avrdude: jtag3_edbg_prepare(): failed to send command to serial port

avrdude done.  Thank you.

the selected serial port 
 does not exist or your board is not connected
```

We can use drag-and-drop method to `drag-and-drop` the compiled **hex** file to `CURIOSITY` virtual drive. 

If `success`, The LED blinks **slowly** for 2 sec, or **rapidly** for 2 sec if `failure`


For example, to run [Change_Interval example](https://github.com/khoih-prog/ATtiny_Slow_PWM/tree/main/examples/Change_Interval), use Arduino IDE to compile, and get the `Change_Interval.ino.hex` file. For Ubuntu Linux, the file is stored in directory `/tmp/arduino_build_xxxxxx`


<p align="center">
    <img src="https://github.com/khoih-prog/ATtiny_Slow_PWM/blob/main/pics/Change_Interval.png">
</p>


After drag-and-drop the `Change_Interval.ino.hex` into `CURIOSITY` virtual drive, the code will run immediately if successfully loaded (LED blinks **slowly**)


<p align="center">
    <img src="https://github.com/khoih-prog/ATtiny_Slow_PWM/blob/main/pics/CURIOSITY_drive.png">
</p>


---
---

### Why do we need this [ATtiny_Slow_PWM library](https://github.com/khoih-prog/ATtiny_Slow_PWM)

### Features

This library enables you to use ISR-based PWM channels on Arduino AVR ATtiny-based boards (ATtiny3217, etc.) using [**megaTinyCore**](https://github.com/SpenceKonde/megaTinyCore), to create and output PWM any GPIO pin. Because this library doesn't use the powerful, high-speed, purely hardware-controlled PWM with **many limitations**, the maximum PWM frequency is currently limited at **1000Hz**, which is still suitable for many real-life applications, such as LED lighting, Servo, etc. Now you can change the PWM settings on-the-fly

---

This library enables you to use Interrupt from Hardware Timers on **AVR ATtiny-based boards** to create and output PWM to any pins. It now supports 64 ISR-based synchronized PWM channels, while consuming only 1 Hardware Timer. PWM interval can be very long (uint64_t microsecs / millisecs). The most important feature is they're `ISR-based PWM` channels. Therefore, their executions are not blocked by bad-behaving functions or tasks. This important feature is absolutely necessary for `mission-critical` tasks. These hardware PWM channels, using interrupt, still work even if other functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software PWM using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **64 ISR-based synchronized PWM channels, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **64 ISR-based PWM-channels**, the maximum interval is **practically unlimited** (limited only by `uint64_t` miliseconds) while **the accuracy is nearly perfect** compared to software PWM channels. 

The most important feature is they're `ISR-based PWM` channels. Therefore, their executions are **not blocked by bad-behaving functions / tasks**, such as connecting to WiFi, Internet or Blynk services. This important feature is absolutely necessary for mission-critical tasks. You can also have many `(up to 64)` PWM channels to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

The [**ISR_8_PWMs_Array_Complex**](examples/ISR_8_PWMs_Array_Complex) example will demonstrate the nearly perfect accuracy, compared to software PWM, by printing the actual period / duty-cycle in `microsecs` of each of PWM-channels.

You'll see `software-based` SimpleTimer is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---

#### Why using ISR-based PWM is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware PWM channels, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software PWM channels using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software PWM channels, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

- **tinyAVR boards using megaTinyCore**

##### Curiosity Nano ATtiny3217

<p align="center">
    <img src="https://github.com/khoih-prog/ATtiny_TimerInterrupt/blob/main/pics/Curiosity_ATtiny3217.png">
</p>


---


#### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as `volatile`.

---
---

## Prerequisites

1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
2. [`SpenceKonde megaTinyCore core 2.5.11+`](https://github.com/SpenceKonde/megaTinyCore) for Arduino ATtiny boards.  [![GitHub release](https://img.shields.io/github/release/SpenceKonde/megaTinyCore.svg)](https://github.com/SpenceKonde/megaTinyCore/releases/latest). Follow [**megaTinyCore Installation**](https://github.com/SpenceKonde/megaTinyCore/blob/master/Installation.md).
3. To use with certain example
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_8_PWMs_Array_Simple](examples/ISR_8_PWMs_Array_Simple) and [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex) examples.
   
   
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**ATtiny_Slow_PWM**](https://github.com/khoih-prog/ATtiny_Slow_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ATtiny_Slow_PWM.svg?)](https://www.ardu-badge.com/ATtiny_Slow_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**ATtiny_Slow_PWM**](https://github.com/khoih-prog/ATtiny_Slow_PWM) page.
2. Download the latest release `ATtiny_Slow_PWM-main.zip`.
3. Extract the zip file to `ATtiny_Slow_PWM-main` directory 
4. Copy whole `ATtiny_Slow_PWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ATtiny_Slow_PWM** library](https://registry.platformio.org/libraries/khoih-prog/ATtiny_Slow_PWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/ATtiny_Slow_PWM/installation). Search for **ATtiny_Slow_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "ATtiny_Slow_PWM.hpp"          //https://github.com/khoih-prog/ATtiny_Slow_PWM
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "ATtiny_Slow_PWM.h"            //https://github.com/khoih-prog/ATtiny_Slow_PWM
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)

---
---

## More useful Information

### 1. Documents

1. [Arduino 101: Timers and Interrupts](https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072)
2. [Getting Started with Timer/Counter Type B (TCB)](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ApplicationNotes/ApplicationNotes/TB3214-Getting-Started-with-TCB-DS90003214.pdf)
3. [megaTinyCore README.md](https://github.com/SpenceKonde/megaTinyCore/blob/master/README.md)
4. [ATtiny3217 Curiosity Nano Hardware User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/40002193A.pdf)
5. [AVR128DA48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DA48-Curiosity-Nano-UG-DS50002971B.pdf)
6. [AVR128DB48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DB48-Curiosity-Nano-HW-UserG-DS50003037A.pdf)


### 2. Timer TCB0-TCB1

TCB0-TCB1 are 16-bit timers

The ATtiny boards, such as `ATtiny3217`, `ATtiny1617`, will have only maximum 2 TCB timers, (TCB0-TCB1).

The ATtiny boards, such as `ATtiny817`, will have only maximum 1 TCB timer, (TCB0).

The number of TCB timers will be automatically configured by the library.

The following is the partial list of number of TCBs for each ATtiny board/chip

#### TCB0-TCB1, TCA, TCD

**ATtiny3217, ATtiny1617, ATtiny3216, ATtiny1616, ATtiny1614**

#### TCB0, TCA, TCD

**ATtinyx12, ATtinyx14, ATtinyx16, ATtinyx17, such as ATtiny817, ATtiny417, ATtiny816, etc.**

#### TCB0, TCA, no TCD

**ATtinyx02, ATtinyx04, ATtinyx06, ATtinyx07, such as ATtiny1607, ATtiny807, ATtiny1606, etc.**

---
---

## Usage


Before using any Timer, you have to make sure the Timer has not been used by any other purpose.


#### 1. Init Hardware Timer

```
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

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "ATtiny_Slow_PWM.h"

// Init AT_TINY_SLOW_PWM, each can service max 64 different ISR-based PWM channels
AT_TINY_SLOW_PWM_ISR ISR_PWM;
```

#### 2. Set PWM Frequency, dutycycle, attach irqCallbackStartFunc and irqCallbackStopFunc functions

```
void irqCallbackStartFunc()
{

}

void irqCallbackStopFunc()
{

}

void setup()
{
  ....
  
  // You can use this with PWM_Freq in Hz
  ISR_PWM.setPWM(PWM_Pin, PWM_Freq, PWM_DutyCycle, irqCallbackStartFunc, irqCallbackStopFunc);
                   
  ....                 
}  
```

---
---

### Examples: 

 1. [ISR_8_PWMs_Array](examples/ISR_8_PWMs_Array)
 2. [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex)
 3. [ISR_8_PWMs_Array_Simple](examples/ISR_8_PWMs_Array_Simple)
 4. [ISR_Changing_PWM](examples/ISR_Changing_PWM)
 5. [ISR_Modify_PWM](examples/ISR_Modify_PWM)
 6. [**multiFileProject**](examples/multiFileProject) **New**

 
---
---

### Example [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex)

https://github.com/khoih-prog/ATtiny_Slow_PWM/blob/137d892c07ae02b04dcc86b4dfeb25093521595b/examples/ISR_8_PWMs_Array_Complex/ISR_8_PWMs_Array_Complex.ino#L16-L481


---
---

### Debug Terminal Output Samples

### 1. ISR_8_PWMs_Array_Complex on AVR_ATtiny3217

The following is the sample terminal output when running example [ISR_8_PWMs_Array_Complex](examples/ISR_8_PWMs_Array_Complex) **Curiosity Nano AVR_ATtiny3217** to demonstrate how to use multiple PWM channels with complex callback functions, the accuracy of ISR Hardware PWM-channels, **especially when system is very busy**.  The ISR PWM-channels is **running exactly according to corresponding programmed periods and duty-cycles**


```
Starting ISR_8_PWMs_Array_Complex on AVR_ATtiny3217
ATtiny_Slow_PWM v1.0.0
CPU Frequency = 20 MHz
Max number PWM channels = 16
TCB Clock Frequency = Full clock (20/16MHz, etc) for highest accuracy
Starting ITimer OK, micros() = 15569
[PWM] Frequency =  1.00
[PWM] Frequency =  2.00
[PWM] Frequency =  3.00
[PWM] Frequency =  4.00
[PWM] Frequency =  5.00
[PWM] Frequency =  6.00
[PWM] Frequency =  7.00
[PWM] Frequency =  8.00
SimpleTimer (us): 2000, us : 7889400, Dus : 7868891
PWM Channel : 0, prog Period (ms): 1000.00, actual : 1000065, prog DutyCycle : 5, actual : 5.00
PWM Channel : 1, prog Period (ms): 500.00, actual : 500018, prog DutyCycle : 10, actual : 9.99
PWM Channel : 2, prog Period (ms): 333.33, actual : 333369, prog DutyCycle : 20, actual : 19.99
PWM Channel : 3, prog Period (ms): 250.00, actual : 249361, prog DutyCycle : 30, actual : 30.06
PWM Channel : 4, prog Period (ms): 200.00, actual : 199999, prog DutyCycle : 40, actual : 39.97
PWM Channel : 5, prog Period (ms): 166.67, actual : 166717, prog DutyCycle : 45, actual : 44.95
PWM Channel : 6, prog Period (ms): 142.86, actual : 142904, prog DutyCycle : 50, actual : 49.94
PWM Channel : 7, prog Period (ms): 125.00, actual : 125031, prog DutyCycle : 55, actual : 54.95
SimpleTimer (us): 2000, us : 15209668, Dus : 7320268
PWM Channel : 0, prog Period (ms): 1000.00, actual : 1000067, prog DutyCycle : 5, actual : 5.00
PWM Channel : 1, prog Period (ms): 500.00, actual : 500047, prog DutyCycle : 10, actual : 9.99
PWM Channel : 2, prog Period (ms): 333.33, actual : 333331, prog DutyCycle : 20, actual : 19.99
PWM Channel : 3, prog Period (ms): 250.00, actual : 175834, prog DutyCycle : 30, actual : 42.64
PWM Channel : 4, prog Period (ms): 200.00, actual : 200075, prog DutyCycle : 40, actual : 39.96
PWM Channel : 5, prog Period (ms): 166.67, actual : 166723, prog DutyCycle : 45, actual : 44.97
PWM Channel : 6, prog Period (ms): 142.86, actual : 142909, prog DutyCycle : 50, actual : 49.96
PWM Channel : 7, prog Period (ms): 125.00, actual : 125073, prog DutyCycle : 55, actual : 54.96
SimpleTimer (us): 2000, us : 22983887, Dus : 7774219
PWM Channel : 0, prog Period (ms): 1000.00, actual : 1000031, prog DutyCycle : 5, actual : 5.00
PWM Channel : 1, prog Period (ms): 500.00, actual : 500018, prog DutyCycle : 10, actual : 9.99
PWM Channel : 2, prog Period (ms): 333.33, actual : 333332, prog DutyCycle : 20, actual : 19.99
PWM Channel : 3, prog Period (ms): 250.00, actual : 250023, prog DutyCycle : 30, actual : 29.99
PWM Channel : 4, prog Period (ms): 200.00, actual : 200032, prog DutyCycle : 40, actual : 39.97
PWM Channel : 5, prog Period (ms): 166.67, actual : 166716, prog DutyCycle : 45, actual : 44.95
PWM Channel : 6, prog Period (ms): 142.86, actual : 142865, prog DutyCycle : 50, actual : 49.98
PWM Channel : 7, prog Period (ms): 125.00, actual : 125062, prog DutyCycle : 55, actual : 54.98
...
```

---

### 2. ISR_8_PWMs_Array on AVR_ATtiny3217

The following is the sample terminal output when running example [**ISR_8_PWMs_Array**](examples/ISR_8_PWMs_Array) on **AVR_ATtiny3217** to demonstrate how to use multiple PWM channels with simple callback functions.

```
Starting ISR_8_PWMs_Array on AVR_ATtiny3217
ATtiny_Slow_PWM v1.0.0
CPU Frequency = 20 MHz
Max number PWM channels = 16
TCB Clock Frequency = Full clock (20/16MHz, etc) for highest accuracy
Starting ITimer OK, micros() = 14778
[PWM] Frequency =  1.00
[PWM] Frequency =  2.00
[PWM] Frequency =  3.00
[PWM] Frequency =  4.00
[PWM] Frequency =  5.00
[PWM] Frequency =  6.00
[PWM] Frequency =  7.00
[PWM] Frequency =  8.00
```

---

### 3. ISR_8_PWMs_Array_Simple on AVR_ATtiny3217

The following is the sample terminal output when running example [**ISR_8_PWMs_Array_Simple**](examples/ISR_8_PWMs_Array_Simple) on **AVR_ATtiny3217** to demonstrate how to use multiple PWM channels.

```
Starting ISR_8_PWMs_Array_Simple on AVR_ATtiny3217
ATtiny_Slow_PWM v1.0.0
CPU Frequency = 20 MHz
Max number PWM channels = 16
TCB Clock Frequency = Full clock (20/16MHz, etc) for highest accuracy
Starting ITimer OK, micros() = 15609
[PWM] Frequency =  1.00
[PWM] Frequency =  2.00
[PWM] Frequency =  3.00
[PWM] Frequency =  4.00
[PWM] Frequency =  5.00
[PWM] Frequency =  6.00
[PWM] Frequency =  7.00
[PWM] Frequency =  8.00
```

---

### 4. ISR_Modify_PWM on AVR_ATtiny3217

The following is the sample terminal output when running example [ISR_Modify_PWM](examples/ISR_Modify_PWM) on **AVR_ATtiny3217** to demonstrate how to modify PWM settings on-the-fly without deleting the PWM channel

```
Starting ISR_Modify_PWM on AVR_ATtiny3217
ATtiny_Slow_PWM v1.0.0
CPU Frequency = 20 MHz
Max number PWM channels = 16
TCB Clock Frequency = Full clock (20/16MHz, etc) for highest accuracy
Starting ITimer OK, micros() = 14755
Using PWM Freq = 2.00, PWM DutyCycle = 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
Modify Freq => 1.00, DC => 5.55
Modify Freq => 2.00, DC => 10.00
```

---

### 5. ISR_Changing_PWM on AVR_ATtiny3217

The following is the sample terminal output when running example [ISR_Changing_PWM](examples/ISR_Changing_PWM) on **AVR_ATtiny3217** to demonstrate how to modify PWM settings on-the-fly by deleting the PWM channel and reinit the PWM channel

```
Starting ISR_Changing_PWM on AVR_ATtiny3217
ATtiny_Slow_PWM v1.0.0
CPU Frequency = 20 MHz
Max number PWM channels = 16
TCB Clock Frequency = Full clock (20/16MHz, etc) for highest accuracy
Starting ITimer OK, micros() = 14769
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
PWM Freq = 1.00, DC = 50.00
PWM Freq = 2.00, DC = 90.00
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [ATtiny_Slow_PWM issues](https://github.com/khoih-prog/ATtiny_Slow_PWM/issues)

---

## TO DO

1. Search for bug and improvement
2. Add support to **AVR ATtiny-based boards (ATtiny3217, etc.)** using [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore)

---

## DONE

 1. Basic hardware multi-channel PWM for **AVR ATtiny-based boards (ATtiny3217, etc.)** using [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore)
 2. Add Table of Contents
 3. Add functions to modify PWM settings on-the-fly
 4. Fix `multiple-definitions` linker error
 5. Optimize library code by using `reference-passing` instead of `value-passing`
 6. Improve accuracy by using `float`, instead of `uint32_t` for `dutycycle`
 7. DutyCycle to be optionally updated at the end current PWM period instead of immediately.
 8. Display informational warning only when `_PWM_LOGLEVEL_` > 3
 9. Make `MAX_NUMBER_CHANNELS` configurable to max **64 PWM channels**
10. Remove debug codes possibly causing hang


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library. Especially to these people who have directly or indirectly contributed to this [Dx_TimerInterrupt library](https://github.com/khoih-prog/Dx_TimerInterrupt)

1. Thanks to good work of [Spence Konde (aka Dr. Azzy)](https://github.com/SpenceKonde) for the [megaTinyCore](https://github.com/SpenceKonde/megaTinyCore)
2. Thanks to [LaurentR59](https://github.com/LaurentR59) to request 
- the enhancement [Support for DX CORE CPU and MightyCORE CPU possible? #8](https://github.com/khoih-prog/TimerInterrupt_Generic/issues/8) leading to this new library


<table>
  <tr>
    <td align="center"><a href="https://github.com/SpenceKonde"><img src="https://github.com/SpenceKonde.png" width="100px;" alt="SpenceKonde"/><br/><sub><b>⭐️⭐️ Spence Konde</b></sub></a><br/></td>
    <td align="center"><a href="https://github.com/LaurentR59"><img src="https://github.com/LaurentR59.png" width="100px;" alt="LaurentR59"/><br/><sub><b>LaurentR59</b></sub></a><br/></td>
  </tr> 
</table>


---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/ATtiny_Slow_PWM/blob/main/LICENSE)

---

## Copyright

Copyright 2022- Khoi Hoang


