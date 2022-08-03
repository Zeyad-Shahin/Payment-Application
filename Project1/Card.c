#include "Std_type.h"
#include "Card.h"

uint8_t getCardHolderName(uint8_t* cardData) {

	uint8_t size = 0, i = 0;


//************** Calculate the Size of Name *************//

	while (cardData[i] != '\0') {
		size++;
		i++;
	}

//************** Check the Size of Name *************//

	if (size <= 24 && size >= 20) {return OK;}
	else { return WRONG_NAME; }
}

uint8_t getCardExpiryDate(uint8_t* cardData) {

	uint8_t size = 0, i = 0;

	//************** Calculate the Size of Date *************//

	while (cardData[i] != '\0') {
		size++;
		i++;
	}

	//************** Check the Size of Date *************//

	if (size == 5 && cardData[2] == '/') { return OK; }
	else { return WRONG_EXP_DATE;}
}

uint8_t getCardPAN(uint8_t* cardData) {

	uint8_t size = 0, i = 0;

	//************** Calculate the Size of PAN *************//

	while (cardData[i] != '\0') {
		size++;
		i++;
	}

	//************** Check the Size of PAN *************//

	if (size <= 19 && size >= 16 ) { return OK; }
	else { return WRONG_PAN;}
}
uint8_t* Generate_PAN(void) {
	uint8_t sum = 0,buff = 0;

	for (int j = 0; j < 16; j++) {
		PAN_LUHN[j] = (rand() % (10)) ;
		//printf("%d", PAN_LUHN[j]);
	}
	//printf("\n");
	for (int j = 0; j < 16; j++) {
		if (j%2 != 0) {
			if (PAN_LUHN[j]*2 / 10 != 0) {
				buff = (PAN_LUHN[j]*2 / 10) + (PAN_LUHN[j]*2 % 10);
			}
			else
			{
				buff = PAN_LUHN[j]*2;
			}
			sum = sum + buff;
			//printf("sum H = %d \n", sum);
		}
		else
		{
			sum = sum + PAN_LUHN[j];
			//printf("sum = %d \n", sum);
		}
	}
	//printf("sum = %d \n",sum);
	if (sum == 0) {
		PAN_LUHN[16] = 0;
	}
	else {
		PAN_LUHN[16] = 10 - (sum % 10);
	}


	return &PAN_LUHN[0];
}

void TransformToInt(uint8_t* cardData) {

	uint8_t size = 0, i = 0;
	uint8_t arr[20] = {0};

	//************** Calculate the Size of PAN *************//

	while (cardData[i] != '\0') {
		arr[i] = cardData[i] - '0';
		i++;
	}
	cardData[i] = '%';
	size = i;
	i--;
	for (int j = 0; j < size; j++) {
		cardData[j] = arr[i];
		//printf("arr[%d] = %d , Carddate[%d] = %d\n",i,arr[i],j,cardData[j]);
		i--;
	}

	for (int j = 0; j < size; j++) {
		//printf("carddate = %d\n",cardData[j]);
	}
	//printf("\n");

}
