#ifndef _PORTS_H_
#define _PORTS_H_

#include "../cpu/types.h"

/* The Master PIC has command 0x20 and data 0x21 */
/* while the slave has command 0xA0 and data 0xA1. */
#define MASTER_PIC_COMMAND 0x20
#define MASTER_PIC_DATA    0x21
#define SLAVE_PIC_COMMAND  0xA0
#define SLAVE_PIC_DATA     0xA1

u8 portByteIn(u16 argPort);
void portByteOut(u16 argPort, u8 argData);

u16 shortportWordIn(u16 argPort);
void pordWordOut(u16 argPort, u16 argData);

#endif /* _PORTS_H_ */
