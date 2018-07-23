// ------------------------------------------------------------------------
// Includes:
#include <avr/interrupt.h>
#include <util/delay.h>
//
#include "main.h"
#include "io.h"
#include "uart.h"

// ------------------------------------------------------------------------
// Main Code:

int main()
{
	cli();

	PIN_MODE(LED0_D, LED0, OUTPUT); // ATmega328 Module

	init_uart();

	// Initial States
	LED0_OFF();

	sei();

	while (1)
	{
		LED0_OFF();
		_delay_ms(500);
		LED0_ON();
	}

	return 0;
}
