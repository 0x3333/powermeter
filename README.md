# Power Meter

This project reads multiple PZEM004T readers in the same UART, using Multi-drop TX. It reads all devices constantly and when asked, will send the last reading, synchronously. It uses UART to read the devices and I2C to responde to a master node. I2C Address is `0x33`.

The default implementation is using an Arduino Pro Mini clone(Funduino), the software is using [Simba Framework](https://github.com/eerimoq/simba/).

Folder `pcb` contains the schematics and my PCB version of the reader.

This project support 2 hacks in the PZEM004T:

1. Power direction, allows the reader to know the direction of the power, used in setups with solar panels, etc.
2. Remote reset, allows the reader to reset the counter remotely, without user interaction.

These hacks, will be documented here later, the PCB includes 3 mini pcbs that will hold the optocouplers need to isolate the high voltage.
