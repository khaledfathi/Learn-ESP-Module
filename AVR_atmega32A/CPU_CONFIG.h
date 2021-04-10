/*
 * CPU_CONFIG.h
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */

#ifndef CPU_CONFIG_H_
#define CPU_CONFIG_H_

#undef F_CPU
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO.h"

#endif /* CPU_CONFIG_H_ */
