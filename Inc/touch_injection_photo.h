#ifndef _TOUCH_INJECTION_PHOTO_H_
#define _TOUCH_INJECTION_PHOTO_H_

#include "ArrayOfInjections.h"

/*
 * Main function.
 */
const uint8_t* get_injection_photo(uint8_t reg);

/*
 * Destroyer.
 */
void destroy_injection_photo();

#endif
