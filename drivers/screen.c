#include "screen.h"
#include "ports.h"
#include "../kernel/utils.h"

int printChar(char argC, int argCol, int argRow, char argAttr);
int getCursorOffset();
void setCursorOffset(int argOffset);
int getOffset(int argCol, int argRow);
int getOffsetRow(int argOffset);
int getOffsetCol(int argOffset);

void clearScreen()
{
    int screenSize = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (u8 *)VIDEO_ADDRESS;

    for (i = 0; i < screenSize; i++)
    {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }

    setCursorOffset(getOffset(0, 0));
}

/*
 * Print a message on the specified location, if col, row are negative it will
 * print at the current offset.
 */
void kprintAt(char *argMessage, int argCol, int argRow)
{
    /* Set cursor if col, row are negative. */
    int offset;
    int i = 0;

    if (argCol >= 0 && argRow >= 0)
    {
        offset = getOffset(argCol, argRow);
    }
    else
    {
        offset = getCursorOffset();
        argRow = getOffsetRow(offset);
        argCol = getOffsetCol(offset);
    }

    /* Loop through the message and print it. */
    while (argMessage[i] != 0)
    {
        offset = printChar(argMessage[i++], argCol, argRow, WHITE_ON_BLACK);

        /* compute row, col for next interation. */
        argRow = getOffsetRow(offset);
        argCol = getOffsetCol(offset);
    }
}

void kprint(char *argMessage)
{
    kprintAt(argMessage, -1, -1);
}


/* PRIVATE KERNEL FUNCTIONS. */

/*
 * Innermost print function for our kernel, directly accesses the video memory
 *
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */
 int printChar(char argC, int argCol, int argRow, char argAttr)
{
    u8 *videoMemory =  (u8 *)VIDEO_ADDRESS;
    int offset;
    int i;
    char *lastLine;

    if (!argAttr)
    {
        argAttr = WHITE_ON_BLACK;
    }

    /* Error control: print a red "E" if the coords aren't right. */
    if (argCol >= MAX_COLS || argRow >= MAX_ROWS)
    {
        videoMemory[2 * (MAX_COLS) * (MAX_ROWS) - 2] = 'E';
        videoMemory[2 * (MAX_COLS) * (MAX_ROWS) - 1] = RED_ON_WHITE;
        return getOffset(argCol, argRow);
    }

    if (argCol >= 0 && argRow >= 0)
    {
        offset = getOffset(argCol, argRow);
    }
    else
    {
        offset = getCursorOffset();
    }

    if (argC == '\n')
    {
        argRow = getOffsetRow(offset);
        offset = getOffset(0, argRow + 1);
    }
    else
    {
        videoMemory[offset] = argC;
        videoMemory[offset + 1] = argAttr;
        offset += 2;
    }

    /* Check if the offset is over the screen size and scroll. */
    if (offset >= MAX_ROWS * MAX_COLS * 2)
    {
        for (i = 0; i < MAX_ROWS; i++)
        {
            memoryCopy(getOffset(0, i) + VIDEO_ADDRESS, getOffset(0, i - 1) + VIDEO_ADDRESS, MAX_COLS * 2);
        }

        lastLine = getOffset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++)
        {
            lastLine[i] = 0;
        }

        offset -= 2 * MAX_COLS;
    }

    setCursorOffset(offset);
    return offset;
}

 int getCursorOffset()
{
    int offset;

    /*
     * Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    portByteOut(SCREEN_CONTROL_REG, 14);
    offset = portByteIn(SCREEN_DATA_REG) << 8;

    portByteOut(SCREEN_CONTROL_REG, 15);
    offset += portByteIn(SCREEN_DATA_REG);

    return offset * 2; /* Position * size of character cell. */
}

 void setCursorOffset(int argOffset)
{
    argOffset /= 2;
    portByteOut(SCREEN_CONTROL_REG, 14);
    portByteOut(SCREEN_DATA_REG, (u8)(argOffset >> 8));
    portByteOut(SCREEN_CONTROL_REG, 15);
    portByteOut(SCREEN_DATA_REG, (u8)(argOffset & 0xFF));
}

 int getOffset(int argCol, int argRow)
{ return 2 * (argRow * MAX_COLS + argCol); }

 int getOffsetRow(int argOffset)
{ return argOffset / (2 * MAX_COLS); }

 int getOffsetCol(int argOffset)
{ return (argOffset - (getOffsetRow(argOffset) * 2 * MAX_COLS)) / 2; }
