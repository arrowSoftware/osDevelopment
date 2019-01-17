#ifndef _PORTS_H_
#define _PORTS_H_

#include "../cpu/types.h"

/* The Master PIC has command 0x20 and data 0x21 */
/* while the slave has command 0xA0 and data 0xA1. */
#define MASTER_PIC_COMMAND 0x20
#define MASTER_PIC_DATA    0x21
#define SLAVE_PIC_COMMAND  0xA0
#define SLAVE_PIC_DATA     0xA1

uint8_t portByteIn(uint16_t argPort);
void portByteOut(uint16_t argPort, uint8_t argData);

uint16_t portWordIn(uint16_t argPort);
void portWordOut(uint16_t argPort, uint16_t argData);

#endif /* _PORTS_H_ */
