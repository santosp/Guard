#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "st7565-config.h"
#include "st7565.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"

//#include "delay.h"

/** Global buffer to hold the current screen contents. */
// This has to be kept here because the width & height are set in
// st7565-config.h
unsigned char glcd_buffer[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
unsigned char glcd_flipped = 1;
/* Look up Table to correct incorrectly labeled pages*/
int pagemap[] = { 4, 5, 6, 7, 0, 1, 2, 3 };
#ifdef ST7565_DIRTY_PAGES
unsigned char glcd_dirty_pages;
#endif
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_pixel
	 - Initialization function that sets up the clock module
*/
void glcd_pixel(unsigned char x, unsigned char y, unsigned char colour) {

    if (x > SCREEN_WIDTH || y > SCREEN_HEIGHT) return;
    // Real screen coordinates are 0-63, not 1-64.
	x -= 0;
	y-=1;
    unsigned short array_pos = x + ((y / 8) * 128);

#ifdef ST7565_DIRTY_PAGES
//#warning ** ST7565_DIRTY_PAGES enabled, only changed pages will be written to the GLCD **
    glcd_dirty_pages |= 1 << (array_pos / 128);
#endif

    if (colour) {
        glcd_buffer[array_pos] |= 1 << (y % 8);
    } else {
        glcd_buffer[array_pos] &= 0xFF ^ (1 << (y % 8));
    }
}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_blank
	 - Clears the buffer and the LCD
*/
void glcd_blank() {
	int n,y,x;
    // Reset the internal buffer
    for ( n=1; n <= (SCREEN_WIDTH * SCREEN_HEIGHT / 8) - 1; n++) {
        glcd_buffer[n] = 0;
    }

    // Clear the actual screen
    for (y = 0; y < 8; y++) {
        glcd_command(GLCD_CMD_SET_PAGE | pagemap[y]);

        // Reset column to 0 (the left side)
        glcd_command(GLCD_CMD_COLUMN_LOWER);
        glcd_command(GLCD_CMD_COLUMN_UPPER);

        // We iterate to 132 as the internal buffer is 65*132, not
        // 64*124.
        for (x = 0; x < 128; x++) {
            glcd_data(0x00);
        }
    }
}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_blank_page
	 - Clears the buffer and the LCD of a certain page
*/
void glcd_blank_page(unsigned char page) {
	int n,x;
    // Reset the internal buffer
    for ( n=(page*128-127); n <= (page*128); n++) {
        glcd_buffer[n] = 0;
    }

    // Clear the actual screen
    //for (y = 0; y < 8; y++) {
        glcd_command(GLCD_CMD_SET_PAGE | pagemap[page-1]);

        // Reset column to 0 (the left side)
        glcd_command(GLCD_CMD_COLUMN_LOWER);
        glcd_command(GLCD_CMD_COLUMN_UPPER);

        // We iterate to 132 as the internal buffer is 65*132, not
        // 64*124.
        for (x = 0; x < 132; x++) {
            glcd_data(0x00);
        }
    //}
}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_blank_page
	 - Clears the buffer and the LCD of a certain page
*/
void glcd_blank_pagexy(unsigned char page,unsigned char n, unsigned char x) {
	//int n,x;
    // Reset the internal buffer
    for ( n; n <= x; n++) {
        glcd_buffer[n] = 0;
    }

    // Clear the actual screen
    //for (y = 0; y < 8; y++) {
        glcd_command(GLCD_CMD_SET_PAGE | pagemap[page-1]);

        // Reset column to 0 (the left side)
        glcd_command(GLCD_CMD_COLUMN_LOWER);
        glcd_command(GLCD_CMD_COLUMN_UPPER);

        // We iterate to 132 as the internal buffer is 65*132, not
        // 64*124.
        for (n; n < x; n++) {
            glcd_data(0x00);
        }
    //}
}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_refresh
	 - Function that actually writes data to the LCD, while others just write
	 to the buffer
*/
void glcd_refresh() {
    int y,x;


	for ( y = 0; y < 8; y++) {

#ifdef ST7565_DIRTY_PAGES
        // Only copy this page if it is marked as "dirty"
        if (!(glcd_dirty_pages & (1 << y))) continue;
#endif

        glcd_command(GLCD_CMD_SET_PAGE|pagemap[y]);

        // Reset column to the left side.  The internal memory of the
        // screen is 132*64, we need to account for this if the display
        // is flipped.
        //
        // Some screens seem to map the internal memory to the screen
        // pixels differently, the ST7565_REVERSE define allows this to
        // be controlled if necessary.
#ifdef ST7565_REVERSE
        if (!glcd_flipped) {
#else
        if (glcd_flipped) {
#endif
            glcd_command(GLCD_CMD_COLUMN_LOWER | 4);
        } else {
            glcd_command(GLCD_CMD_COLUMN_LOWER);
        }
        glcd_command(GLCD_CMD_COLUMN_UPPER);

        for ( x = 0; x <= 128; x++) {
            glcd_data(glcd_buffer[(y * 128) + x]);
        }
    }

#ifdef ST7565_DIRTY_PAGES
    // All pages have now been updated, reset the indicator.
    glcd_dirty_pages = 0;
#endif
}
	/*======================================================================*/
	/*  Type: Function - Public
		Name: glcd_init
		 - Initialization function that sets up the LCD module
	*/
void glcd_init() {
    //Enable Ports for use
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    	//Enable Pins as inputs
	//GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1|GPIO_PIN_2);
	// Select the chip
	 BIT_CLR(((GLCD_CS1)),GLCD_CS1P);//GLCD_CS1 = 0;


	 BIT_CLR(((GLCD_RESET)),GLCD_RESETP);//GLCD_RESET = 0;

    // Datasheet says "wait for power to stabilise" but gives
    // no specific time!
    //DelayMs(50);

    BIT_SET(((GLCD_RESET)),GLCD_RESETP);//GLCD_RESET = 1;

    // Datasheet says max 1ms here
    //DelayMs(1);
    //Initializing the pins
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);



	// Connect SPI to PA2 (clock) and PA5(TX)
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//TODO make rom
	GPIOPinConfigure(GPIO_PD0_SSI3CLK);
	GPIOPinConfigure(GPIO_PD3_SSI3TX);
	//GPIOPinTypeSSI(GPIO_PORTA_BASE, SSI_CLK | SSI_TX);
	GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_3);
	//
		// Configure SSI0
		//
		SSIConfigSetExpClk(SSI3_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,  SSI_MODE_MASTER, SysCtlClockGet()/2, 8);

		//
		// Enable the SSI module.
		//
		SSIEnable(SSI3_BASE);


    // Set LCD bias to 1/9th
    glcd_command(GLCD_CMD_BIAS_9);

    // Horizontal output direction (ADC segment driver selection)
    glcd_command(GLCD_CMD_HORIZONTAL_NORMAL);

    // Vertical output direction (common output mode selection)
    glcd_command(GLCD_CMD_VERTICAL_REVERSE);

    // The screen is the "normal" way up
    //glcd_flipped = 0;

    // Set internal resistor.  A suitable middle value is used as
    // the default.
    glcd_command(GLCD_CMD_RESISTOR | 0x3);

    // Power control setting (datasheet step 7)
    // Note: Skipping straight to 0x7 works with my hardware.
    //	glcd_command(GLCD_CMD_POWER_CONTROL | 0x4);
    //	DelayMs(50);
    //	glcd_command(GLCD_CMD_POWER_CONTROL | 0x6);
    //	DelayMs(50);
    glcd_command(GLCD_CMD_POWER_CONTROL | 0x7);
    //	DelayMs(10);

    // Volume set (brightness control).  A middle value is used here
    // also.
    glcd_command(GLCD_CMD_VOLUME_MODE);
    glcd_command(31);
    glcd_contrast(5, 35);
    // Reset start position to the top
    glcd_command(GLCD_CMD_DISPLAY_START);

    // Unselect the chip
    BIT_SET(((GLCD_CS1)),GLCD_CS1P);// GLCD_CS1 = 1;
}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_data
	 - Function that sends commands to the LCD
*/
void glcd_data(unsigned char data) {

    // A0 is high for display data
	BIT_SET(((GLCD_A0)),GLCD_A0P);//GLCD_A0 = 1;

    // Select the chip
    BIT_CLR(((GLCD_CS1)),GLCD_CS1P);//GLCD_CS1 = 0;

    SSIDataPut(SSI3_BASE, data);
    //
    // Wait until SSI is done transferring all the data in the transmit FIFO
    //
    while(SSIBusy(SSI3_BASE))
    {
    }

    // Unselect the chip
    BIT_SET(((GLCD_CS1)),GLCD_CS1P);//GLCD_CS1 = 1;

}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_command
	 - Function that sends commands to the LCD
*/
void glcd_command(char command) {

    // A0 is low for command data
	BIT_CLR(((GLCD_A0)),GLCD_A0P);//GLCD_A0 = 0;

    // Select the chip
    BIT_CLR(((GLCD_CS1)),GLCD_CS1P);//GLCD_CS1 = 0;

    SSIDataPut(SSI3_BASE, command);
    //
    // Wait until SSI is done transferring all the data in the transmit FIFO
    //
    while(SSIBusy(SSI3_BASE))
    {
    }

    // Unselect the chip
    BIT_SET(((GLCD_CS1)),GLCD_CS1P);//GLCD_CS1 = 1;
}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_flip_screen
	 - Allows the user to orient the screen accordingly
*/
void glcd_flip_screen(unsigned char flip) {
    if (flip) {
        glcd_command(GLCD_CMD_HORIZONTAL_NORMAL);
        glcd_command(GLCD_CMD_VERTICAL_REVERSE);
        glcd_flipped = 0;
    } else {
        glcd_command(GLCD_CMD_HORIZONTAL_REVERSE);
        glcd_command(GLCD_CMD_VERTICAL_NORMAL);
        glcd_flipped = 1;
    }
}
/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_inverse_screen
	 - Allows the user to flip the screen on the fly
*/
void glcd_inverse_screen(unsigned char inverse) {
    if (inverse) {
        glcd_command(GLCD_CMD_DISPLAY_REVERSE);
    } else {
        glcd_command(GLCD_CMD_DISPLAY_NORMAL);
    }
}

/*======================================================================*/
/*  Type: Function - Public
	Name: glcd_contrast
	 - Enables the user to set the contrast of the LCD backlight
*/
void glcd_contrast(char resistor_ratio, char contrast) {
    if (resistor_ratio > 7 || contrast > 63) return;

    glcd_command(GLCD_CMD_RESISTOR | resistor_ratio);
    glcd_command(GLCD_CMD_VOLUME_MODE);
    glcd_command(contrast);
}

//=================================================================================//
/*Change log
 * Paul Santos
 * 1/9/13
 * -Changed all of the bit setting and clearing to a macro that is defined in the
 * 	-st7565-counfig.h
 * -commented out the delays and #warning
 *
 *
 */
