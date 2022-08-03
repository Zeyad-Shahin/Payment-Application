#include <stdio.h>

#include "Std_type.h"
#include "App.h"



//#define _CRT_SECURE_NO_WARNINGS





int main() {

	srand(time(0)); //current time as seed of random number generator

	/***************Create file with accounts ******************/

	fill_account_amount();
	fill_array();


	while (1) {
		appStart();
	}

	return 0;
}