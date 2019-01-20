/*******************************************************************************
 * File:
 *
 * Description:
 *
 * Members:
 *
 * Modification History:
 *
 ******************************************************************************/

#ifndef _MEM_H_
#define _MEM_H_

#include "../cpu/types.h"
#include <stddef.h>

void memoryCopy(uint8_t *argSource, uint8_t *argDestination, int argNumBytes);
void memorySet(uint8_t *argDestination, uint8_t argValue, uint32_t argLength);

uint32_t kmalloc(size_t argSize, int argAlign, uint32_t *argPhysicalAddr);

#endif /* _MEM_H_ */
