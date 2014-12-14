#ifndef Types_H
#define Types_H

#if !(defined(__XC) || defined(__18CXX))
// For PC
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int
#define int8 char
#define int16 short int
#define int32 int

#else
// For PIC18
#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long
#define int8 char
#define int16 int
#define int32 long

#endif // !(defined(__XC) || defined(__18CXX))


#endif // Types_H