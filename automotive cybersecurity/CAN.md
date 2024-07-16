# Attack catalogue

| ID  | **Attack Name**                   | **Description**                                                                                                                                                                                                                                                                                                                                                                                                                                                                               | **STRIDE category** | MITRE<br>EMB3D TID |
| :-: | --------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------- | ------------------ |
| 01  | **Bus Flood Attack**              | A simple denial-of-service attack where CAN frames are transmitted as fast as possible to saturate the bus bandwidth. This causes a delay or complete DoS in ECU communication, leading to system failures. An open bus can be exploited by transmitting frames with a high-priority CAN ID (where highest priority has ID 0x0 due to [CAN Arbitration](https://dissec.to/kb/chapters/can/can.html#can-arbitration-cdma-cr) ).                                                                | Denial of Service   |                    |
| 02  | **Simple Frame Spoofing**         | An authentication attack involving the acceptance of a fake frame by a receiver as if it came from a legitimate sender. The attack may trigger the Arbitration Doom Loop, potentially causing ECUs to go to the Bus-Off state.                                                                                                                                                                                                                                                                | Spoofing            |                    |
| 03  | **Adaptive Spoofing**             | Improves upon simple spoofing by synchronizing with legitimate frames to avoid clashes.                                                                                                                                                                                                                                                                                                                                                                                                       | Spoofing            |                    |
| 04  | **Error Passive Spoofing Attack** | Exploits the Error Passive mode of the CAN protocol. Involves generating error frames to force the ECU into the error passive state, then waiting for a targetet frame to appear on the bus and overwriting data and CRC fields with a spoofed payload. Due to the error passive state, the targeted ECU cannot signal an error before it is accepted and responded to by other ECUs. This attack subverts the CAN protocol itself and is harder to detect using conventional bus monitoring. | Spoofing, Tampering |                    |
| 05  | **Wire-Cutting Spoofing Attack**  | Requires physical access to the CAN bus, enabling the attacker to cut wires and partition the bus. By emulating one partition and gatewaying frames, the attacker can spoof frames to the other partition, potentially manipulating data.                                                                                                                                                                                                                                                     | Spoofing (MITM)     |                    |
| 06  | **Double Receive Attack**         | Exploits a CAN protocol feature where receivers accept a frame as finished slightly earlier than transmitters. By asserting a dominant bit at a specific time, the attacker triggers a double receive scenario. This can lead to unintended consequences if systems are not designed to handle such situations.                                                                                                                                                                               | Spoofing, Tampering |                    |
| 07  | **Bus-Off Attack**                | Drives a targeted ECU offline by targeting all frames from that ECU. Forces the Transmit Error Counter above 255, causing the ECU's CAN controller to go bus-off.                                                                                                                                                                                                                                                                                                                             | Denial of Service   |                    |
| 08  | **Freeze Doom Loop Attack**       | Exploits a legacy feature of the CAN protocol by freezing bus traffic for an arbitrary time. Difficult to detect, this attack involves asserting a dominant bit at specific points in the inter-frame space (IFS), causing controllers to enter an error recovery process without incrementing error counters. Can be used for delaying frames or as a simple denial-of-service attack.                                                                                                       | Denial of Service   |                    |
| 09  | **CAN Injection**                 | Involves using a modified CAN transciever which can actively drive the recessive “1” state on the CAN bus. Using this method, the attacker blocks the CAN arbitration and error mechanisms, allowing him to spoof frames without protocol restrictions.                                                                                                                                                                                                                                       | Spoofing            |                    |