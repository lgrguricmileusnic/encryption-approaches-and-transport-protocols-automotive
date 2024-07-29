
# Description

AutoSAR (Automotive Open System Architecture) SecOC (Security On-board Communication) is a security architecture that aims to protect the communication between the various electronic control units (ECUs) within a vehicle against cyber-attacks.

- SecOC is an AUTOSAR module
- Provides integrity and authentication for messages (PDUs)
- Freshness protects against replay attacks
- Generic specification which can operate with asymmetric or symmetric cryptography
- Key distribution is not specified
    
- Every PDU has a unique identifier (SecOCDataID).
    - On CAN networks, the CAN identifier is used.
    - On Ethernet networks, the PDU identifier or internal mappings for PDU identifier to SecOCDataIDs are used.


![[secOC_diagram.png]]


AutoSAR specifies three different profiles with different sizes for truncated freshness value and truncated MAC. All profiles use CMAC with AES128

- SecOC Profile 1 (or 24Bit-CMAC-8Bit-FV)
    - Algorithm: CMAC/AES-128
    - truncated freshness value: 8 bits
    - truncated MAC: 24 bits
        
- SecOC Profile 2 (or 24Bit-CMAC-No-FV)
    - Algorithm: CMAC/AES-128
    - truncated freshness value: 0 bits
    - truncated MAC: 24 bits
    - Don’t use freshness values at all
        
- SecOC Profile 3 (or JASPAR)
    - Algorithm: CMAC/AES-128
    - length of freshness value: 64 bits
    - truncated freshness value: 4 bits
    - truncated MAC: 28 bits

# Implementations
# Scapy (socketCAN Linux)
https://munich.dissec.to/kb/chapters/can/can-secoc.html
- for testing
# Open source SecOC implementation

https://github.com/HosamAboabla/Autosar_SecOC
