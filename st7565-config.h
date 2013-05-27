// Setup for ST7565R in SPI mode
//#define BIT0 0x01
//#define BIT1 0x02
//#define BIT2 0x04
//#define BIT3 0x08
//#define BIT4 0x0F
//#define BIT5 0x20//32
//#define BIT6 0x40//64
//#define BIT7 0x80//128
/** The chip select pin */
#define GLCD_CS1 GPIO_PORTE_BASE
#define GLCD_CS1P GPIO_PIN_5
/** The reset pin (this is required and should not be tied high) */
#define GLCD_RESET GPIO_PORTE_BASE
#define GLCD_RESETP GPIO_PIN_4
/** The A0 pin, which selects command or data mode */
#define GLCD_A0 GPIO_PORTB_BASE
#define GLCD_A0P GPIO_PIN_1
/** The clock pin */
//#define GLCD_SCL GPIO_PORTB_BASE
#define GLCD_SCL GPIO_PORTA_BASE
//#define GLCD_SCLP GPIO_PIN_0
#define GLCD_SCLP GPIO_PIN_2
/** The data pin */
//#define GLCD_SDA GPIO_PORTB_BASE
#define GLCD_SDA GPIO_PORTA_BASE
//#define GLCD_SDAP GPIO_PIN_5
#define GLCD_SDAP GPIO_PIN_5

#define BIT_SET(Location,Mask) GPIOPinWrite(Location, Mask, Mask)//((Location) |= (Mask))
#define BIT_CLR(Location,Mask) GPIOPinWrite(Location, Mask, 0x00)//((Location) &= ~(Mask))



/** Screen width in pixels (tested with 128) */
#define SCREEN_WIDTH 0x80//128
/** Screen height in pixels (tested with 64) */
#define SCREEN_HEIGHT 0x40//64

/** Define this if your screen is incorrectly shifted by 4 pixels */
#define ST7565_REVERSE

/** By default we only write pages that have changed.  Undefine this
    if you want less/faster code at the expense of more SPI operations. */
#define ST7565_DIRTY_PAGES 0
//#undef ST7565_DIRTY_PAGES 1

//=================================================================================//
/*Change log
 * Paul Santos
 * 1/9/13
 * - Changed all of the defines for the pins so it will fit the Stellaris
 * 		- Also added a secondary define to each so it can describe the Port and Pin used
 * - Added macro that will set or clear a specific bit based on the Port and Pin
 * - Changed screen width and height to HEX
 * ----------------------------------------------------------------------------------
 * 1/10/13
 *  - Changed the macro so that it is using the stellaris GPIOPINWRITE function
 *  	- First argument is the PORT, 2nd is the PIN, and 3rd is what you are setting it with
 *  		- If set with same address as the pin is, it will set the bit
 *  		- If set with 0x00 it will clear the bit
 *
 */

