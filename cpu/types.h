#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

#define LOW_16(argAddress) (uint16_t)((argAddress) & 0xFFFF)
#define HIGH_16(argAddress) (uint16_t)(((argAddress) >> 16) & 0xFFFF)

#endif /* _TYPES_H_ */
