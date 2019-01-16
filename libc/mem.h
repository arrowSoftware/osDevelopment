#ifndef _MEM_H_
#define _MEM_H_

#include "../cpu/types.h"

void memoryCopy(u8 *argSource, u8 *argDestination, int argNumBytes);
void memorySet(u8 *argDestination, u8 argValue, u32 argLength);

#endif /* _MEM_H_ */
