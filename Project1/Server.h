#pragma once
#include"Std_type.h"

uint8_t recieveTransactionData(float* termdata, uint8_t* cardData);
uint8_t isValidAccount(uint8_t* cardData);
uint8_t isAmountAvailable(float* termData);
uint8_t saveTransaction(float* transData);
uint8_t getTransaction(uint32_t transactionSequenceNumber, uint8_t* transData);


void fill_account_amount(void);
void fill_array(void);


typedef struct ST_transaction_t
{
	uint8_t cardHolderData;
	uint8_t terminalData;
	uint8_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction;

uint8_t ST_accountsDB_t[255][20];
float ST_accountsAmount_t[255];
uint32_t transaction[255][3];

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
	ok, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

