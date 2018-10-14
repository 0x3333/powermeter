#ifndef _DEVICE_H_
#define _DEVICE_H_

// ------------------------------------------------------------------------

#define BAUD_RATE 9600
#define READ_TIMEOUT 1000
#define READ_ERROR_VALUE -1

#define COMMAND_VOLTAGE 0xB0
#define COMMAND_CURRENT 0xB1
#define COMMAND_POWER 0xB2
#define COMMAND_ENERGY 0xB3
#define COMMAND_SET_ADDRESS 0xB4
#define COMMAND_POWER_ALARM 0xB5

#define RESPONSE_VOLTAGE 0xA0
#define RESPONSE_CURRENT 0xA1
#define RESPONSE_POWER 0xA2
#define RESPONSE_ENERGY 0xA3
#define RESPONSE_SET_ADDRESS 0xA4
#define RESPONSE_POWER_ALARM 0xA5

// ------------------------------------------------------------------------

struct Command
{
    uint8_t command;
    uint8_t address[4];
    uint8_t data;
    uint8_t crc;
};

// ------------------------------------------------------------------------

void pz_device_setup();

void pz_device_start();

// ------------------------------------------------------------------------

#endif /* _DEVICE_H_ */
