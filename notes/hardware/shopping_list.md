# SHOPPING LIST
## Microcontrollers

1. CANPico v1
	- https://www.skpang.co.uk/collections/hats/products/canpico-with-pico-w-board
	- £49.20 (including pico wh)
	- https://buyzero.de/products/canpico-v2-with-pico-wh-pre-installed
	- 71,93 € (including pico wh)
2. CANPico v2 
	- https://buyzero.de/products/canpico-board?s=rec&w=p
	- €61,28 + price of RPI Pico

3. RPI pico with SPI/UART CAN-FD peripheral boards with controller+transciever (RPI doesn't have a controller itself):
	1. MCP2517FD + MCP2562FD
		- https://copperhilltech.com/can-fd-breakout-board-with-spi-interface/
	2. MCP2518FD + ATA6561
		- https://www.reichelt.com/de/en/developer-boards-can-module-mcp2518-debo-can-mcp2518-p376524.html
			- Croatian seller Soldered Electronics
	3. Any other board with controller + transciever which supports driving CAN-FD via SPI, I2C, UART...

5. CANBed **FD**
	- FD is important as there is another variant called only CANBed that doesn't support CAN-FD
	- Arduino supported, but can be used with AVR Studio to program in C/C++
	- https://www.longan-labs.cc/1030009.html
		- 26 USD
6. CANBed Dual
	- https://www.longan-labs.cc/1030019.html
		- $14.90
7. CANBed M4
	- https://www.longan-labs.cc/1030013.html
		- $29.90
8. Arduino from classic family (for example UNO R3) + CAN FD Shield
	- CAN FD shield
		- https://www.seeedstudio.com/CAN-FD-Shield-for-Arduino-p-5604.html
			- $19.90
		- https://www.longan-labs.cc/1030012.html
			- $19.90
		- **MCP2517FD CAN Bus controller**, **SIT1042T CAN transceiver**
	- ARDUINO UNO R3
		- https://www.electrofun.pt/arduino/arduino-uno
			- 16,50 €
10. SAM C21 XPLAINED PRO EVALUATION KIT from MicroChip
	- devboard -  https://www.microchip.com/en-us/development-tool/atsamc21-xpro
		- built in controller and transciever
		- €75.19
11. Any STM32 devboard from product series STM32G0, STM32G4, STM32H5, STM32H7, STM32L5, STM32U5 + transciever breakout board
	- for example NUCLEO STMG0B1RE
		- https://www.st.com/en/evaluation-tools/nucleo-g0b1re.html
	- with MCP2562FD transciever breakout board
		- https://www.skpang.co.uk/products/can-bus-can-fd-breakout-board-5v-supply-and-3-3v-logic
	- nucleo boards can also be used with arduino shields, so the shield mentioned above also applies, however we are then not using the built in STM32 CAN controller, but communicating with an external one on the shield using SPI
		- https://www.longan-labs.cc/1030012.html
12. Teensy 4.0 or 4.1 with CAN-FD transciever breakout board
	- https://www.pjrc.com/store/teensy41.html
	- with MCP2562FD transciever breakout board
		- https://www.skpang.co.uk/products/can-bus-can-fd-breakout-board-5v-supply-and-3-3v-logic

## Single board computers

1. PiCAN FD Zero for Raspberry Pi Zero
	- this is not a microcontroller, but a SBC
	- https://buyzero.de/products/pican-fd-zero-for-raspberry-pi-zero?s=rec&w=p
		- 59,32 € + price of rpi zero
	- https://www.skpang.co.uk/products/copy-of-pican-fd-zero-for-raspberry-pi-zero
		- £47.88 + price of rpi zero
	- RPI ZERO
		- https://www.kubii.com/en/nano-computers/1401-raspberry-pi-zero-v13-3272496006973.html (portugese reseller)
			- 12 €
2. Raspberry Pi (any) with CAN FD shields
	- https://raspberrypi.dk/en/product/2-channel-isolated-can-fd-hat-for-raspberry-pi/
		- €80,27 + price of RPi
	- seeedstudio MCP2518FD CAN FD shield
		- €69 + price of RPi
		- MCP2518FD controller
		- https://www.antratek.nl/2-channel-can-bus-fd-shield-for-raspberry-pi-mcp2518fd
		- https://www.seeedstudio.com/CAN-BUS-FD-HAT-for-Raspberry-Pi-p-4742.html
	