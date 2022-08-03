#pragma once
#include "Std_type.h"

uint8_t getCardHolderName(uint8_t* cardData);
uint8_t getCardExpiryDate(uint8_t* cardData);
uint8_t getCardPAN(uint8_t* cardData);

void TransformToInt(uint8_t* cardData);
uint8_t *Generate_PAN(void);
uint8_t PAN_LUHN[20];

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

ST_cardData_t User_1;

typedef enum EN_cardError_t
{
	OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

