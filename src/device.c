// ------------------------------------------------------------------------
#include "simba.h"
//
#include "device.h"

// ------------------------------------------------------------------------
void pz_device_setup()
{
    // TODO: Initialize UART
    // TODO: Initialize Devices Addresses
}

// Thread Stack
static THRD_STACK(pz_device_handler_stack, 256);

// Thread Entrypoint
static void *pz_device_handler(void *arg_p)
{
    while (1)
    {
        thrd_sleep_ms(250);
    }

    return NULL;
}

void pz_device_start()
{
    thrd_spawn(&pz_device_handler, NULL, 0, pz_device_handler_stack, sizeof(pz_device_handler_stack));
}

static uint8_t crc(uint8_t *data, uint8_t size)
{
    uint16_t crc = 0;
    for (uint8_t i = 0; i < size; i++)
        crc += *data++;
    return (uint8_t)(crc & 0xFF);
}