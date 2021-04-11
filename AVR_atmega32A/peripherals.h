/*
 * peripherals.h
 *
 *  Created on: Apr 11, 2021
 *      Author: khaled
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "MCU_Config.h"
//like ADC,TIMERS,UART,I2C,SPI [peripherals inside MCU]

/*########## PERIPHERALS PORTS/PINS CONFIG ##########*/
/****UART****/
#define FRQ             160000
#define BAUDRATE        96
/*****END******/
/*########## END OF SECTION ##########*/

/*########## PERIPHERALS CLASSES ##########*/

/****UART****/
class UART{
public:
	void init(void){//default baud rate 9600
	        Uint16t UBRR_Val = 0;//Baud rate value
	        UCSRB = (1 << RXEN) | (1 << TXEN);//enable transmitter and reciver
	        UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);//full config for UART
	        //Baud Rate Calculations
	        UBRR_Val = (((FRQ) / (16 * BAUDRATE)) - 1);
	        //set baud rate [16bit register]
	        UBRRL = UBRR_Val;
	        UBRRH = UBRR_Val >> 8;
	}
	void init(Uint32t baud_rate){//manual baudrate [overload]
			Uint16t UBRR_Val = 0;//Baud rate value
			UCSRB = (1 << RXEN) | (1 << TXEN);//enable transmitter and reciver
			UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);//full config for UART
			//Baud Rate Calculations
			UBRR_Val = (((FRQ) / (16 * (baud_rate/100))) - 1);
			//set baud rate [16bit register]
			UBRRL = UBRR_Val;
			UBRRH = UBRR_Val >> 8;
	}
	void transmit(Uint8t data){
	        UDR = data;
	        while(GET_BIT(UCSRA, TXC) != 1);
	}
	Uint8t receive(void){
	        while(GET_BIT(UCSRA, RXC) != 1);
	        return UDR;
	}
};
/*****END******/

/****ADC****/
class ANALOG{
public :
public:
	void init (void){
	 CLR_BIT(ADMUX , REFS1 );SET_BIT(ADMUX , REFS0 );

	 CLR_BIT(ADMUX , ADLAR );

	 CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );CLR_BIT(ADMUX , MUX2 );CLR_BIT(ADMUX , MUX1 );CLR_BIT(ADMUX , MUX0 );
	 SET_BIT(ADCSRA , ADEN);
	 SET_BIT(ADCSRA , ADATE);
	 SET_BIT(ADCSRA , ADPS0);SET_BIT(ADCSRA , ADPS1);SET_BIT(ADCSRA , ADPS0);
	}
	Uint16t read (void){
	        Uint16t var = 0 ;
	        SET_BIT(ADCSRA , ADSC);
	        while (GET_BIT(ADCSRA,ADIF) !=1 );
	        var = ADC;
	        return var;
	}
};
/*****END******/
/*########## END OF SECTION ##########*/
#endif /* PERIPHERALS_H_ */
