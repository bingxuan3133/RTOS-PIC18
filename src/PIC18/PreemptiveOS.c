/* 
 * File:   PreemptiveOS.c
 * Author: Chiew Bing Xuan
 *
 * Created on November 03, 2014, 2:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "TaskControlBlock.h"


#if !(defined(__XC) || defined(__18CXX))
  #include "usart.h"
  #include "spi.h"
  #include "timers.h"
#else
    #include <usart.h>
#endif // __18CXX
