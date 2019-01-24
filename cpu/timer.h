/*******************************************************************************
 * File:
 *  timer.h
 *
 * Description:
 *  This file contains code to start a registers an ISR with the cpu timer.
 *
 * Members:
 *  initTimer()
 *
 * Todo:
 *  None.
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#include "../cpu/types.h"

/*******************************************************************************
 * Function:
 *  initTimer
 *
 * Description:
 *  This function sets up and starts the Programmable Interval Timer (PIT).
 *
 * Arguments:
 *  argFrequency: The frequency at which to call the ISR.
 *
 * Returns:
 *  None.
 *
 ******************************************************************************/
void initTimer(uint32_t argFrequency);

#endif /* _TIMER_H_ */
