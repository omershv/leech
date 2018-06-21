/*
 * touch_logger_with_timer.h
 *
 *  Created on: 21 αιεπι 2017
 *      Author: omershv
 */

#ifndef INC_TOUCH_LOGGER_WITH_TIMER_H_
#define INC_TOUCH_LOGGER_WITH_TIMER_H_

uint8_t logger_with_timer_was_timer_triggered();
uint8_t logger_with_timer_was_woken();
uint8_t logger_with_timer_was_reboot();
uint8_t logger_with_timer_completed();
void logger_with_timer_init(uint32_t timer_timeout, uint8_t stop_on_reboot);
void logger_with_timer_destroy();

#endif /* INC_TOUCH_LOGGER_WITH_TIMER_H_ */
