/*
 * applib.h
 *
 *  Created on: Apr 5, 2021
 *      Author: khaled
 */

#ifndef APPLIB_H_
#define APPLIB_H_

#include "MCU_Config.h"

//expo integer
//Parameter : base = number , power = expo number
Uint32t expo (Uint8t base , Uint8t power);

//convert integer to string
//Parameter : org_num = unsigned number
Uint8t* int2str (Uint32t org_num);

//convert array of digits [0~9] to integer
//Parameter : num = array of digits , len = length of array
Uint32t digits2number (Uint8t *num , Uint8t len);



#endif /* APPLIB_H_ */
