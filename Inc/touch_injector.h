/*
 * touch_injector.h
 *
 *  Created on: 21 αιεπι 2017
 *      Author: omershv
 */

#ifndef INC_TOUCH_INJECTOR_H_
#define INC_TOUCH_INJECTOR_H_

enum injection_types
{
	INJECTION_APP,
	INJECTION_PHOTO,
	INJECTION_URL,
	INJECTION_GARBAGE
};


typedef const uint8_t* (*injector_action)(uint8_t);
typedef void (*injector_initer)(void);
typedef void (*injector_destroyer)(void);

struct injection_scheme
{
	injector_action injection_action;
	injector_initer injection_init;
	injector_destroyer injection_destroy;
};


void base_injector_init(enum injection_types type);
void base_injector_destroy();
int base_injector_mem_read();

#endif /* INC_TOUCH_INJECTOR_H_ */
