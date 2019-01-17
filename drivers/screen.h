#ifndef _SCREEN_H_
#define _SCREEN_H_

#define VIDEO_ADDRESS  0xB8000
#define MAX_ROWS       25
#define MAX_COLS       80
#define WHITE_ON_BLACK 0x0F
#define RED_ON_WHITE   0xF4

/* Screen I/O ports. */
#define SCREEN_CONTROL_REG 0x3D4
#define SCREEN_DATA_REG    0x3D5

/* Public kernel API. */
void clearScreen();
void kprintAt(char *argMessage, int argCol, int argRow);
void kprint(char *argMessage);
void kprint_backspace();

#endif /* _SCREEN_H_ */
