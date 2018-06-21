#ifndef _TOUCH_INJECTION_URL_H_
#define _TOUCH_INJECTION_URL_H_

#include "ArrayOfInjections.h"
#include"touch_injection_macros.h"

/*
 * getInfo(uint8_t c):
 * 	given character c , bring the matching type's data (array) from our database.
 * 	if not found, return null.
 */
const uint8_t* getInfo(uint8_t c);


/*
 * Main function.
 */
const uint8_t* get_injection_URL(uint8_t reg) ;

/*
 * Initialize and destroy.
 */
void init_injector_URL();
void destroy_injection_URL();

#endif
