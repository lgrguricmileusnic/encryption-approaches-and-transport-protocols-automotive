# UDS introduction
- [https://www.csselectronics.com/pages/uds-protocol-tutorial-unified-diagnostic-services](https://www.csselectronics.com/pages/uds-protocol-tutorial-unified-diagnostic-services)
- [https://dissec.to/kb/chapters/uds/uds.html#communication-examples](https://dissec.to/kb/chapters/uds/uds.html#communication-examples)
# Security related services:

- **0x10 Diagnostic Session Control**
    - allows changing sessions
    - sessions define which services are available
        - “Programming Session” - for uploading new firmware.
        - "Extended Diagnostic Session" - used to unlock additional diagnostic functions, such as the adjustment of sensors.
        - "Safety system diagnostic session" used to test all safety-critical diagnostic functions, such as airbag tests.
        - proprietary sessions

- **0x11 ECU Reset**
    - resets the ECU
    - should not be triggerable while driving

- **0x27 Security Access & 0x29 Authentication**
    - crucial for implementing authenticated access to security-critical services
    - 0x29 allows for PKI based authentication

- **0x28 Communication Control**
    - allows silencing a ECU if enabled.

- **0x84 Secured Data Transmission**
	- **Read**
	    - **0x22 Data By Identifier**
	        - enables reading data by OEM specific identifiers.
	        - Data IDs can contain keys, passwords, milage, commands.
	    
		- **0x23 Memory By Address**
	        - enables reading from memory by address.
	
	- **Write**
	    - **0x2E Data By Identifier**
	        - enables writing data by OEM specific identifiers.
	        - Data IDs can contain keys, passwords, milage, commands.
	    
	    - **0x3D Memory By Address**
	        - enables writing to memory by address.

- **0x2F Input Output Control By Identifier**
    
    - allows to overwrite input signals or to control actuators.

- **0x31 Routine Control**
    - used for arbitrary functions from OEMs. Can be safety critical actions, security access related functions, or necessary functions during software updates.

- **0x34 Request Download**
    - initiates a software update.

- **0x36 Transfer Data**
    - transports the software update data.

- **0x3E Tester Present**
    - needs to be send periodically, to keep ECU in a certain session / security access level

# Attack catalogue by UDS service

## `0x10` Diagnostic Session Control
| **ID** | **Attack**        | **Description**                                                                                                                                                                            | **Prerequisites**                                                                                               | **MITRE EMB3D TIDs**                                    |
| :----: | ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
| DSC01  | UDS Session Abuse | Impact of abusing this service depends on its implementation, but can enable further attacks. For example, switching to the Programming Session can allow for flashing malicious firmware. | Service 0x10 doesn’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. | [TID-310](https://emb3d.mitre.org/threats/TID-310.html) |
## `0x27` Secure Access
| **ID** | **Attack**                                  | **Description**                                                                                                                                                                       | **Prerequisites**                                      | **MITRE EMB3D TIDs**                                                                                            |
| :----: | ------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------- |
|  SA01  | Reverse engineer secure access key function | The UDS protocol doesn’t specify the seed-and-key challenge. A cryptographically weak function for calculating the key can be easily reverse engineered thus breaking access control. | Cryptographically weak security access implementation. | [TID-317](https://emb3d.mitre.org/threats/TID-317.html)                                                         |
|  SA02  | Key replay attack                           | A non-random seed can allow for replaying a captured key and gaining secure access.                                                                                                   | Cryptographically weak source of randomness.           | [TID-317](https://emb3d.mitre.org/threats/TID-317.html),[TID-221](https://emb3d.mitre.org/threats/TID-221.html) |
|  SA03  | Key bruteforce attack                       | A cryptographically weak source of randomness for seed generation can allow for bruteforcing attacks on the key.                                                                      | Cryptographically weak source of randomness.           | [TID-317](https://emb3d.mitre.org/threats/TID-317.html)                                                         |
|  SA04  | Fault Injection                             | Attacker can use fault injection to skip instructions which check the key.                                                                                                            | Physical access to the ECU board.                      | [TID-105](https://emb3d.mitre.org/threats/TID-105.html)                                                         |
## `0x11` ECU Reset

| **ID** | **Attack**                        | **Description**                                                                                                                                                                                                                                                                      | **Prerequisites**                                                                                               | **MITRE EMB3D TIDs**                                                                                                                                                      |
| :----: | --------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|  ER01  | ECU DoS                           | Service 0x11 can be used to reset and temporarily disable a safety-critical ECU during driving.                                                                                                                                                                                      | Service 0x11 is not disabled during vehicle opearation.                                                         | [TID-310](https://emb3d.mitre.org/threats/TID-310.html), [TID-404](https://emb3d.mitre.org/threats/TID-404.html), [TID-222](https://emb3d.mitre.org/threats/TID-222.html) |
|  ER02  | Diagnostic Session Control Bypass | By resetting the ECU, the attacker can jump to the bootloader code, potentially switching to a UDS Programming Session or enable other attacks. This can be useful to the attacker if service 0x10 requires authentication. This can also be achieved through power cycling the ECU. | Service 0x11 doesn’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. | [TID-310](https://emb3d.mitre.org/threats/TID-310.html)                                                                                                                   |
## `0x28` Communication Control
| **ID** | **Attack** | **Description**                                                             | **Prerequisites**                                                                                                | **MITRE EMB3D TIDs**                                    |
| :----: | ---------- | --------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
|  CC01  | ECU DoS    | Attacker completely disables sending and receiving messages for target ECU. | Service 0x28 doesn’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services.. | [TID-404](https://emb3d.mitre.org/threats/TID-404.html) |
##  "Read" services `0x19`, `0x22`, `0x23`, `0x24`, `0x2A`, `0x86`
| **ID** | **Attack**        | **Description**                                                                                                      | **Prerequisites**                                                                                         | **MITRE EMB3D TIDs**                                    |
| :----: | ----------------- | -------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
|  R01   | Unauthorized read | Attacker can use these services to gather internal information about an ECU or the vehicle or even extract firmware. | Services don’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. | [TID-224](https://emb3d.mitre.org/threats/TID-224.html) |
## "Write" services `0x2E`, `0x3D`
| **ID** | **Attack**         | **Description**                                                                                          | **Prerequisites**                                                                                         | **MITRE EMB3D TIDs**                                    |
| :----: | ------------------ | -------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
|  W01   | Unauthorized write | Attacker can use these services to modify memory (stored data or code), impacting operational integrity. | Services don’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. | [TID-224](https://emb3d.mitre.org/threats/TID-224.html) |
## `0x31` Routine Control
| **ID** | **Attack**                              | **Description**                                                                           | **Prerequisites**                                                                                          | **MITRE EMB3D TIDs**                                    |
| :----: | --------------------------------------- | ----------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
|  RC01  | Exploit vulnerable proprietary routines | Attacker can exploit various vulnerabilities possibly present in routine implementations. | Service doesn’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. | [TID-224](https://emb3d.mitre.org/threats/TID-224.html) |
## 0x34 - 0x38 "Firmware upload/download" services

| **ID** | **Attack**                         | **Description**                                                                                                            | **Prerequisites**                                                                                         | **MITRE EMB3D TIDs**                                    |
| :----: | ---------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
|  UD01  | Exploit vulnerable update services | Attacker can exploit various vulnerabilities possibly present in firmware upload/download service implementations.         | Services don’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. |                                                         |
|  UD02  | Unauthorized firmware download     | Attacker can use these services to extract firmware from the target ECU.                                                   | Services don’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. | [TID-224](https://emb3d.mitre.org/threats/TID-224.html) |
|  UD03  | Arbitrary Code Execution           | Attacker can use these services to upload a malicious firmware version if the update process is not appropriately secured. | Services don’t require authentication or a exploitable vulnerability exists in the 0x27 or 0x29 services. | [TID-211](https://emb3d.mitre.org/threats/TID-211.html) |

[[automotive cybersecurity/literature#UDS|literature]]