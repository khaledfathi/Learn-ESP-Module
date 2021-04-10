/*
 * DRIVERS_CONFIG.h
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */

#ifndef DRIVERS_CONFIG_H_
#define DRIVERS_CONFIG_H_

#include "CPU_CONFIG.h"


/****LED****/
#define LED0_PORT 	DIO_PORTC
#define LED1_PORT 	DIO_PORTC
#define LED2_PORT 	DIO_PORTD
#define LED_PIN0  	DIO_PIN2
#define LED_PIN1  	DIO_PIN7
#define LED_PIN2  	DIO_PIN3
#define LED_HIGH  	DIO_HIGH
#define LED_LOW 	DIO_LOW
#define LED_OUTPUT 	DIO_OUTPUT
/***********/

/****LCD****/
#define LCD_CNTRL_PORT DIO_PORTB
#define LCD_DATA_PORT  DIO_PORTA
#define LCD_RS         DIO_PIN1
#define LCD_RW         DIO_PIN2
#define LCD_EN         DIO_PIN3
#define LCD_DTA0       DIO_PIN0
#define LCD_DTA1       DIO_PIN1
#define LCD_DTA2       DIO_PIN2
#define LCD_DTA3       DIO_PIN3
#define LCD_DTA4       DIO_PIN4
#define LCD_DTA5       DIO_PIN5
#define LCD_DTA6       DIO_PIN6
#define LCD_DTA7       DIO_PIN7
#define LCD_LOW        DIO_LOW
#define LCD_HIGH       DIO_HIGH
#define LCD_OUTPUT     DIO_OUTPUT
/***********/

/****7seg****/
#define SEG_CNTRL_PORT DIO_PORTB
#define SEG_DATA_PORT  DIO_PORTA
#define SEG_EN1        DIO_PIN1
#define SEG_EN2        DIO_PIN2
#define SEG_DTA0_A     DIO_PIN4
#define SEG_DTA1_B     DIO_PIN5
#define SEG_DTA2_C     DIO_PIN6
#define SEG_DTA3_D     DIO_PIN7
#define SEG_OUTPUT     DIO_OUTPUT
#define SEG_LOW        DIO_LOW
#define SEG_HIGH       DIO_HIGH
/***********/

/****KEYPAD****/
#define KEYPAD_PORT 	DIO_PORTC
#define KEYPAD_ROW0 	DIO_PIN0
#define KEYPAD_ROW1 	DIO_PIN1
#define KEYPAD_ROW2 	DIO_PIN2
#define KEYPAD_ROW3 	DIO_PIN3
#define KEYPAD_COL0 	DIO_PIN4
#define KEYPAD_COL1 	DIO_PIN5
#define KEYPAD_COL2 	DIO_PIN6
#define KEYPAD_COL3 	DIO_PIN7
#define KEYPAD_INPUT	DIO_INPUT
#define KEYPAD_OUTPUT	DIO_OUTPUT
#define KEYPAD_HIGH		DIO_HIGH
#define KEYPAD_LOW		DIO_LOW

/***********/

/****UART****/

#define FRQ             160000
#define BAUDRATE        96

/***********/




#endif /* DRIVERS_CONFIG_H_ */
