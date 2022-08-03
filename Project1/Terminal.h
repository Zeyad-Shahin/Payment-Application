#pragma once
#include"Std_type.h"

void getTransactionDate(void);
uint8_t isCardExpired(uint8_t *cardData);
uint8_t isValidCardPAN(uint8_t* cardData);
uint8_t getTransactionAmount(float termData);
uint8_t isBelowMaxAmount(float* trans);
uint8_t setMaxAmount(float* transData);

typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

ST_terminalData_t User1;

typedef enum EN_terminalError_t
{
	Ok, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

