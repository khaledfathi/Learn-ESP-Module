/*
 * applib.cpp
 *
 *  Created on: Apr 5, 2021
 *      Author: khaled
 *
 *	Functions
 */

#include "applib.h"
#include "MCU_Config.h"


Uint32t expo (Uint8t base , Uint8t power){
	Uint32t res=base;
	for (;power>1;power--){
		res*=base;
	}
	return res;
}
Uint8t* int2str (Uint32t org_num){
	//counting digits
	Uint32t num = org_num ;
	Uint8t i=10 , counter=0;
	Uint32t tmp ;
	while((i/10)!=0){
		tmp = num/10 ;
		num=tmp;
		i=tmp;
		if (tmp)counter++;
	}
	counter++;

	//convert int to digits and save it in array
	Uint8t res_arr[counter];
	num= org_num ;
	for (i=0;i<counter;i++){
		tmp=num/10;
		res_arr[i] =num-(tmp*10);
		num=tmp;
	}

	//convert digits array to string
	static Uint8t res[20]; // max digits is 20 | can not use static without constant size
	Uint8t num_str[]={'1','2','3','4','5','6','7','8','9','0'};
	Uint8t num_int[]={1,2,3,4,5,6,7,8,9,0};
	Uint8t j ;
	for (i=0; i<counter ; i++){
		for (j=0; j<10; j++){
			if(num_int[j]==res_arr[i]){
				res[i] = num_str[j];
			}
		}
	}

	//reverse array
	Uint8t start=0 , end=counter-1 , temp; //counter-1 cuz laste elment is NULL
	while (start<end){
		temp= res[start];
		res[start]=res[end];
		res[end]=temp;
		start++;
		end--;
	}

	res[i]='\0';
	return res;
}

Uint32t digits2number (Uint8t *num , Uint8t len){
	//parameter = num[array of numbers] , num_length[size of array]
	Uint32t factor= expo(10,(len-1)), temp[len];

	Uint8t i;
	for (i=0 ; i<len;i++){
		temp[i]= num[i]*factor;
		factor/=10;
	}

	Uint32t res=0 ;

	for (i=0; i<len; i++){
		res+= temp[i];
	}
	return res;
}

