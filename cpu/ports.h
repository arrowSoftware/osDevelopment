/*******************************************************************************
 * File:
 *  ports.h
 *
 * Description:
 *  This files contains code used to write and read from the I/O ports.
 *
 * Members:
 *  portByteIn(uint16_t argPort);
 *  portByteOut(uint16_t argPort, uint8_t argData);
 *  portWordIn(uint16_t argPort);
 *  portWordOut(uint16_t argPort, uint16_t argData);
 *
 * Todo:
 *  None.
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/

#ifndef _PORTS_H_
#define _PORTS_H_

#include "../cpu/types.h"

/* PIT COMMAND DATA;
Bits   Usage
6 & 7  Select channel :
        0 0 = Channel 0
        0 1 = Channel 1
        1 0 = Channel 2
        1 1 = Read-back command (8254 only)
4 & 5  Access mode :
        0 0 = Latch count value command
        0 1 = Access mode: lobyte only
        1 0 = Access mode: hibyte only
        1 1 = Access mode: lobyte/hibyte
1 to 3  Operating mode :
        0 0 0 = Mode 0 (interrupt on terminal count)
        0 0 1 = Mode 1 (hardware re-triggerable one-shot)
        0 1 0 = Mode 2 (rate generator)
        0 1 1 = Mode 3 (square wave generator)
        1 0 0 = Mode 4 (software triggered strobe)
        1 0 1 = Mode 5 (hardware triggered strobe)
        1 1 0 = Mode 2 (rate generator, same as 010b)
        1 1 1 = Mode 3 (square wave generator, same as 011b)
0       BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD
*/
#define PIT_CHAN_0_DATA  0x40 /* Channel 0 data port (read/write) */
#define PIT_CHAN_1_DATA  0x41 /* Channel 1 data port (read/write) */
#define PIT_CHAN_2_DATA  0x42 /* Channel 2 data port (read/write) */
#define PIT_COMMAND      0x43 /* Mode/Command register (write only, a read is ignored) */
#define PIT_CMD_CHAN_0   0x0  /* 00000000 */
#define PIT_CMD_LO_HI    0x30 /* 00110000 */
#define PIT_CMD_SQR_WAVE 0x6  /* 00000110 */
#define PIT_CMD_BIN_MODE 0x0  /* 00000000 */


/* The Master PIC has command 0x20 and data 0x21 */
/* while the slave has command 0xA0 and data 0xA1. */
#define MASTER_PIC_COMMAND 0x20
#define MASTER_PIC_DATA    0x21
#define SLAVE_PIC_COMMAND  0xA0
#define SLAVE_PIC_DATA     0xA1

/*******************************************************************************
 * Function:
 *  portByteIn
 *
 * Description:
 *  This runtions reads a byte from a specified I/O port.
 *
 * Arguments:
 *  argPort: The I/O port to read from.
 *
 * Returns:
 *  The data from the read of the I/O port.
 *
 ******************************************************************************/
uint8_t portByteIn(uint16_t argPort);

/*******************************************************************************
 * Function:
 *  portByteOut
 *
 * Description:
 *  This function writes a byte to a specified I/O port.
 *
 * Arguments:
 *  argPort: Which port to write to.
 *  argData: The data to write.
 *
 * Returns:
 *  None.
 *
 ******************************************************************************/
void portByteOut(uint16_t argPort, uint8_t argData);

/*******************************************************************************
 * Function:
 *  portWordIn
 *
 * Description:
 *  This runtions reads a word from a specified I/O port.
 *
 * Arguments:
 *  argPort: The I/O port to read from.
 *
 * Returns:
 *  The data from the read of the I/O port.
 *
 ******************************************************************************/
uint16_t portWordIn(uint16_t argPort);

/*******************************************************************************
 * Function:
 *  portWordOut
 *
 * Description:
 *  This function writes a word to a specified I/O port.
 *
 * Arguments:
 *  argPort: Which port to write to.
 *  argData: The data to write.
 *
 * Returns:
 *  None.
 *
 ******************************************************************************/
void portWordOut(uint16_t argPort, uint16_t argData);

#endif /* _PORTS_H_ */
