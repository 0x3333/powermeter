// ------------------------------------------------------------------------
#include "simba.h"
//
#include "main.h"
#include "device.h"

// ------------------------------------------------------------------------
static struct uart_driver_t uart;
static struct pin_driver_t tx_en[6];
static struct pin_driver_t dir[6];
static char buf[16];

// ------------------------------------------------------------------------
static void set_tx_en(uint8_t dev)
{
    for (uint8_t i = 0; i < MAX_DEVICES; i++)
    {
        pin_set_mode(&tx_en[i], (i == dev) ? PIN_INPUT : PIN_OUTPUT);
        pin_write(&tx_en[i], (i == dev) ? 0 : 1);
    }
}

static void read_device(uint8_t dev, struct read *reading)
{
    set_tx_en(dev);
}

// Thread Stack
static THRD_STACK(pz_device_handler_stack, 256);

// Thread Entrypoint
static void *pz_device_handler(void *arg_p)
{
    while (1)
    {
        for (uint8_t dev = 0; dev < MAX_DEVICES; dev++)
        {
            rwlock_writer_take(&readings_lock);
            read_device(dev, &readings[dev]);

            rwlock_writer_give(&readings_lock);
        }
    }

    return NULL;
}

void pz_device_setup()
{
    uart_init(&uart, &uart_device[0], 9600, &buf, sizeof(buf));

    // TX Enable
    pin_init(&tx_en[0], &pin_d2_dev, PIN_INPUT);
    pin_init(&tx_en[1], &pin_d3_dev, PIN_INPUT);
    pin_init(&tx_en[2], &pin_d4_dev, PIN_INPUT);
    pin_init(&tx_en[3], &pin_d5_dev, PIN_INPUT);
    pin_init(&tx_en[4], &pin_d6_dev, PIN_INPUT);
    pin_init(&tx_en[5], &pin_d7_dev, PIN_INPUT);

    // Direction
    pin_init(&dir[0], &pin_a3_dev, PIN_INPUT);
    pin_init(&dir[1], &pin_a2_dev, PIN_INPUT);
    pin_init(&dir[2], &pin_a1_dev, PIN_INPUT);
    pin_init(&dir[3], &pin_a0_dev, PIN_INPUT);
    pin_init(&dir[4], &pin_d8_dev, PIN_INPUT);
    pin_init(&dir[5], &pin_d9_dev, PIN_INPUT);
}

void pz_device_start()
{
    thrd_spawn(&pz_device_handler, NULL, 0, pz_device_handler_stack, sizeof(pz_device_handler_stack));
}

// static uint8_t crc(uint8_t *data, uint8_t size)
// {
//     uint16_t sum = 0;
//     for (uint8_t i = 0; i < size; i++)
//     {
//         sum += *data++;
//     }
//     return (uint8_t)(sum & 0xFF);
// }