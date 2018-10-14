// ------------------------------------------------------------------------
#include "simba.h"
//
#include "i2c.h"

// ------------------------------------------------------------------------
static struct i2c_driver_t i2c_bus;

void pz_i2c_setup()
{
    i2c_init(&i2c_bus, &i2c_0_dev, -1, SLAVE_ADDRESS);
    i2c_slave_start(&i2c_bus);
}

// Thread Stack
static THRD_STACK(pz_i2c_handler_stack, 256);

// Thread Entrypoint
static void *pz_i2c_handler(void *arg_p)
{
    uint8_t buf[5];
    memset(buf, 0, sizeof(buf));
    while (1)
    {
        thrd_sleep_ms(250);
    }

    return NULL;
}

void pz_i2c_start()
{
    thrd_spawn(&pz_i2c_handler, NULL, 0, pz_i2c_handler_stack, sizeof(pz_i2c_handler_stack));
}
