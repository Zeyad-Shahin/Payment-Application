#include "Std_type.h"
#include "Card.h"
#include "Terminal.h"
#include "Server.h"

//#define _CRT_SECURE_NO_WARNINGS

void CheckCard(uint8_t data) {
	if (data == 0) {
		printf("OK\n");
	}
	else if (data == 1) {
		printf("WRONG_NAME\n");
	}
	else if (data == 2) {
		printf("WRONG_EXP_DATE\n");
	}
	else if (data == 3) {
		printf("WRONG_PAN\n");
	}
	else {
		printf("Error\n");
	}
}

void CheckTerm(uint8_t data) {
	if (data == 0) {
		printf("OK\n");
	}
	else if (data == 1) {
		printf("WRONG_DATE\n");
	}
	else if (data == 2) {
		printf("EXPIRED_CARD\n");
	}
	else if (data == 3) {
		printf("INVALID_CARD\n");
	}
	else if (data == 4) {
		printf("INVALID_AMOUNT\n");
	}
	else if (data == 5) {
		printf("EXCEED_MAX_AMOUNT\n");
	}
	else if (data == 6) {
		printf("INVALID_MAX_AMOUNT\n");
	}
	else {
		printf("Error\n");
	}
}

void checkServer (uint8_t data) {
	if (data == 0) {
		printf("APPROVED\n");
	}
	else if (data == 1) {
		printf("DECLINED_INSUFFECIENT_FUND\n");
	}
	else if (data == 2) {
		printf("DECLINED_STOLEN_CARD\n");
	}
	else if (data == 3) {
		printf("INTERNAL_SERVER_ERROR\n");
	}
	else {
		printf("Error\n");
	}
}

void checkServerError (uint8_t data) {
	if (data == 0) {
		printf("ok\n");
	}
	else if (data == 1) {
		printf("SAVING_FAILED\n");
	}
	else if (data == 2) {
		printf("TRANSACTION_NOT_FOUND\n");
	}
	else if (data == 3) {
		printf("ACCOUNT_NOT_FOUND\n");
	}
	else if (data == 4) {
		printf("LOW_BALANCE\n");
	}

	else {
		printf("Error\n");
	}
}


int appStart(void) {
	uint32_t sequence_num;

	/************************************************************************************************
												Card Module
	**************************************************************************************************/
	
	//************** Taking Name From User ********************//
	do {
		printf("Enter Card Holder Name (Size 20-24) : \n");
		gets(User_1.cardHolderName);

		//********************Check The Name format********************//
		CheckCard(getCardHolderName(User_1.cardHolderName));

	} while (getCardHolderName(User_1.cardHolderName) == 1);


	//************** Taking Date From User ********************//
	do {
		printf("Enter Card Expiry Date (format MM/YY) : \n");
		gets(User_1.cardExpirationDate);

		//************** Check The Date Format  *******************//
		CheckCard(getCardExpiryDate(User_1.cardExpirationDate));

	} while (getCardExpiryDate(User_1.cardExpirationDate));

	//***************Get the Date From Computer ***************//
	getTransactionDate();

	//************** Check The Card Expiration  *******************//
	printf("Card Expiration :");							//printing status
	CheckTerm(isCardExpired(User_1.cardExpirationDate));
	printf("\n");                                          //printing new line

	if (isCardExpired(User_1.cardExpirationDate) == 2) {
		printf("\n");
		return 1;
	}

	//************** Taking PAN From User ********************//
	do {
		printf("Enter PAN (Size 16-19) : \n");
		gets(User_1.primaryAccountNumber);

		//************** Check The PAN Format  *******************//
		CheckCard(getCardPAN(User_1.primaryAccountNumber));

	} while (getCardPAN(User_1.primaryAccountNumber));

	TransformToInt(User_1.primaryAccountNumber);

	//************** Check The card number (Luhn Number)  ****************//
	CheckTerm(isValidCardPAN(User_1.primaryAccountNumber));
	printf("is valid = %d\n", isValidAccount(&User_1.primaryAccountNumber));

	if (isValidCardPAN(User_1.primaryAccountNumber) == 2) {
		printf("\n");
		return 1;
	}

	/************************************************************************************************
											Terminal Module
	**************************************************************************************************/

	//************ Taking Transaction Amount From User ************//
	do {
		printf("Enter Trans Amount : \n");
		scanf_s("%f", &User1.transAmount);
		//************** Check The trans Amount  *******************//
		printf("Transaction Amount :");							//printing status
		CheckTerm(getTransactionAmount(User1.transAmount));
		printf("\n");				//printing new line
	} while (getTransactionAmount(User1.transAmount));

	//************** Set The max trans Amount  *****************//
	User1.maxTransAmount = 7000;
	printf("Max Trans Amount :");							//printing status
	CheckTerm(setMaxAmount(&User1.maxTransAmount));
	printf("\n");				//printing new line

	//************** Check The max trans Amount ****************//
	printf("Is Below Max :");							//printing status
	CheckTerm(isBelowMaxAmount(&User1.transAmount));
	printf("\n");				//printing new line
	if (isBelowMaxAmount(&User1.transAmount) == 5) {
		printf("\nThe transaction amount is greater than max allowed");
		return 1;
	}

	/************************************************************************************************
											Server Module
	**************************************************************************************************/
	
	recieveTransactionData(&User1.transAmount,User_1.primaryAccountNumber);

	printf("Enter seq num : \n");
	scanf_s("%d", &sequence_num);

	getTransaction(sequence_num,&User1.maxTransAmount);
	return 0;
}

