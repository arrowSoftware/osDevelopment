/*******************************************************************************
 * File:
 *  types.h
 *
 * Description:
 *  This files contains standard types and function to work with types.
 *
 * Members:
 *  LOW_16
 *  HIGH_16
 *
 * Todo:
 *  Make this stand alone and replace stdint with typedefs for each int...
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/
#ifndef _TYPES_H_
#define _TYPES_H_

/*#include <stdint.h>*/

typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;

/* This will return the lower 16 bits of a 32 bit address. */
#define LOW_16(argAddress) (uint16_t)((argAddress) & 0xFFFF)

/* This will return the upper 16 bits of a 32 bit address. */
#define HIGH_16(argAddress) (uint16_t)(((argAddress) >> 16) & 0xFFFF)

#endif /* _TYPES_H_ */
