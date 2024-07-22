
Consists of properites and threats that map to said properties. Threat is defined by:
- ID
- Overview
- Description
- Maturity and Evidence
	- Threat Maturity: This defines the maturity of the threat, including whether it is an Observed Adversarial Technique, Known Exploitable Weakness (KEV), Proof of Concept, or Theoretic threat.
	- Threat Evidence: This provides references to the specific threat event, including ATT&CK TTPs, technical reporting, and research papers/presentations defining the threat. The exact contents of this field depend on the defined Threat Maturity level, asdefined in the following table.
	  ![[emb3d_maturity_evidence.png]]
- Supporting Weaknesses and Vulnerabilities (CWEs and CVEs)

Properties are separated in categories:
- hw architecture
- system software
- application software
- networking

An example of a property threat mapping (1:N) ([link](https://emb3d.mitre.org/properties-list/)):
- Proprety "Device includes a hardware access port (e.g., UART, JTAG)" (PID-15)
	- Threats:
		- Firmware/Data Extraction via Hardware Interface (TID-115)
		- Latent Privileged Access Port (TID-116)
		- Latent Hardware Debug Port Allows Memory/Code Manipulation (TID-119)