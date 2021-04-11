/*
 * main.cpp
 *
 *  Created on: Apr 4, 2021
 *      Author: khaled
 */
#include <string.h>
#include "DRIVERS.h"
#include "UI.h"


char password[] = "00000";
Uint8t state_machine = 0;

LCD lcd;
KEYPAD buttons;
int main (){
	lcd.init();
	buttons.init();

	lcd.write_string((Uint8t*) "ADMIN PASSWORD :");
	lcd.cursor_position(1, 2);
	while(true){

		/********** Check Auth **********/
		if (state_machine==0){//right password
			if (read_auth(password, &lcd, &buttons)){
				lcd.clear();
				lcd.write_string((Uint8t*)"Login Successfully");
				_delay_ms(2000);
				state_machine = 1;
			}else { //wrong password
				lcd.clear();
				lcd.write_string((Uint8t*)"Wrong Password");
				_delay_ms(2000);
				lcd.clear();
				lcd.write_string((Uint8t*) "ADMIN PASSWORD :");
				lcd.cursor_position(1, 2);
			}
		}
		/**********END**********/

	}
}
