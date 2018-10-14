// ------------------------------------------------------------------------
#include "simba.h"
//
#include "main.h"
#include "device.h"
#include "i2c.h"

// ------------------------------------------------------------------------
static struct pin_driver_t heartbeat_led;

static void pz_setup()
{
	sys_start();

	pin_init(&heartbeat_led, &pin_led_dev, PIN_OUTPUT);
	pin_write(&heartbeat_led, 0);
}

// Main Thread Entrypoint
int main()
{
	// Setup Hardware
	pz_setup();
	pz_device_setup();
	pz_i2c_setup();

	// Start Read Devices Thread
	pz_device_start();

	// Start I2C Thread
	pz_i2c_start();

	while (1)
	{
		pin_write(&heartbeat_led, 1);
		thrd_sleep_ms(250);
		pin_write(&heartbeat_led, 0);
		thrd_sleep_ms(250);
	}

	return (0);
}