#ifndef _PORTS_H_
#define _PORTS_H_

unsigned char portByteIn(unsigned short argPort);
void portByteOut(unsigned short argPort, unsigned char argData);

unsigned short shortportWordIn(unsigned short argPort);
void pordWordOut(unsigned short argPort, unsigned short argData);

#endif /* _PORTS_H_ */
