/*
 * peripherals.h
 *
 *  Created on: Apr 11, 2021
 *      Author: khaled
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <string.h>
#include "MCU_Config.h"

//like ADC,TIMERS,UART,I2C,SPI [peripherals inside MCU]

/*########## PERIPHERALS PORTS/PINS CONFIG ##########*/
/****UART****/
//in class config
/*****END******/

/****ADC****/
//in class config
/*****END******/

/****TIMER0****/
//in class config
/*****END******/
/*########## END OF SECTION ##########*/

/*########## PERIPHERALS CLASSES ##########*/

/****UART****/
class UART{
private :
	Uint8t baud_rate;
	Uint32t FRQ;
public:
	UART( Uint8t baud_rate_){
		FRQ= F_CPU/100;
		baud_rate = baud_rate_;
		init();
	}
	void init(){//manual baudrate [overload]
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
private :
	Uint8t channel;
	char *ref;
public :
	ANALOG(Uint8t channel_ =1 ,char *ref_=(char*)"AVCC"){
		channel= channel_;
		ref= ref_;
		init();
	}
	void init (void){
		if(!strcmp(ref , (char*)"AVCC")){//select REF
			CLR_BIT(ADMUX , REFS1 );SET_BIT(ADMUX , REFS0 );
		}else if(!strcmp(ref , (char*)"AVCC")){
			SET_BIT(ADMUX , REFS1 );SET_BIT(ADMUX , REFS0 );
		}
		CLR_BIT(ADMUX , ADLAR );//left adjest

		switch(channel){//Select channel
		case 0:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );CLR_BIT(ADMUX , MUX2 );CLR_BIT(ADMUX , MUX1 );CLR_BIT(ADMUX , MUX0 );//ADC0
		break;
		case 1:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );CLR_BIT(ADMUX , MUX2 );CLR_BIT(ADMUX , MUX1 );SET_BIT(ADMUX , MUX0 );//ADC1
		break;
		case 2:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );CLR_BIT(ADMUX , MUX2 );SET_BIT(ADMUX , MUX1 );CLR_BIT(ADMUX , MUX0 );//ADC2
		break;
		case 3:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );CLR_BIT(ADMUX , MUX2 );SET_BIT(ADMUX , MUX1 );SET_BIT(ADMUX , MUX0 );//ADC3
		break;
		case 4:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );SET_BIT(ADMUX , MUX2 );CLR_BIT(ADMUX , MUX1 );CLR_BIT(ADMUX , MUX0 );//ADC4
		break;
		case 5:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );SET_BIT(ADMUX , MUX2 );CLR_BIT(ADMUX , MUX1 );SET_BIT(ADMUX , MUX0 );//ADC5
		break;
		case 6:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );CLR_BIT(ADMUX , MUX2 );SET_BIT(ADMUX , MUX1 );SET_BIT(ADMUX , MUX0 );//ADC6
		break;
		case 7:
			CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );SET_BIT(ADMUX , MUX2 );SET_BIT(ADMUX , MUX1 );SET_BIT(ADMUX , MUX0 );//ADC7
		break;
		}
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

/****TIMER0****/


class TIMER0 {
private :
	char *mode ;
	Uint16t prescaler;
	char *pwm_dir ;

public:
	TIMER0(char *mode_=(char*)"OVF" , Uint16t prescaler_=256 , char *pwm_dir_ = (char*)"NON_INVERTING"){
		mode=mode_;
		prescaler=prescaler_;
		pwm_dir=pwm_dir_;
		if (!strcmp(mode , (char*)"OVF")){
			ovf_init();
			ovf_start(prescaler);
		}else if (!strcmp(mode , (char*)"CTC")){
			CTC_init();
			CTC_start(prescaler);
		}if (!strcmp(mode , (char*)"PWM")){
			fast_pwm_init();
			fast_pwm_duty(100);
			fast_pwm_start();
		}
	}
	/*Functions for Timer0 with Normal Mode*/
	void ovf_init(void){
		CLR_BIT(TCCR0, WGM01); CLR_BIT(TCCR0, WGM00);//Select Normal mode
		SET_BIT(SREG, 7);//Enable Global interrupt
		SET_BIT(TIMSK, TOIE0);//Enable Peripheral interrupt
	}
	void ovf_start(Uint16t prescaler){
		switch(prescaler)//Choose prescaler to start operation
		{
			case 0:
			CLR_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);SET_BIT(TCCR0, CS00);
			break;
			case 8:
			CLR_BIT(TCCR0, CS02);SET_BIT(TCCR0, CS01);CLR_BIT(TCCR0, CS00);
			break;
			case 64:
			CLR_BIT(TCCR0, CS02);SET_BIT(TCCR0, CS01);SET_BIT(TCCR0, CS00);
			break;
			case 256:
			SET_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);CLR_BIT(TCCR0, CS00);
			break;
			case 1024:
			SET_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);SET_BIT(TCCR0, CS00);
			break;
		}
	}
	void ovf_stop(void){
		CLR_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);CLR_BIT(TCCR0, CS00);
	}
	/*Functions for Timer0 with Normal Mode*/
	void CTC_init(void){
		SET_BIT(TCCR0, WGM01); CLR_BIT(TCCR0, WGM00);//Select CTC mode
		SET_BIT(SREG, 7);//Enable Global interrupt
		SET_BIT(TIMSK, OCIE0);//Enable Peripheral interrupt
	}
	void CTC_start(Uint16t prescaler){
		switch(prescaler)//Choose prescaler to start operation
		{
			case 8:
			CLR_BIT(TCCR0, CS02);SET_BIT(TCCR0, CS01);CLR_BIT(TCCR0, CS00);
			break;
			case 64:
			CLR_BIT(TCCR0, CS02);SET_BIT(TCCR0, CS01);SET_BIT(TCCR0, CS00);
			break;
			case 256:
			SET_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);CLR_BIT(TCCR0, CS00);
			break;
			case 1024:
			SET_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);SET_BIT(TCCR0, CS00);
			break;
		}
	}
	void CTC_stop(void){
		CLR_BIT(TCCR0, CS02);CLR_BIT(TCCR0, CS01);CLR_BIT(TCCR0, CS00);
	}
	void fast_pwm_init(void){
		//define direction for OC0 pin as
		SET_BIT(DDRB , PB3);
		//chose fast PWM mode wave generation
		SET_BIT(TCCR0 , WGM01);SET_BIT(TCCR0 , WGM00);
		//choose inverting or non inverting
		if (!strcmp(pwm_dir , "NON_INVERTING")){
			SET_BIT(TCCR0 , COM01);CLR_BIT(TCCR0 , COM00);
		}else if (!strcmp(pwm_dir , "INVERTING")){
			SET_BIT(TCCR0 , COM01);SET_BIT(TCCR0 , COM00);
		}else {
			SET_BIT(TCCR0 , COM01);CLR_BIT(TCCR0 , COM00);//Non inverting
		}
	}
	void fast_pwm_start(void){
		SET_BIT(TCCR0 , CS02);CLR_BIT(TCCR0 , CS01);CLR_BIT(TCCR0 , CS00);
	}
	void fast_pwm_duty(Uint8t dutycycle){
		if (!strcmp(pwm_dir , "NON_INVERTING")){
			OCR0 = ((256*dutycycle)/100)-1;
		}else if (!strcmp(pwm_dir , "NON_INVERTING")){
			OCR0 = 256 - (((256*dutycycle)/100)-1);
		}else {
			OCR0 = ((256*dutycycle)/100)-1;//non inverting equation
		}
	}
};
/*****END******/
/*########## END OF SECTION ##########*/
#endif /* PERIPHERALS_H_ */
