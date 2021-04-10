/*
 * applib.h
 *
 *  Created on: Apr 5, 2021
 *      Author: khaled
 */

#ifndef APPLIB_H_
#define APPLIB_H_

#include "CPU_CONFIG.h"

Uint32t expo (Uint8t base , Uint8t power);
Uint8t* int2str (Uint32t org_num);
Uint32t digits2number (Uint8t *num , Uint8t len);



#endif /* APPLIB_H_ */
