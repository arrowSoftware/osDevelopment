/*******************************************************************************
 * File:
 *  mem.h
 *
 * Description:
 *  This file contains functions to work with memory.
 *
 * Members:
 *  memcpy
 *  memset
 *
 * Todo:
 *  Add memcmp, malloc, free, calloc
 *
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/21/19    T.Gajewski   Initial version.
 ******************************************************************************/
#ifndef _MEM_H_
#define _MEM_H_

#include "../cpu/types.h"
#include <stddef.h>

/*******************************************************************************
 * Function:
 *  memcpy
 *
 * Description:
 *  Allocates a block of memory for an array of num elements, each of them size
 *  bytes long, and initializes all its bits to zero.
 *
 * Arguments:
 *
 *
 * Returns:
 *
 *
 ******************************************************************************/
void memcpy(uint8_t *argSource, uint8_t *argDestination, int argNumBytes);

/*******************************************************************************
 * Function:
 *  memset
 *
 * Description:
 *
 *
 * Arguments:
 *
 *
 * Returns:
 *
 *
 ******************************************************************************/
void memset(uint8_t *argDestination, uint8_t argValue, uint32_t argLength);


/*******************************************************************************
 * Function:
 *  malloc
 *
 * Description:
 *  Allocates a block of size bytes of memory, returning a pointer to the
 *  beginning of the block. The content of the newly allocated block of memory
 *  is not initialized, remaining with indeterminate values.
 *
 * Arguments:
 *  argSize: Size of the memory block, in bytes.
 *
 * Returns:
 *  A pointer to the memory block allocated by the function.
 *
 ******************************************************************************/
void *malloc(size_t argSize);

/*******************************************************************************
 * Function:
 *  calloc
 *
 * Description:
 *  Allocates a block of memory for an array of num elements, each of them size
 *  bytes long, and initializes all its bits to zero.
 *
 * Arguments:
 *  argSize: Size of the memory block, in bytes.
 *
 * Returns:
 *  A pointer to the memory block allocated by the function.
 *
 ******************************************************************************/
void *calloc(size_t argNumber, size_t argSize);

/*******************************************************************************
 * Function:
 *  free
 *
 * Description:
 *
 *
 * Arguments:
 *
 *
 * Returns:
 *
 *
 ******************************************************************************/
void free(void *argAddr);

uint32_t kmalloc(size_t argSize, int argAlign, uint32_t *argPhysicalAddr);

#endif /* _MEM_H_ */
