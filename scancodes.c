//Key Code Assignments

// Note: This file, as received from Atmel, contained some strange assignments.
// Most of the non numeric/character characters were mapped incorrectly
// according to my determination and I remapped them.  Either the file was
// incorrect or my keyboard was incorrect or I am missing some fundamental
// issue. A ':' now shows up as a ':' on the terminal.
#include "scancodes.h"

// Unshifted characters
const INT8U unshifted[][2] = {
	{0x76,NOTMAPPED},//ESC
	{0x05,F1},
	{0x06,F2},
	{0x04,F3},
	{0x0C,F4},
	{0x03,F5},
	{0x0B,F6},
	{0x83,F7},
	{0x0A,F8},
	{0x01,F9},
	{0x09,F10},
	{0x78,F11},
	{0x07,F12},
	{0x0E,'`'},
	{0x16,'1'},
	{0x1e,'2'},
	{0x26,'3'},
	{0x25,'4'},
	{0x2e,'5'},
	{0x36,'6'},
	{0x3d,'7'},
	{0x3e,'8'},
	{0x46,'9'},
	{0x45,'0'},
	{0x4e,'-'},
	{0x55,'='},
	{0x66,NOTMAPPED}, //BACKSPACE
	{0x66,NOTMAPPED}, //TAB
	{0x15,'q'},
	{0x1d,'w'},
	{0x24,'e'},
	{0x2d,'r'},
	{0x2c,'t'},
	{0x35,'y'},
	{0x3c,'u'},
	{0x43,'i'},
	{0x44,'o'},
	{0x4d,'p'},
	{0x1c,'a'},
	{0x1b,'s'},
	{0x23,'d'},
	{0x2b,'f'},
	{0x34,'g'},
	{0x33,'h'},
	{0x3b,'j'},
	{0x42,'k'},
	{0x4b,'l'},
	{0x1a,'z'},
	{0x22,'x'},
	{0x21,'c'},
	{0x2a,'v'},
	{0x32,'b'},
	{0x31,'n'},
	{0x3a,'m'},
	{0x54,'['},
	{0x5b,']'},
	{0x5d,'\\'},//'\'
	{0x58,NOTMAPPED}, // Caps lock but shouldnt even get here
	{0x4c,';'},
	{0x52,'\''},//'
	{0x5a,NOTMAPPED}, //ENTER
	{0x12,NOTMAPPED}, // left shift but shouldnt even get here
	{0x41,','},
	{0x49,'.'},
	{0x4a,'/'},
	{0x59,NOTMAPPED}, // Right shift but shouldnt even get here
	{0x14,NOTMAPPED}, // left ctrl but shouldnt even get here
	{0x11,NOTMAPPED}, // left alt but shouldnt even get here
	{0x29,' '},/*Space Bar*/
	{0x11,NOTMAPPED}, // Right alt but shouldnt even get here
	{0x14,NOTMAPPED}, // Right ctrl but shouldnt even get here
	{0x70,'0'},
	{0x69,'1'},
	{0x72,'2'},
	{0x7a,'3'},
	{0x6b,'4'},
	{0x73,'5'},
	{0x74,'6'},
	{0x6c,'7'},
	{0x75,'8'},
	{0x7d,'9'},
	{0x71,NOTMAPPED},//DEL
	{0x79,'+'},
	{0x7b,'-'},
	{0x7c,'*'},
	{0,0}
};

// Shifted characters
const INT8U  shifted[][2] = {
	{0x76,NOTMAPPED},//ESC
	{0x05,F1},
	{0x06,F2},
	{0x04,F3},
	{0x0C,F4},
	{0x03,F5},
	{0x0B,F6},
	{0x83,F7},
	{0x0A,F8},
	{0x01,F9},
	{0x09,F10},
	{0x78,F11},
	{0x07,F12},
	{0x0E,'~'},
	{0x16,'!'},
	{0x1e,'@'},
	{0x26,'#'},
	{0x25,'$'},
	{0x2e,'%'},
	{0x36,'^'},
	{0x3d,'&'},
	{0x3e,'*'},
	{0x46,'('},
	{0x45,')'},
	{0x4e,'_'},
	{0x55,'+'},
	{0x66,NOTMAPPED}, //BACKSPACE
	{0x66,NOTMAPPED}, //TAB
	{0x15,'Q'},
	{0x1d,'W'},
	{0x24,'E'},
	{0x2d,'R'},
	{0x2c,'T'},
	{0x35,'Y'},
	{0x3c,'U'},
	{0x43,'I'},
	{0x44,'O'},
	{0x4d,'P'},
	{0x1c,'A'},
	{0x1b,'S'},
	{0x23,'D'},
	{0x2b,'F'},
	{0x34,'G'},
	{0x33,'H'},
	{0x3b,'J'},
	{0x42,'K'},
	{0x4b,'L'},
	{0x1a,'Z'},
	{0x22,'X'},
	{0x21,'C'},
	{0x2a,'V'},
	{0x32,'B'},
	{0x31,'N'},
	{0x3a,'M'},
	{0x54,'{'},
	{0x5b,'}'},
	{0x5d,'|'},
	{0x58,NOTMAPPED}, // Caps lock but shouldnt even get here
	{0x4c,':'},
	{0x52,'"'},//'
	{0x5a,NOTMAPPED}, //ENTER
	{0x12,NOTMAPPED}, // left shift but shouldnt even get here
	{0x41,'<'},
	{0x49,'>'},
	{0x4a,'?'},
	{0x59,NOTMAPPED}, // Right shift but shouldnt even get here
	{0x14,NOTMAPPED}, // left ctrl but shouldnt even get here
	{0x11,NOTMAPPED}, // left alt but shouldnt even get here
	{0x29,' '},/*Space Bar*/
	{0x11,NOTMAPPED}, // Right alt but shouldnt even get here
	{0x14,NOTMAPPED}, // Right ctrl but shouldnt even get here
	{0x70,'0'},
	{0x69,'1'},
	{0x72,'2'},
	{0x7a,'3'},
	{0x6b,'4'},
	{0x73,'5'},
	{0x74,'6'},
	{0x6c,'7'},
	{0x75,'8'},
	{0x7d,'9'},
	{0x71,NOTMAPPED},//DEL
	{0x79,'+'},
	{0x7b,'-'},
	{0x7c,'*'},
	{0,0}
};

