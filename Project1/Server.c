#include "Server.h"
#include "Card.h"
#include <string.h>

#pragma warning (disable : 4996)

#define _CRT_SECURE_NO_DEPRECATE

uint8_t k;
void fill_array(void) {
	uint8_t* x;
	for (int i = 0; i < 255; i++) {
		x = Generate_PAN();
		for (int j = 0; j < 17; j++) {
			ST_accountsDB_t[i][j] = *(x + j);
		}
	}
	
	for (int i = 0; i < 255; i++) {
		printf("ST_accountsDB_t[%d] =\t", i);
		printf("Amount = %f\t", ST_accountsAmount_t[i]);
		for (int j = 0; j < 17; j++) {
			printf("%d", ST_accountsDB_t[i][j]);

		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

void fill_account_amount(void) {
	srand(time(0)); //current time as seed of random number generator
	for (int i = 0; i < 255; i++) {
		ST_accountsAmount_t[i] = rand() % (10000 + 1);
	}
	//ST_accountsAmount_t[18] = *transData;
}



uint8_t recieveTransactionData(float *termdata, uint8_t* cardData) {
	int buf = 0 , sym = 0;
	buf = isValidAccount(cardData);
	if (buf == 2) {
		printf("This Card is Stolen");
		return DECLINED_STOLEN_CARD;
	}
	buf = saveTransaction(termdata);
	if (buf == 1) {
		printf("Saving failed");
		return INTERNAL_SERVER_ERROR;
	}
	buf = isAmountAvailable(termdata);
	if (buf == 4) {
		printf("DECLINED_INSUFFECIENT_FUND");
		return DECLINED_INSUFFECIENT_FUND;
	}
	ST_accountsAmount_t[k] = ST_accountsAmount_t[k] - *termdata;
	printf("The remaining Amount is %f\n",ST_accountsAmount_t[k]);
	return APPROVED;
}

uint8_t isValidAccount(uint8_t* cardData) {
	int flag = 0;
	for (int j = 0; j < 17; j++) {
		//printf("Card Data is %d",cardData[j]);
	}
	for (int i = 0; i < 255; i++) {
		for (int j = 0; j < 17; j++) {
			if (ST_accountsDB_t[i][16-j] == cardData[j]) {
				flag++;
				//printf("flag = %d \n", flag);
			}
		}
		//printf("i = %d \n", i);
		if (flag == 17){
			k = i;
			break;
		}
		else {
			flag = 0;
		}
	}
	//printf("flag = %d \n", flag);
	if (flag == 17) {
		return ok;
	}
	else {
		return DECLINED_STOLEN_CARD;
	}
}

uint8_t isAmountAvailable(float* termData) {
	
	//printf("k is %d\n",k);

	//printf("trans amount is %f\n", *termData);

	if (*termData <= ST_accountsAmount_t[k]) {
		return ok;
	}
	else {
		return LOW_BALANCE;
	}
}
uint8_t saveTransaction(float* transData) {
	uint32_t seq_num = 1000 , k = 0 , flag = 0;

	if (k == 254) {
		flag = 1;
	}
	else {
		transaction[k][0] = seq_num;
		transaction[k][1] = *transData;

		int x = isAmountAvailable(transData);
		if (x == 0) {
			transaction[k][2] = APPROVED;
		}
		else
		{
			transaction[k][2] = DECLINED_INSUFFECIENT_FUND;
		}
	}
	k++;
	seq_num++;

	if (flag == 0) {
		return ok;
	}
	else
	{
		return SAVING_FAILED;
	}
}

uint8_t getTransaction(uint32_t transactionSequenceNumber, uint8_t* transData) {
	int flag = 0;
	for (int i = 0; i < 255; i++) {
		if (transaction[i][0] == transactionSequenceNumber) {
			flag = 1;
			printf("\ntransaction num % d = % d \t", transactionSequenceNumber, transaction[i][1]);
			if (transaction[i][2] == APPROVED) {
				printf("Approved\n");
			}
			else {
				printf("Declined\n");
			}
		}
	}
	if (flag == 1) {
		return ok;
	}
	else {
		return TRANSACTION_NOT_FOUND;
	}
}
