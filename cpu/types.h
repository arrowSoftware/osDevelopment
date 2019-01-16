#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

#define LOW_16(argAddress) (u16)((argAddress) & 0xFFFF)
#define HIGH_16(argAddress) (u16)(((argAddress) >> 16) & 0xFFFF)

#endif /* _TYPES_H_ */
