/*******************************************************************************
 * File:
 *  string.h
 *
 * Description:
 *  This file contains functions to work with strings. Specfically character
 *  arrays.
 *
 * Members:
 *  strcmp
 *  append
 *  strlen
 *  reverse
 *  backspace
 *  intToAscii
 *  hexToAscii
 *
 * Todo:
 *  Update strcmp to check the sizes of each argument to compare entire string.
 *  
 * Modification History:
 *  Date         Who         Description
 *  ============================================================================
 *  01/17/19    T.Gajewski   Initial version.
 ******************************************************************************/
#ifndef _STRING_H_
#define _STRING_H_

/*******************************************************************************
 * Function:
 *  strcmp
 *
 * Description:
 *  This function will compare two string arrays against each other.  If the
 *  arrays are not the same size, if argStr1 contains 'abc\0' and argStr2
 *  contains 'abcd\0' the return will indicate the strings are valid.
 *
 * Arguments:
 *  argStr1: char array to compare.
 *  argStr2: char array to compare.
 *
 * Returns:
 *  < 0 if argStr1 < argStr2
 *  0 is argStr1 is equal to argStr2.
 *  > 0 if argStr1 > argStr2
 ******************************************************************************/
int strcmp(char argStr1[], char argStr2[]);

/*******************************************************************************
 * Function:
 *  append
 *
 * Description:
 *  This function append a character to a character array.
 *
 * Arguments:
 *  argStr: char array to append to.
 *  argChar: characer to append.
 *
 * Returns:
 *  None.
 ******************************************************************************/
void append(char argStr[], char argChar);

/*******************************************************************************
 * Function:
 *  strlen
 *
 * Description:
 *  This function will return the index of the first null termintor in the char
 *  array.  It in turn returns the size of a character array.
 *
 * Arguments:
 *  argStr: Character array to check the size of.
 *
 * Returns:
 *  int: index of the first null terminating character - 1.
 ******************************************************************************/
int strlen(char argStr[]);

/*******************************************************************************
 * Function:
 *  reverse
 *
 * Description:
 *  This function will reverse a character arrays order.
 *
 * Arguments:
 *  argStr: character array to reverse
 *
 * Returns:
 *  None.
 ******************************************************************************/
void reverse(char argStr[]);

/*******************************************************************************
 * Function:
 *  backspace
 *
 * Description:
 *  This function will replace that last character in the character array with
 *  a null terminating character.
 *
 * Arguments:
 *  argStr: character array to remove last characer from.
 *
 * Returns:
 *  None.
 ******************************************************************************/
void backspace(char argStr[]);

/*******************************************************************************
 * Function:
 *  intToAscii
 *
 * Description:
 *  This function will convert an integer to a character array.
 *
 * Arguments:
 *  argNumer Number to convert a character array.
 *  argOutput: Character to array to populate with stringified integer.
 *
 * Returns:
 *  None.
 ******************************************************************************/
void intToAscii(int argNumber, char argOutput[]);

/*******************************************************************************
 * Function:
 *  hexToAscii
 *
 * Description:
 *  This function will convert an integer(hex) to a character array.  It will
 *  convert the integer to its hex representation as a string.
 *
 * Arguments:
 *  argNumer Number to convert a character array.
 *  argOutput: Character to array to populate with stringified integer.
 *
 * Returns:
 *  None.
 ******************************************************************************/
void hexToAscii(int argNumber, char argOutput[]);

#endif /* _STRING_H_ */
