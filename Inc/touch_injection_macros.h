/*
 * touch_injection_macros.h
 *
 *  Created on: Jun 18, 2017
 *      Author: User
 */

#ifndef INC_TOUCH_INJECTION_MACROS_H_
#define INC_TOUCH_INJECTION_MACROS_H_

#define UNIT (255) // Default 1 -> mili
#define CONVERT_TO_UNIT(V) (((V)*UNIT)/100)
#define NORAML_DELAY CONVERT_TO_UNIT(15)		// 10 mili seconds between 2 messages.
#define GUI_DELAY CONVERT_TO_UNIT(100)
#define INTERNET_PLAYSTORE_LOADING_DELAY CONVERT_TO_UNIT(100)
#define DOWNLOADING_DELAY CONVERT_TO_UNIT(100)
#define END_SWIPE_DELAY CONVERT_TO_UNIT(100)

#endif /* INC_TOUCH_INJECTION_MACROS_H_ */
