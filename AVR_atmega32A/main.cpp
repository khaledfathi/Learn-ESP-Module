/*
 * main.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */
#include "DRIVERS.h"
#include "applib.h"
#include <string.h>

LCD lcd ;
LED led;
UART serial;

int main (){
	lcd.init();
	led.init();
	serial.init();
	Uint8t data=0;
	while(true){
		if (serial.receive()=='c'){
			if (serial.receive()=='o'){
				if (serial.receive()=='m'){
					data= serial.receive();
				}
			}
		}
		if(data){
			switch(data){
			case 'A':
				led.action("0", "ON");
				lcd.clear();
				lcd.write_character(data);
			break;
			case 'a' :
				led.action("0", "OFF");
				lcd.clear();
				lcd.write_character(data);
			break;
			case 'B':
				led.action("1", "ON");
				lcd.clear();
				lcd.write_character(data);
			break;
			case 'b':
				led.action("1", "OFF");
				lcd.clear();
				lcd.write_character(data);
			break;
			case 'C':
				led.action("2", "ON");
				lcd.clear();
				lcd.write_character(data);
			break;
			case 'c':
				led.action("2", "OFF");
				lcd.clear();
				lcd.write_character(data);
			break;
			}
		}
		data=0;
	}
}
