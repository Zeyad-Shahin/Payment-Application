#include"Std_type.h"
#include "Terminal.h"
#include <time.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

uint8_t current_date[6];
uint8_t trans_date[11];



void getTransactionDate(void) {

	time_t t;   // not a primitive datatype
	time(&t);
	char str[26];
	ctime_s(str, sizeof str, &t);

	printf("\nThis program has been writeen at (date and time): %s", str);
	
	trans_date[0] = str[8];
	trans_date[1] = str[9];

	if (str[4] == 'J' && str[5] == 'a' && str[6] == 'n') {
		trans_date[3] = '0';
		trans_date[4] = '1';

		current_date[3] = '0';
		current_date[4] = '1';
	}
	else if (str[4] == 'F' && str[5] == 'e' && str[6] == 'b') {
		trans_date[3] = '0';
		trans_date[4] = '2';

		current_date[3] = '0';
		current_date[4] = '2';
	}
	else if (str[4] == 'M' && str[5] == 'a' && str[6] == 'r') {
		trans_date[3] = '0';
		trans_date[4] = '3';

		current_date[3] = '0';
		current_date[4] = '3';
	}
	else if (str[4] == 'A' && str[5] == 'p' && str[6] == 'r') {
		trans_date[3] = '0';
		trans_date[4] = '4';

		current_date[3] = '0';
		current_date[4] = '4';
	}
	else if (str[4] == 'M' && str[5] == 'a' && str[6] == 'y') {
		trans_date[3] = '0';
		trans_date[4] = '5';

		current_date[3] = '0';
		current_date[4] = '5';
	}
	else if (str[4] == 'J' && str[5] == 'u' && str[6] == 'n') {
		trans_date[3] = '0';
		trans_date[4] = '6';

		current_date[3] = '0';
		current_date[4] = '6';
	}
	else if (str[4] == 'J' && str[5] == 'u' && str[6] == 'l') {
		trans_date[3] = '0';
		trans_date[4] = '7';

		current_date[3] = '0';
		current_date[4] = '7';
	}
	else if (str[4] == 'A' && str[5] == 'u' && str[6] == 'g') {
		trans_date[3] = '0';
		trans_date[4] = '8';

		current_date[3] = '0';
		current_date[4] = '8';
	}
	else if (str[4] == 'S' && str[5] == 'e' && str[6] == 'p') {
		trans_date[3] = '0';
		trans_date[4] = '9';

		current_date[3] = '0';
		current_date[4] = '9';
	}
	else if (str[4] == 'O' && str[5] == 'c' && str[6] == 't') {
		trans_date[3] = '1';
		trans_date[4] = '0';

		current_date[3] = '1';
		current_date[4] = '0';
	}
	else if (str[4] == 'N' && str[5] == 'o' && str[6] == 'v') {
		trans_date[3] = '1';
		trans_date[4] = '1';

		current_date[3] = '1';
		current_date[4] = '1';
	}
	else if (str[4] == 'D' && str[5] == 'e' && str[6] == 'c') {
		trans_date[3] = '1';
		trans_date[4] = '2';

		current_date[3] = '1';
		current_date[4] = '2';
	}

	trans_date[2] = '/';
	trans_date[5] = '/';
	current_date[2] = '/';
	
	trans_date[6] = str[20];
	trans_date[7] = str[21];

	current_date[0] = str[22];
	current_date[1] = str[23];
	trans_date[8] = str[22];
	trans_date[9] = str[23];

	current_date[5] = '\0';
	trans_date[10] = '\0';

	printf("\nTrans Date: %s\n", trans_date);
}
uint8_t isCardExpired(uint8_t *cardData){
	uint8_t state[6] = {0};
	sint8_t x;
	state[0] = cardData[3];
	state[1] = cardData[4];
	state[2] = '/';
	state[3] = cardData[0];
	state[4] = cardData[1];
	state[5] = '\0';
	
	x = strcmp(state, current_date);

	if (x > 0) {
		return Ok;
	}
	else {
		return EXPIRED_CARD;
	}
}
uint8_t isValidCardPAN(uint8_t* cardData) {
	int sum = 0, res , buff = 0 , j = 0 ;
	//printf("start = %d \n", cardData[0]);
	while (*(cardData + j) != '%') {
		if (j % 2 != 0) {
			if (*(cardData + j) * 2 / 10 != 0) {
				buff = (*(cardData + j) * 2 / 10) + (*(cardData + j) * 2 % 10);
			}
			else {
				buff = *(cardData + j)*2;
			}
			sum = sum + buff;
			//printf("sum H = %d \n", sum);
		}
		else
		{
			sum = sum + *(cardData + j);
			//printf("sum = %d \n", sum);

		}
		j++;
	}
	res = sum % 10;
	//printf("Sum = %d \n", sum);
	//printf("res = %d \n",res);

	if (res == 0) {
		return Ok;
	}
	else {
		return INVALID_CARD;
	}
}

uint8_t getTransactionAmount(float termData) {
	if (termData <= 0) {
		return INVALID_AMOUNT;
	}
	else
	{
		return Ok;
	}

}

uint8_t isBelowMaxAmount(float* trans) {
	if (*trans <= User1.maxTransAmount) {
		return Ok;
	}
	else {
		return EXCEED_MAX_AMOUNT;
	}
}

uint8_t setMaxAmount(float* transData) {
	if (*transData <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return Ok;
	}
}