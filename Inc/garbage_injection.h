#ifndef _GARBAGE_INJECTION_H_
#define _GARBAGE_INJECTION_H_


/*
 * Main function.
 */
const uint8_t* get_injection_garbage(uint8_t reg) ;

/*
 * Initialize and destroy.
 */
void init_injection_garbage();
void destroy_injection_garbage();

#endif
