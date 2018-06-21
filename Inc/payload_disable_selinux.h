#include "payload_auto_defs.h"

#define ZEROS 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define OVERRUN_VALUE ZEROS
#define OVERRUN_ADDR SELINUX_ENFORCING_DIVIDED

#include "payload_overrun_common.h"
