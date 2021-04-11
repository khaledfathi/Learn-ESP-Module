/*
 * UI.cpp
 *
 *  Created on: Apr 11, 2021
 *      Author: khaled
 */

#include <string.h>
#include "UI.h"


bool read_auth (char* password , LCD* lcd, KEYPAD *but){
	Uint8t pw[6] , i=0 ,wating=1 , data;
	lcd->write_string((Uint8t*)'*');
	while(wating){
		data= but->read();
		if( data != 16){
			pw[i] = data+48;//data is number +48 it'll convert it to same number as character in ascii
			lcd->write_character('*');
			i++;
			if (i>4)wating=0;
		}
	}
	pw[5]='\0'; //null to end of string

	if (!strcmp(password , (char*)pw)){
		return true;
	}else {
		return false;
	}

}

