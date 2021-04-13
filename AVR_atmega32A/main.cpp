/*
 * main.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */

#include "peripherals.h"
#include "modules.h"
#include "MCU_Config.h"

KEYPAD buttons;

LCD lcd;

Uint16t ovf=0;

int main (){
	lcd.init();
	buttons.init();
	Uint8t data ;
	while(true){
		data = buttons.read();
		if  (data){
			lcd.clear();
			if (dig_char2dig_number(data)>=0 &&dig_char2dig_number(data)<10){
				lcd.write_number(dig_char2dig_number(data));
			}else {
				lcd.write_character(data);
			}

		}

	}
}

