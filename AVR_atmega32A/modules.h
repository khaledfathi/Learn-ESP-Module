/*
 * modules.h
 *
 *  Created on: Apr 11, 2021
 *      Author: khaled
 */

#ifndef MODULES_H_
#define MODULES_H_

#include <string.h>
#include "MCU_Config.h"
#include "applib.h"


//like LCD, blutooth, sensors [Modules Outside MCU]

/*########## Module PORTS/PINS CONFIG ##########*/
/****LED****/
#define LED0_PORT 	GPIO_PORTC
#define LED1_PORT 	GPIO_PORTC
#define LED2_PORT 	GPIO_PORTD
#define LED_PIN0  	GPIO_PIN2
#define LED_PIN1  	GPIO_PIN7
#define LED_PIN2  	GPIO_PIN3
#define LED_HIGH  	GPIO_HIGH
#define LED_LOW 	GPIO_LOW
#define LED_OUTPUT 	GPIO_OUTPUT
/*****END******/

/****LCD****/
#define LCD_CNTRL_PORT GPIO_PORTB
#define LCD_DATA_PORT  GPIO_PORTA
#define LCD_RS         GPIO_PIN1
#define LCD_RW         GPIO_PIN2
#define LCD_EN         GPIO_PIN3
#define LCD_DTA0       GPIO_PIN0
#define LCD_DTA1       GPIO_PIN1
#define LCD_DTA2       GPIO_PIN2
#define LCD_DTA3       GPIO_PIN3
#define LCD_DTA4       GPIO_PIN4
#define LCD_DTA5       GPIO_PIN5
#define LCD_DTA6       GPIO_PIN6
#define LCD_DTA7       GPIO_PIN7
#define LCD_LOW        GPIO_LOW
#define LCD_HIGH       GPIO_HIGH
#define LCD_OUTPUT     GPIO_OUTPUT
/*****END******/

/****7seg****/
#define SEG_CNTRL_PORT GPIO_PORTB
#define SEG_DATA_PORT  GPIO_PORTA
#define SEG_EN1        GPIO_PIN1
#define SEG_EN2        GPIO_PIN2
#define SEG_DTA0_A     GPIO_PIN4
#define SEG_DTA1_B     GPIO_PIN5
#define SEG_DTA2_C     GPIO_PIN6
#define SEG_DTA3_D     GPIO_PIN7
#define SEG_OUTPUT     GPIO_OUTPUT
#define SEG_LOW        GPIO_LOW
#define SEG_HIGH       GPIO_HIGH
/***********/

/****KEYPAD****/
#define KEYPAD_PORT 	GPIO_PORTC
#define KEYPAD_ROW0 	GPIO_PIN0
#define KEYPAD_ROW1 	GPIO_PIN1
#define KEYPAD_ROW2 	GPIO_PIN2
#define KEYPAD_ROW3 	GPIO_PIN3
#define KEYPAD_COL0 	GPIO_PIN4
#define KEYPAD_COL1 	GPIO_PIN5
#define KEYPAD_COL2 	GPIO_PIN6
#define KEYPAD_COL3 	GPIO_PIN7
#define KEYPAD_INPUT	GPIO_INPUT
#define KEYPAD_OUTPUT	GPIO_OUTPUT
#define KEYPAD_HIGH		GPIO_HIGH
#define KEYPAD_LOW		GPIO_LOW
/*****END******/
/*########## END OF SECTION ##########*/

/*########## Module CLASSES ##########*/
/****LED****/
class LED : private GPIO{
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
/*****END******/

/****LCD****/
class LCD : private GPIO{
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
/*****END******/

/****7seg****/
class SEG : private GPIO {
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
/*****END******/

/****KEYPAD****/
class KEYPAD : private GPIO{
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
/*****END******/
/*########## END OF SECTION ##########*/
#endif /* MODULES_H_ */
