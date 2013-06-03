//Key Code Assignments

// Note: This file, as received from Atmel, contained some strange assignments.
// Most of the non numeric/character characters were mapped incorrectly
// according to my determination and I remapped them.  Either the file was
// incorrect or my keyboard was incorrect or I am missing some fundamental
// issue. A ':' now shows up as a ':' on the terminal.
#include "Code_Standards.h"
#define NOTMAPPED 0x2A // '*'
#define F1 0x80
#define F2 0x81
#define F3 0x82
#define F4 0x83
#define F5 0x84
#define F6 0x85
#define F7 0x86
#define F8 0x87
#define F9 0x88
#define F10 0x89
#define F11 0x90
#define F12 0x91
#define CR 0x0D
#define BS 0x08
#define EXTENED 0xE0
#define LEFTA	0xA0//0x6B
#define RIGHTA	0xA1//0x74
#define UPA 	0xA2//0x75
#define DOWNA 	0xA3//0x72

// Unshifted characters
extern const INT8U unshifted[][2];

// Shifted characters
extern const INT8U shifted[][2];
// Extended characters
extern const INT8U  extended[][2];
