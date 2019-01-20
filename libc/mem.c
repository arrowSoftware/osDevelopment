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

#include "mem.h"

void memoryCopy(uint8_t *argSource, uint8_t *argDestination, int argNumBytes)
{
    int i;

    for (i = 0; i < argNumBytes; i++)
    {
        *(argDestination + i) = *(argSource + i);
    }
}

void memorySet(uint8_t *argDestination, uint8_t argValue, uint32_t argLength)
{
    uint8_t *temp = argDestination;

    for (; argLength != 0; argLength--)
    {
        *temp++ = argValue;
    }
}

/* This should be computed at link time, but a hardcoded value is
 * fine for now.  Remember out kernel starts at 0x1000 as defined on the Makefile
 */
 uint32_t freeMemAddr = 0x10000;

 /* Implementation is just a pointer to some free memory which keeps growing. */
 uint32_t kmalloc(size_t argSize, int argAlign, uint32_t *argPhysicalAddr)
 {
     uint32_t returnAddr;

     /* Pages are aligned to 4K, or 0x1000 */
     if (argAlign == 1 && (freeMemAddr & 0xFFFFF000))
     {
         freeMemAddr &= 0xFFFFF000;
         freeMemAddr += 0x1000;
     }

     /* Save also the physical address. */
     if (argPhysicalAddr)
     {
         *argPhysicalAddr = freeMemAddr;
     }

     returnAddr = freeMemAddr;
     freeMemAddr += argSize;
     return returnAddr;
 }
