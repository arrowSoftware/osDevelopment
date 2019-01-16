#ifndef _UTILS_H_
#define _UTILS_H_

#include "../cpu/types.h"

void memoryCopy(char *argSource, char *argDestination, int argNumBytes);
void memorySet(u8 *argDestination, u8 argValue, u32 argLength);
void intToAscii(int argNumber, char argStr[]);
void reverse(char argStr[]);
int strlen(char argStr[]);

#endif /* _UTILS_H_ */
