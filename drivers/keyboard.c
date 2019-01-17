#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define BACKSPACE 0x0E
#define ENTER     0x1C

static char keyBuffer[256];

#define SC_MAX 57
const char *scName[] =
{
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
    "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
    "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
    "/", "RShift", "Keypad *", "LAlt", "Spacebar"
};

const char scAscii[] =
{
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
    'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

static void keyboardCallback(registers_t *argRegs)
{
    /* The PIC leaves the scancode in port 0x60 */
    uint8_t scancode;

    scancode = portByteIn(0x60);
    if (scancode > SC_MAX)
    {
        return;
    }

    if (scancode == BACKSPACE)
    {
        backspace(keyBuffer);
        kprint_backspace();
    }
    else if (scancode == ENTER)
    {
        kprint("\n");
        userInput(keyBuffer);
        keyBuffer[0] = '\0';
    }
    else
    {
        char letter = scAscii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(keyBuffer, letter);
        kprint(str);
    }
    UNUSED(argRegs);
}

void initKeyboard()
{
    registerInterruptHandler(IRQ1, keyboardCallback);
}
