# ***_Code not implemented yet_***

# Power Meter

This project reads multiple PZEM004T readers in the same UART(Support for 6 devices), using Multi-drop TX. It reads all devices constantly and when asked, will send the last reading, synchronously. It uses UART to read the devices and I2C to responde to a master node. I2C Address is `0x33`.

The default implementation is using an Arduino Pro Mini clone(Funduino), the software is using [Simba Framework](https://github.com/eerimoq/simba/).

Folder `pcb` contains the schematics and my PCB version of the reader.

This project support 2 hacks in the PZEM004T:

1. Power direction, allows the reader to know the direction of the power, used in setups with solar panels, etc.
2. Remote reset, allows the reader to reset the counter remotely, without user interaction(Reset all simultaneously, not possible to reset individualy).

These hacks, will be documented here later, the PCB includes 3 mini pcbs that will hold the optocouplers need to isolate the high voltage.

## Info

* The `TX#_EN` pins are used to disable a device `TX` line, so we can set the addresses without user interaction. We force `TX#_EN` `High` on all devices except the one we want to set the address, and then send the set address command. There is a jumper to enable/disable this in case of failure to work.
* `DC_DC` component is a 5V->3.3V converter, I'm using these: [Step-Down Power Supply Buck Module AMS1117](https://www.aliexpress.com/item/10Pcs-5V-To-3-3V-DC-DC-Step-Down-Power-Supply-Buck-Module-AMS1117-800MA/32838774398.html)

## PCB

[Schematic](https://github.com/0x3333/powermeter/raw/master/pcb/schematic.pdf)

[PCB](https://github.com/0x3333/powermeter/raw/master/pcb/pcb.pdf)

![Schematic](https://raw.githubusercontent.com/0x3333/powermeter/master/github/schematic.png)

![PCB](https://raw.githubusercontent.com/0x3333/powermeter/master/github/pcb.png)
