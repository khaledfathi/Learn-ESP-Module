/*
 * DRIVERS.H
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */

#ifndef DRIVERS_H_
#define DRIVERS_H_

#include <string.h>
#include "DRIVERS_CONFIG.h"
#include "applib.h"


/****LED****/
class LED : private DIO{
public :
	void init(void){
		set_dir(LED0_PORT, LED_PIN0, LED_OUTPUT);
		set_dir(LED1_PORT, LED_PIN1, LED_OUTPUT);
		set_dir(LED2_PORT, LED_PIN2, LED_OUTPUT);
	}
	void action(char *led_num , char *action ){
		for (;*led_num!='\0';led_num++ ){
			if (!strcmp((char*)action,"ON")){
				switch (*led_num){
				case '0':
					set_pin(LED0_PORT, LED_PIN0, LED_HIGH);
				break;
				case '1':
					set_pin(LED1_PORT, LED_PIN1, LED_HIGH);
				break;
				case '2':
					set_pin(LED2_PORT, LED_PIN2, LED_HIGH);
				break;
				}
			}
			if (!strcmp((char*)action,"OFF")){
				switch (*led_num){
				case '0':
					set_pin(LED0_PORT, LED_PIN0, LED_LOW);
				break;
				case '1':
					set_pin(LED1_PORT, LED_PIN1, LED_LOW);
				break;
				case '2':
					set_pin(LED2_PORT, LED_PIN2, LED_LOW);
				break;
				}
			}
			if (!strcmp((char*)action,"TGL")){
				switch (*led_num){
				case '0':
					toggle_pin(LED0_PORT, LED_PIN0);
				break;
				case '1':
					toggle_pin(LED1_PORT, LED_PIN1);
				break;
				case '2':
					toggle_pin(LED2_PORT, LED_PIN2);
				break;
				}
			}
		}
	}
};
/***********/

/****LCD****/
class LCD : private DIO{
public :
	void init(void){ //4bit mode
	   //Define direction for control pins
	   set_dir(LCD_CNTRL_PORT, LCD_RS, LCD_OUTPUT);
	   set_dir(LCD_CNTRL_PORT, LCD_RW, LCD_OUTPUT);
	   set_dir(LCD_CNTRL_PORT, LCD_EN, LCD_OUTPUT);
	   //Define direction for data pins
	   set_dir(LCD_DATA_PORT, LCD_DTA4, LCD_OUTPUT);
	   set_dir(LCD_DATA_PORT, LCD_DTA5, LCD_OUTPUT);
	   set_dir(LCD_DATA_PORT, LCD_DTA6, LCD_OUTPUT);
	   set_dir(LCD_DATA_PORT, LCD_DTA7, LCD_OUTPUT);
	   //Define commands needed to choose 4Bit mode [depend on datasheet]
	   command(0x33);
	   command(0x32);
	   command(0x28);
	   command(0x02);
	   command(0x0C);
	   command(0x01);
	   command(0x06);
	}
	void command (Uint8t command){
		//Register Select pin will select control register
		set_pin(LCD_CNTRL_PORT, LCD_RS, LCD_LOW);
		//Read/Write pin will be write on LCD
		set_pin(LCD_CNTRL_PORT, LCD_RW, LCD_LOW);
		//Be sure that enable is disabled
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_LOW);
		//Send high nipple of the command, without changing old PORTA pins(0-3)
		send_high_nipple(LCD_DATA_PORT, command);
		//Send High pulse for 1 ms
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_HIGH);
		_delay_ms(1);
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_LOW);
		//Send low nipple of the command, without changing old PORTA pins(0-3)
		send_low_nipple(LCD_DATA_PORT, command);
		//Send High pulse for 1 ms
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_HIGH);
		_delay_ms(1);
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_LOW);
		//Wait controller to finish command
		_delay_ms(5);
	}
	void write_character (Uint8t character){
		//Register Select pin will select data register
		set_pin(LCD_CNTRL_PORT, LCD_RS, LCD_HIGH);
		//Read/Write pin will be write on LCD
		set_pin(LCD_CNTRL_PORT, LCD_RW, LCD_LOW);
		//Be sure that enable is disabled
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_LOW);
		//Send high nipple of the command, without changing old PORTA pins(0-3)
		send_high_nipple(LCD_DATA_PORT, character);
		//Send High pulse for 1 ms
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_HIGH);
		_delay_ms(1);
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_LOW);
		//Send low nipple of the command, without changing old PORTA pins(0-3)
		send_low_nipple(LCD_DATA_PORT, character);
		//Send High pulse for 1 ms
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_HIGH);
		_delay_ms(1);
		set_pin(LCD_CNTRL_PORT, LCD_EN, LCD_LOW);
		//Wait controller to finish command
		_delay_ms(5);
	}
	void write_string(Uint8t* str){
		 while(*str != '\0')
		{
			write_character(*str);
			_delay_ms(10);
			str++;
		}
	}
	void write_number(Uint32t num){
		write_string(int2str(num));
	}
	void clear(void){
        command(0x01);
	}
	void cursor_to_home (void){
		command(0x02);
	}
	void cursor_position(Uint8t col , Uint8t row){
        switch(row){
		case 1 :
		command(0x80 + col-1);
		break;
		case 2 :
		command(0xC0 + col-1);
		break;
        }
	}
};
/***********/

/****7seg****/
class SEG : private DIO {
public:
	void init(void){
		set_dir(SEG_CNTRL_PORT, SEG_EN1, SEG_OUTPUT);
		set_dir(SEG_CNTRL_PORT, SEG_EN2, SEG_OUTPUT);
		set_dir(SEG_DATA_PORT, SEG_DTA0_A, SEG_OUTPUT);
		set_dir(SEG_DATA_PORT, SEG_DTA1_B, SEG_OUTPUT);
		set_dir(SEG_DATA_PORT, SEG_DTA2_C, SEG_OUTPUT);
		set_dir(SEG_DATA_PORT, SEG_DTA3_D, SEG_OUTPUT);
	}
	void display(Uint8t data , Uint16t time){
		if (time<2) time = 2;
		time= time/2;
		Uint8t data0 = data % 10;
		Uint8t data1 = data / 10;
		for (;0<time;time--){
			PORTA = (data0 << 4) | (PORTA & 0x0F);
			set_pin(SEG_CNTRL_PORT, SEG_EN1, SEG_HIGH);
			set_pin(SEG_CNTRL_PORT, SEG_EN2, SEG_LOW);
			_delay_ms(1);
			PORTA = (data1 << 4) | (PORTA & 0x0F);
			set_pin(SEG_CNTRL_PORT, SEG_EN1, SEG_LOW);
			set_pin(SEG_CNTRL_PORT, SEG_EN2, SEG_HIGH);
			_delay_ms(1);
		}
		set_pin(SEG_CNTRL_PORT, SEG_EN1, SEG_LOW);
		set_pin(SEG_CNTRL_PORT, SEG_EN2, SEG_LOW);
	}
};
/***********/

/****KEYPAD****/
class KEYPAD : private DIO{
public:
	void init (void){
		set_dir(KEYPAD_PORT, KEYPAD_COL0, KEYPAD_OUTPUT);
		set_dir(KEYPAD_PORT, KEYPAD_COL1, KEYPAD_OUTPUT);
		set_dir(KEYPAD_PORT, KEYPAD_COL2, KEYPAD_OUTPUT);
		set_dir(KEYPAD_PORT, KEYPAD_COL3, KEYPAD_OUTPUT);

		set_pin(KEYPAD_PORT, KEYPAD_COL0, KEYPAD_HIGH);
		set_pin(KEYPAD_PORT, KEYPAD_COL1, KEYPAD_HIGH);
		set_pin(KEYPAD_PORT, KEYPAD_COL2, KEYPAD_HIGH);
		set_pin(KEYPAD_PORT, KEYPAD_COL3, KEYPAD_HIGH);

		set_dir(KEYPAD_PORT, KEYPAD_ROW0, KEYPAD_INPUT);
		set_dir(KEYPAD_PORT, KEYPAD_ROW1, KEYPAD_INPUT);
		set_dir(KEYPAD_PORT, KEYPAD_ROW2, KEYPAD_INPUT);
		set_dir(KEYPAD_PORT, KEYPAD_ROW3, KEYPAD_INPUT);

		set_pullup(KEYPAD_PORT, KEYPAD_ROW0);
		set_pullup(KEYPAD_PORT, KEYPAD_ROW1);
		set_pullup(KEYPAD_PORT, KEYPAD_ROW2);
		set_pullup(KEYPAD_PORT, KEYPAD_ROW3);
	}
	Uint8t read_press(void){
		Uint8t keys [4][4]={
				//1,2,3,A
				//4,5,6,B
				//7,8,9,C
				//#,0,*,D
				{1,2,3,16},
				{4,5,6,15},
				{7,8,9,14},
				{10,11,12,13},
		};
		Uint8t row ,col ,value=0 ;
		for (col=4 ; col<=7 ; col++){
			set_pin(KEYPAD_PORT, col, KEYPAD_LOW);
			for (row= 0 ; row<=3 ; row++){
				if(!read_pin(KEYPAD_PORT, row)){
					value=keys[row][col-4];
					while(!read_pin(KEYPAD_PORT, row));//Waiting for release press
				}
			}
			set_pin(KEYPAD_PORT, col, KEYPAD_HIGH);
		}
		return value ;
	}
	Uint8t read(void){ // @suppress("No return")
		volatile Uint8t data= read_press()  ;
		if (data){
			switch (data){
			case 1:
				return 1;
			break;
			case 2:
				return 2;
			break;
			case 3:
				return 3;
			break;
			case 4:
				return 4;
			break;
			case 5:
				return 5;
			break;
			case 6:
				return 6;
			break;
			case 7:
				return 7;
			break;
			case 8:
				return 8;
			break;
			case 9:
				return 9;
			break;
			case 10:
				return '*';
			break;
			case 11:
				return 0;
			break;
			case 12:
				return '#';
			break;
			case 13:
				return 'D';
			break;
			case 14:
				return 'C';
			break;
			case 15:
				return 'B';
			break;
			case 16:
				return 'A';
			break;
			}
		}
		return 16;
	}

};
/***********/

/****UART****/
class UART{
public:
	void init(void){
	        Uint16t UBRR_Val = 0;//Baud rate value
	        UCSRB = (1 << RXEN) | (1 << TXEN);//enable transmitter and reciver
	        UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);//full config for UART
	        //Baud Rate Calculations
	        UBRR_Val = (((FRQ) / (16 * BAUDRATE)) - 1);
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
/***********/

/****ADC****/
class ANALOG{
public :
public:
	void init (void){
	 CLR_BIT(ADMUX , REFS1 );SET_BIT(ADMUX , REFS0 );

	 CLR_BIT(ADMUX , ADLAR );

	 CLR_BIT(ADMUX , MUX4 );CLR_BIT(ADMUX , MUX3 );CLR_BIT(ADMUX , MUX2 );CLR_BIT(ADMUX , MUX1 );CLR_BIT(ADMUX , MUX0 );
	 /*
	 ADMUX = 0b01000001;
	 ADMUX = 0x41;
	 ADMUX |= (1 << REFS0) | (1 << MUX0);
	  */
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
/***********/
#endif /* DRIVERS_H_ */

