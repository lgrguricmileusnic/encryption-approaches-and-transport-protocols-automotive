# uCs, uC devboards and shields
## Raspberry Pi, Pico, Zero...
### CANPico Board (ARM)
#### v1
- https://kentindell.github.io/canpico
- https://raw.githubusercontent.com/kentindell/canhack/master/docs/CANPico%20hardware%20reference%20manual.pdf
- https://buyzero.de/products/canpico-board?s=rec&w=p
	- €61,28 + price of RPI Pico
-  Plug bridge for a standard 120-CAN bus termination resistor
- Jumper for activating and disabling the transmission input for the transceiver
- MC - RP2040 
	- https://www.raspberrypi.com/products/rp2040/
		- Dual Cortex M0+ processor cores, up to 133MHz
		- 264kB of embedded SRAM in 6 banks
		- 2MB Flash
		- Accelerated integer and floating-point libraries on-chip
- CAN 2.0 and CAN FD
	- [Microchip](https://www.microchip.com) [MCP2517/18FD](https://www.microchip.com/en-us/product/MCP2518FD) CAN controller with 2Kbyte buffer space
	- Microchip [[CAN_transceivers_controllers#transceivers#MCP2562FD|MCP2562FD]]
#### v2
- https://www.skpang.co.uk/collections/hats/products/canpico-with-pico-w-board
	- £49.20 (including pico wh)
- https://buyzero.de/products/canpico-v2-with-pico-wh-pre-installed
	- 71,93 € (including pico wh)
Same as [[hardware#CANPico Board (ARM)#v1|v1]] but with:
- MCP251863T controller
### PiCAN FD Zero for Raspberry Pi Zero
- https://buyzero.de/products/pican-fd-zero-for-raspberry-pi-zero?s=rec&w=p
	- 59,32 € + price of rpi zero
- https://www.skpang.co.uk/products/copy-of-pican-fd-zero-for-raspberry-pi-zero
	- £47.88 + price of rpi zero
- RPI ZERO
	- https://www.kubii.com/en/nano-computers/1401-raspberry-pi-zero-v13-3272496006973.html (portugese seller)
		- 12 €
	- SBC not a microcontroller
- https://cdn.shopify.com/s/files/1/1560/1473/files/PICAN_FD_Zero_UGB_10.pdf?v=1631789542
- **Features**  
	- **Microchip MCP2518FD CAN Controller**
	- **Microchip [[CAN_transceivers_controllers#MCP2562FD|MCP2562FD]] CAN transceiver**
	- Arbitration Bit Rate up to 1Mbps
	- Data Bit Rate up to 8Mbps
	- CAN FD Controller modes
	- Mixed CAN 2.0B and CANFD mode
	- CAN 2.0B mode
	- Conforms to ISO 11898-1:2015
	- High speed SPI Interface
	- 4 way plug-in terminal for CAN and power
	- 120Ω terminator ready
	- LED indicator (GPIO 22)
	- SocketCAN driver, appears as can0 to application
	- Interrupt RX on GPIO25 or GPIO6
	- [Qwiic (I2C)](https://buyzero.de/products/sparkfun-qwiic-kabel-200mm) connector for extra sensors

## Arduino
### CANBed FD
- https://www.longan-labs.cc/1030009.html
	- 25.90 USD
- Atmega32U4
	- low-power Microchip 8-bit AVR® RISC-based microcontroller
	- 32 KB self-programming Flash program memory
	- 2.5 KB SRAM
- **programmable using Arduino IDE or AVR Studio (C/C++)**
- The Arduino CAN FD library helps to save time on your CAN project.
- CAN 2.0 and FD
	- up to 8Mbps communication speed
	- controller - MCP2517FD
	- transciever - [[CAN_transceivers_controllers#MCP2542|MCP2542]] (MCP2557)
### CAN FD Shield for Arduino
- https://www.seeedstudio.com/CAN-FD-Shield-for-Arduino-p-5604.html
	- 19.90 USD + price of arduino board from classic family
		- https://docs.arduino.cc/hardware/
- CAN 2.0 and FD
	- 5 Mb/s speed
	- controller - MCP2517FD
	- transciever - SIT1042T
		- https://semic-boutique.com/wp-content/uploads/2016/05/SIT1042.pdf

## Microchip 32-bit MCUs with CAN
### MCU selector
- https://www.microchip.com/en-us/products/interface-and-connectivity/can/32-bit-mcus-with-can-quick-selector-guide
	- look under Development Tools section

### SAM C21 XPLAINED PRO EVALUATION KIT
- devboard -  https://www.microchip.com/en-us/development-tool/atsamc21-xpro
	- €75.19
	- https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/UserGuides/Atmel-42460-SAM-C21-Xplained-Pro_User-Guide.pdf
- MCU - https://www.microchip.com/en-us/product/atsamc21j18a
	- 32-Bit ARM Cortex M0+ MCU
	- 256KB in-system self-programmable Flash
	- 8KB independent self-programmable Flash for EEPROM emulation
	- 32KB SRAM Main Memory
- CAN FD and CAN 2.0
	- Communication Speed up to 5 Mbps
	- transciever [[CAN_transceivers_controllers#transceivers#ATA6560|ATA6560]]

## STM32 (ARM)

![[stm32_canfd_products.png]]
- [[an5348-introduction-to-fdcan-peripherals-for-stm32-product-classes-stmicroelectronics.pdf|FDCAN peripherals for stm32 products]]

### CAN 2.0 ONLY!
- [How to use fdcan peripherals stm32 NUCLEO-G0B1RE](https://community.st.com/t5/stm32-mcus/how-to-use-fdcan-to-create-a-simple-communication-with-a-basic/ta-p/671766)
- ~~communication between two stm32 boards with CAN 2.0~~
- ~~need two NUCLEO boards with HW-021 TJA1050 transcievers~~
	- ~~https://www.hansinformation.com/showpro.asp?id=333
	- ~~[[CAN_transceivers_controllers#TJA1050|TJA1050]]~~
		- **DOESN'T SUPPORT CAN FD**, ~~would need to find different CAN transceiver board, maybe [[CAN_transceivers_controllers#transceivers#MCP2542|MCP2542]] or [[CAN_transceivers_controllers#transceivers#SIT1042|SIT1042]]~~
	- ~~NUCLEO boards have CAN controller, but no transciever~~
- https://controllerstech.com/fdcan-normal-mode-stm32/


# Transciever/controller breakout boards

Notes:
- volatage levels of popular controllers
	- Pico is 3.3V
	- STM32 is 3.3V
	- Arduino Uno is 5V


## [[CAN_transceivers_controllers#MCP2562FD|MCP2562FD]]

- https://www.skpang.co.uk/products/can-bus-can-fd-breakout-board-5v-supply-and-3-3v-logic
	- 22.20 GBP
	- 5V supply, 3.3V logic
	- 6 Mb/s
	- 120R terminating resistor via jumper
	- could work with teensy 4.0 or 4.1 as seen in schematic of:
		- https://buyzero.de/products/teensy-4-0-can-fd-and-lin-bus-board-include-teensy-4-0

## [[CAN_transceivers_controllers#MCP2542|MCP2542]]
- https://www.mikroe.com/mcp2542-click
	- it says 8Mbps for the IC, but UART might be a bottleneck
	- might be connectable directly using CAN TX RX pins to a controller or a uC with built in controller (skipping UART)
	
	![[mcp2542_click_pinout.png]]


## MCP2517FD + MCP2562FD
- https://copperhilltech.com/can-fd-breakout-board-with-spi-interface/
	- 49.95$
	- SPI
	- 5V supply, 3.3V logic
	- 8Mbps
	- 120R terminating resistor via jumper
## MCP2518
- https://www.reichelt.com/de/en/developer-boards-can-module-mcp2518-debo-can-mcp2518-p376524.html
	- 19,90
	- SPI



