/*
 * CPU_CONFIG.h
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */

#ifndef MCU_CONFIG_H_
#define MCU_CONFIG_H_

#undef F_CPU
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/********** STANDER TYPES **********/
typedef unsigned char Uint8t;
typedef unsigned short int Uint16t;
typedef unsigned long int Uint32t;
typedef signed char Int8t;
typedef signed short int Int16t;
typedef signed long int Int32t;
typedef float Fint32t;
typedef double Dint64t;
/********** END **********/

/********** BIT MATH **********/
#define SET_BIT(REG,BIT)         REG |= (1<<BIT)
#define CLR_BIT(REG,BIT)         REG &=~ (1<<BIT)
#define GET_BIT(REG,BIT)         ((REG>>BIT)&1)
#define TGL_BIT(REG,BIT)     	 REG ^= (1<<BIT)
#define Get_LOW_Nibble(REG)  	 REG & 0x0F
#define Get_HIGH_Nibble(REG) 	 (REG>>4) & 0b00001111
#define GET_PORT(REG) 			 REG & 0xFF
#define TGL_PORT(REG) 			 REG ^= 0xFF
/********** END **********/


/********** PORT/PIN/STATUS RENAMING **********/
#define GPIO_PORTA	0
#define GPIO_PORTB	1
#define GPIO_PORTC	2
#define GPIO_PORTD	3
#define GPIO_PIN0 	0
#define GPIO_PIN1 	1
#define GPIO_PIN2 	2
#define GPIO_PIN3 	3
#define GPIO_PIN4 	4
#define GPIO_PIN5 	5
#define GPIO_PIN6 	6
#define GPIO_PIN7 	7
#define GPIO_LOW 	0
#define GPIO_HIGH 	1
#define GPIO_INPUT 	0
#define GPIO_OUTPUT 	1
/********** END **********/

/********** GPIO CONFIG CLASS **********/
class GPIO {
public :
	void set_dir(Uint8t port ,Uint8t pin , Uint8t dir){
		if (dir== GPIO_OUTPUT){
			switch(port){
			case GPIO_PORTA:
				SET_BIT(DDRA , pin);
			break;
			case GPIO_PORTB:
				SET_BIT(DDRB , pin);
			break;
			case GPIO_PORTC:
				SET_BIT(DDRC , pin);
			break;
			case GPIO_PORTD:
				SET_BIT(DDRD , pin);
			break;
			}
		}else if (dir ==GPIO_INPUT){
			switch(port){
			case GPIO_PORTA:
				CLR_BIT(DDRA , pin);
			break;
			case GPIO_PORTB:
				CLR_BIT(DDRB , pin);
			break;
			case GPIO_PORTC:
				CLR_BIT(DDRC , pin);
			break;
			case GPIO_PORTD:
				CLR_BIT(DDRD , pin);
			break;
			}
		}
	}
	void set_pin(Uint8t port ,Uint8t pin , Uint8t status){
		if (status== GPIO_HIGH){
			switch(port){
			case GPIO_PORTA:
				SET_BIT(PORTA , pin);
			break;
			case GPIO_PORTB:
				SET_BIT(PORTB , pin);
			break;
			case GPIO_PORTC:
				SET_BIT(PORTC , pin);
			break;
			case GPIO_PORTD:
				SET_BIT(PORTD , pin);
			break;
			}
		}else if (status ==GPIO_LOW){
			switch(port){
			case GPIO_PORTA:
				CLR_BIT(PORTA , pin);
			break;
			case GPIO_PORTB:
				CLR_BIT(PORTB , pin);
			break;
			case GPIO_PORTC:
				CLR_BIT(PORTC , pin);
			break;
			case GPIO_PORTD:
				CLR_BIT(PORTD , pin);
			break;
			}
		}
	}
	void set_pullup(Uint8t port ,Uint8t pin){
		switch (port){
		case GPIO_PORTA:
			SET_BIT(PORTA , pin);
		break;
		case GPIO_PORTB:
			SET_BIT(PORTB , pin);
		break;
		case GPIO_PORTC:
			SET_BIT(PORTC , pin);
		break;
		case GPIO_PORTD:
			SET_BIT(PORTD , pin);
		break;
		}
	}
	void toggle_pin(Uint8t port ,Uint8t pin){
		switch (port){
		case GPIO_PORTA:
			TGL_BIT(PORTA , pin);
		break;
		case GPIO_PORTB:
			TGL_BIT(PORTB , pin);
		break;
		case GPIO_PORTC:
			TGL_BIT(PORTC , pin);
		break;
		case GPIO_PORTD:
			TGL_BIT(PORTD , pin);
		break;
		}
	}
	Uint8t read_pin(Uint8t port ,Uint8t pin){
		Uint8t value ;
		switch (port){
		case GPIO_PORTA:
			value= GET_BIT(PINA , pin);
		break;
		case GPIO_PORTB:
			value = GET_BIT(PINB , pin);
		break;
		case GPIO_PORTC:
			value = GET_BIT(PINC , pin);
		break;
		case GPIO_PORTD:
			value = GET_BIT(PIND , pin);
		break;
		}
		return value;
	}
	void send_high_nipple(Uint8t port , Uint8t data){
		switch (port){
		case GPIO_PORTA:
			PORTA = (data & 0xF0) | (PORTA & 0x0F);
		break;
		case GPIO_PORTB:
			PORTB = (data & 0xF0) | (PORTA & 0x0F);
		break;
		case GPIO_PORTC:
			PORTC = (data& 0xF0) | (PORTA & 0x0F);
		break;
		case GPIO_PORTD:
			PORTD = (data & 0xF0) | (PORTA & 0x0F);
		break;
		}
	}
	void send_low_nipple(Uint8t port , Uint8t data){
		switch (port){
		case GPIO_PORTA:
			PORTA = (data<< 4) | (PORTA & 0x0F);
		break;
		case GPIO_PORTB:
			PORTB = (data<< 4) | (PORTA & 0x0F);
		break;
		case GPIO_PORTC:
			PORTC = (data<< 4) | (PORTA & 0x0F);
		break;
		case GPIO_PORTD:
			PORTD = (data<< 4) | (PORTA & 0x0F);
		break;
		}

	}
};
/********** END **********/

#endif /* MCU_CONFIG_H_ */
