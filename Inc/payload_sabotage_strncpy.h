#include "payload_auto_defs.h"

#define OVERRUN_VALUE MOV_X2_0xFFFFFFFFFFFFFFFF
#define OVERRUN_ADDR 0x0C + STRNCPY_FROM_USER_DIVIDED

#include "payload_overrun_common.h"