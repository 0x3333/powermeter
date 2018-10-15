# Power Meter

This project reads multiple PZEM004T readers in the same UART(Support for 6 devices), using Multi-drop TX. It reads all devices constantly and when asked, will send the last reading, synchronously. It uses UART to read the devices and I2C to responde to a master node. I2C Address is `0x33`.

The default implementation is using an Arduino Pro Mini clone(Funduino), the software is using [Simba Framework](https://github.com/eerimoq/simba/).

Folder `pcb` contains the schematics and my PCB version of the reader.

This project support 2 hacks in the PZEM004T:

1. Power direction, allows the reader to know the direction of the power, used in setups with solar panels, etc.
2. Remote reset, allows the reader to reset the counter remotely, without user interaction(Reset all simultaneously, not possible to reset individualy).

These hacks, will be documented here later, the PCB includes 3 mini pcbs that will hold the optocouplers need to isolate the high voltage.


***_Code not implemented yet_***


## PCB

[Schematic](https://github.com/0x3333/powermeter/raw/master/pcb/schematic.pdf)

[PCB Top](https://github.com/0x3333/powermeter/raw/master/pcb/pcb_top.pdf)

[PCB Bottom](https://github.com/0x3333/powermeter/raw/master/pcb/pcb_bottom.pdf)

![Schematic](https://raw.githubusercontent.com/0x3333/powermeter/master/github/schematic.png)

![PCB Top](https://raw.githubusercontent.com/0x3333/powermeter/master/github/pcb_top.png)

![PCB Bottom](https://raw.githubusercontent.com/0x3333/powermeter/master/github/pcb_bottom.png)
