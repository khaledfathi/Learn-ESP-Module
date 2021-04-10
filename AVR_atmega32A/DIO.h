/*
 * DIO.h
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */

#ifndef DIO_H_
#define DIO_H_

#include "DIO_CONFIG.h"

class DIO {
public :
	void set_dir(Uint8t port ,Uint8t pin , Uint8t dir){
		if (dir== DIO_OUTPUT){
			switch(port){
			case DIO_PORTA:
				SET_BIT(DDRA , pin);
			break;
			case DIO_PORTB:
				SET_BIT(DDRB , pin);
			break;
			case DIO_PORTC:
				SET_BIT(DDRC , pin);
			break;
			case DIO_PORTD:
				SET_BIT(DDRD , pin);
			break;
			}
		}else if (dir ==DIO_INPUT){
			switch(port){
			case DIO_PORTA:
				CLR_BIT(DDRA , pin);
			break;
			case DIO_PORTB:
				CLR_BIT(DDRB , pin);
			break;
			case DIO_PORTC:
				CLR_BIT(DDRC , pin);
			break;
			case DIO_PORTD:
				CLR_BIT(DDRD , pin);
			break;
			}
		}
	}
	void set_pin(Uint8t port ,Uint8t pin , Uint8t status){
		if (status== DIO_HIGH){
			switch(port){
			case DIO_PORTA:
				SET_BIT(PORTA , pin);
			break;
			case DIO_PORTB:
				SET_BIT(PORTB , pin);
			break;
			case DIO_PORTC:
				SET_BIT(PORTC , pin);
			break;
			case DIO_PORTD:
				SET_BIT(PORTD , pin);
			break;
			}
		}else if (status ==DIO_LOW){
			switch(port){
			case DIO_PORTA:
				CLR_BIT(PORTA , pin);
			break;
			case DIO_PORTB:
				CLR_BIT(PORTB , pin);
			break;
			case DIO_PORTC:
				CLR_BIT(PORTC , pin);
			break;
			case DIO_PORTD:
				CLR_BIT(PORTD , pin);
			break;
			}
		}
	}
	void set_pullup(Uint8t port ,Uint8t pin){
		switch (port){
		case DIO_PORTA:
			SET_BIT(PORTA , pin);
		break;
		case DIO_PORTB:
			SET_BIT(PORTB , pin);
		break;
		case DIO_PORTC:
			SET_BIT(PORTC , pin);
		break;
		case DIO_PORTD:
			SET_BIT(PORTD , pin);
		break;
		}
	}
	void toggle_pin(Uint8t port ,Uint8t pin){
		switch (port){
		case DIO_PORTA:
			TGL_BIT(PORTA , pin);
		break;
		case DIO_PORTB:
			TGL_BIT(PORTB , pin);
		break;
		case DIO_PORTC:
			TGL_BIT(PORTC , pin);
		break;
		case DIO_PORTD:
			TGL_BIT(PORTD , pin);
		break;
		}
	}
	Uint8t read_pin(Uint8t port ,Uint8t pin){
		Uint8t value ;
		switch (port){
		case DIO_PORTA:
			value= GET_BIT(PINA , pin);
		break;
		case DIO_PORTB:
			value = GET_BIT(PINB , pin);
		break;
		case DIO_PORTC:
			value = GET_BIT(PINC , pin);
		break;
		case DIO_PORTD:
			value = GET_BIT(PIND , pin);
		break;
		}
		return value;
	}
	void send_high_nipple(Uint8t port , Uint8t data){
		switch (port){
		case DIO_PORTA:
			PORTA = (data & 0xF0) | (PORTA & 0x0F);
		break;
		case DIO_PORTB:
			PORTB = (data & 0xF0) | (PORTA & 0x0F);
		break;
		case DIO_PORTC:
			PORTC = (data& 0xF0) | (PORTA & 0x0F);
		break;
		case DIO_PORTD:
			PORTD = (data & 0xF0) | (PORTA & 0x0F);
		break;
		}
	}
	void send_low_nipple(Uint8t port , Uint8t data){
		switch (port){
		case DIO_PORTA:
			PORTA = (data<< 4) | (PORTA & 0x0F);
		break;
		case DIO_PORTB:
			PORTB = (data<< 4) | (PORTA & 0x0F);
		break;
		case DIO_PORTC:
			PORTC = (data<< 4) | (PORTA & 0x0F);
		break;
		case DIO_PORTD:
			PORTD = (data<< 4) | (PORTA & 0x0F);
		break;
		}

	}
};



#endif /* DIO_H_ */
